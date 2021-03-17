#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <tf/tf.h>  
#include <tf/transform_datatypes.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>

ros::Publisher pub;


void cmd_trackCallback(ar_track_alvar_msgs::AlvarMarkers req)
{
      static tf2_ros::TransformBroadcaster br;
      geometry_msgs::TransformStamped transformStamped;

      double rotx,roty,rotz;
	// check if we have any marker
      if (!req.markers.empty()) {
	
	// Get orientation
	tf::Quaternion q(req.markers[0].pose.pose.orientation.x, req.markers[0].pose.pose.orientation.y, req.markers[0].pose.pose.orientation.z, req.markers[0].pose.pose.orientation.w);
	tf::Matrix3x3 m(q);
	m.getRPY(rotx,roty,rotz);
	
	// Get position
	tf::Point p(req.markers[0].pose.pose.position.x, req.markers[0].pose.pose.position.y, req.markers[0].pose.pose.position.z);
	
	// Building and sending transformation of detected tag respect to kinect
	 transformStamped.header.stamp = ros::Time::now();
	 transformStamped.header.frame_id = "rgb_mert";
	 transformStamped.child_frame_id = "detected_frame";
	 transformStamped.transform.translation.x = p.x();
	 transformStamped.transform.translation.y = p.y();
	 transformStamped.transform.translation.z = p.z();
	 transformStamped.transform.rotation.x = q.x();
	 transformStamped.transform.rotation.y = q.y();
	 transformStamped.transform.rotation.z = q.z();
	 transformStamped.transform.rotation.w = q.w();
	 br.sendTransform(transformStamped);	 

      }  
}

int main (int argc, char **argv)
{
        ros::init(argc,argv,"track_pose");
        ros::NodeHandle n;
        ros::Subscriber sub=n.subscribe ("ar_pose_marker",1000,cmd_trackCallback);
	ros::spin(); // <--equivalente bucle infinito
}

