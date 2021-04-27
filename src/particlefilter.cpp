#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include "tf/tf.h"
#include "random_numbers/random_numbers.h"
#include "geometry_msgs/PoseArray.h"
#include <tf/transform_listener.h>
#include <std_msgs/Int32.h>

ros::Publisher pub;
random_numbers::RandomNumberGenerator distrib;
geometry_msgs::PoseArray parray;
geometry_msgs::Pose array;

int particles = 100;
double samples[100][3] = {0};
double last_pose[3] = {0};
const double PI = 3.1415926535;

tf::StampedTransform FrameTransform;
tf::StampedTransform BaseTransform; 
tf::Transform TagTransform; 
tf::Transform BaseTrans;

// Pose composition function
void pose_comp(double p1_data[3],double p2_data[3], double p[3])
{
  double b_x_tmp;
  double x_tmp;
  x_tmp = std::sin(p1_data[2]);
  b_x_tmp = std::cos(p1_data[2]);
  p[0] = (p1_data[0] + p2_data[0] * b_x_tmp) - p2_data[1] * x_tmp;
  p[1] = (p1_data[1] + p2_data[0] * x_tmp) + p2_data[1] * b_x_tmp;
  p[2] = p1_data[2] + p2_data[2];
}

void get_control(double pose[3],double old_pose[3], double control[3])
{
  //theta1, wrapped between -pi,pi
  double theta1;
  theta1 = std::atan2(pose[1]-old_pose[1],pose[0]-old_pose[0])-old_pose[2];
  theta1= std::fmod(theta1+PI,2*PI);
  if (theta1< 0){theta1 = theta1+ 2*PI;} 
  theta1 = theta1 - PI;
  control[0] = theta1;

  //d
  control[1] = std::sqrt(std::pow(pose[0]-old_pose[0],2)+std::pow(pose[1]-old_pose[1],2));

  //theta2, also wrapped
  double theta2;
  theta2 = pose[2]-old_pose[2]-control[0];
  theta2= std::fmod(theta2+PI,2*PI); 
  if (theta2< 0){theta2 = theta2+ 2*PI;} 
  theta2 = theta2 - PI;
  control[2] = theta2;
 
}
int32_t tracked_frame = 0;

void trackedIdCallback(const std_msgs::Int32 msg){
  tracked_frame = msg.data;
}

void PoseCallback(const nav_msgs::Odometry::ConstPtr & msg)
{	
	// pose and control signal
	double current_pose[3];	
	double control[3];
	double pose[3];
	double mid_pose[3];
	double final_pose[3];
	
	// Noise parameters
	double alpha1 = 0.02;
        double alpha2 = 0.02;
        double alpha3 = 0.4;
	double alpha4 = 0.4;
	double mu = 0;
	double n = 1;
	double sigma1;
	double sigma2;
	double sigma3;
	double sigma_sensor = 0.5;
	
	// noise control
	double noisy_control[3];
	double sampling_theta1;
	double sampling_theta2;
	double sampling_d;
	
	// weight
	double TagDistanceX;
	double TagDistanceY;
	double Basex;
	double Basey;	
	double Zpred[100] = {0};
	double Z = 0;
	double Zx = 0;
	double Zy = 0;
	double W[100] = {0};	
	
	if (tracked_frame != 0){
	  
	    // Get Z distance
	    TagDistanceX = FrameTransform.getOrigin().z();
	    TagDistanceY = FrameTransform.getOrigin().x();
	    Basex = BaseTransform.getOrigin().x();
	    Basey = BaseTransform.getOrigin().y();
	    Z = std::sqrt(std::pow(Basex-TagDistanceX,2)+std::pow(Basey-TagDistanceY,2));
	}
	
	// Pose x,y
	tf::Point p(msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);	
	// Orientation
	double rotx,roty,rotz;
	tf::Quaternion q(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	tf::Matrix3x3 m(q);
	m.getRPY(rotx,roty,rotz);
	
	// Current pose
	current_pose[0] = p.x();
	current_pose[1] = p.y();
	current_pose[2] = rotz;
	
	// calculating control
	get_control(current_pose,last_pose,control);
	
	// Particle Filter implementation	
	parray.poses.clear();
	
	// building 100 particles
	for(int i=0;i < particles;i++)
	{
	    // building noise for control signal
	    
	    sigma1 = (alpha1*std::pow(control[0],2))+(alpha2*std::pow(control[1],2));   
	    sigma2 = (alpha3*std::pow(control[1],2))+(alpha4*(std::pow(control[0],2)+std::pow(control[2],2))); 
	    sigma3 = (alpha1*std::pow(control[2],2))+(alpha2*std::pow(control[1],2));
	    
	    sampling_theta1 = sigma1*distrib.gaussian(n,1)+mu;
	    sampling_d = sigma2*distrib.gaussian(n,1)+mu;
	    sampling_theta2 = sigma3*distrib.gaussian(n,1)+mu;
	  
	    noisy_control[0] = control[0]+sampling_theta1;
	    noisy_control[1] = control[1]+sampling_d;
	    noisy_control[2] = control[2]+sampling_theta2;
	  
	    // Get pose from control
	    pose[0] = noisy_control[1]*std::cos(last_pose[2]+noisy_control[0]);
	    pose[1] = noisy_control[1]*std::sin(last_pose[2]+noisy_control[0]);
	    pose[2] = noisy_control[0]+noisy_control[2];
	    
	    // Building samples
	    samples[i][0] = samples[i][0] + pose[0];
	    samples[i][1] = samples[i][1] + pose[1];
	    samples[i][2] = samples[i][2] + pose[2];
	    
	   if (tracked_frame !=0){
	      // Weight computation
	      Zpred[i] = std::sqrt(std::pow(TagDistanceX-samples[i][0],2)+std::pow(TagDistanceY-samples[i][1],2));
	      W[i] = std::exp(-0.5*(Z - Zpred[i])*(1/sigma_sensor)*(Z - Zpred[i])) + 0.001;
	   }
	}
	
	if (tracked_frame !=0){
	    // weight selection
	    double sum = 0;
	    double cumsum[100] = {0};
	    double CDF[100] = {0};
	    double iselect[100] = {0};
	    double inext[100][3] = {0};
	    
	    // Cumsum function
	    for(int i = 0; i < particles ; i++){
		sum+=W[i];
		cumsum[i]=sum;
	    }
	    
	    // CDF and random selection
	    for(int i = 0; i < particles ; i++){
		CDF[i] = cumsum[i]/sum;
		iselect[i] = distrib.uniform01();

	    }

	    // Interpolation
	    for(int i =0; i < particles;i++) {
		for(int j=0;j < particles;j++) {
		    if ( iselect[i] <= CDF[j]) {
			inext[i][0] = samples[j][0];
			inext[i][1] = samples[j][1];
			inext[i][2] = samples[j][2];
			break;
		    } 		    
		}
	    }
	    
	    for (int i= 0;i < particles;i++) {
		// Resampling
		samples[i][0] = inext[i][0];
		samples[i][1] = inext[i][1];
		samples[i][2] = inext[i][2];
	    }
	}
	

	// Building array from samples
	for (int i=0; i < particles; i++) {
	  	    
	    // Pose building
	    array.position.x = samples[i][0];	   
	    array.position.y = samples[i][1];
	    array.position.z = 0;
	      
	    array.orientation.x = 0;
	    array.orientation.y = 0;
	    array.orientation.z = sin(samples[i][2]/2);
	    array.orientation.w = cos(samples[i][2]/2);

	    // Pushing this pose to PoseArray
	    parray.poses.push_back(array);
	}
	
	// PoseArray header parameters
	parray.header.stamp = ros::Time::now();
	parray.header.frame_id = "world";
	pub.publish(parray);
	
	// Saving current pose as last pose
	last_pose[0] = current_pose[0];
	last_pose[1] = current_pose[1];
	last_pose[2] = current_pose[2];
	tracked_frame = 0;
}

int main (int argc, char **argv)
{
    ros::init(argc,argv,"particlefilter");
    ros::NodeHandle n;           
    //subscribing to odometry pose
    ros::Subscriber sub=n.subscribe ("odom",100,PoseCallback);	
    //Subscribing to detected Id
    ros::Subscriber sub2=n.subscribe ("detected_Id",100,trackedIdCallback);
    //publishing array of estimated poses
    pub=n.advertise<geometry_msgs::PoseArray>("particleFilter",100);
    // To listen transforms
    tf::TransformListener listener;
    
while (ros::ok()){ 
	    // Try to listen the tf of the detected tag and predicted base_robot
	try{
	    listener.lookupTransform("current_tag","world", ros::Time(0), FrameTransform);
	    listener.lookupTransform("base_robot","world", ros::Time(0), BaseTransform);
	    }   
	catch (tf::TransformException ex){
	    ROS_ERROR("%s",ex.what());
	    ros::Duration(1.0).sleep();
	}
	
	ros::spinOnce();
    }
}