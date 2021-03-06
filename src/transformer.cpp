#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/PointStamped.h>
#include <std_msgs/Int32.h>

int32_t tracked_frame;

void trackedIdCallback(const std_msgs::Int32 msg){
  tracked_frame = msg.data;
}

int main(int argc, char** argv){
  
  // Ros initializations
  ros::init(argc, argv, "transformer");
  ros::NodeHandle node;
  ros::Rate rate(10.0);
  ros::Subscriber sub=node.subscribe ("detected_Id",1000,trackedIdCallback);
  
  //tf initializations 
  geometry_msgs::TransformStamped transformStamped;
  static tf2_ros::TransformBroadcaster br;
  tf::TransformListener listener;
  tf::StampedTransform transform;
  tf::StampedTransform transform_tag1world;
  tf::StampedTransform transform_tag2world;
  tf::StampedTransform transform_tag3world;
  tf::Transform transform_worldcamera;
  
  while (node.ok()){

    try{
      // Check tags position and detected tag, then calculate transforms.
      listener.lookupTransform("rgb_mert", "detected_frame", ros::Time(0), transform);
      listener.lookupTransform("world", "tag1", ros::Time(0), transform_tag1world);
      listener.lookupTransform("world", "tag2", ros::Time(0), transform_tag2world);
      listener.lookupTransform("world", "tag3", ros::Time(0), transform_tag3world);
    }   
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }
    
    if (tracked_frame == 10){
      
        transform_worldcamera = transform_tag1world*transform;
    }
    else if (tracked_frame == 13){
    
      transform_worldcamera = transform_tag2world*transform;
    }
    else if (tracked_frame == 7){
       transform_worldcamera = transform_tag3world*transform;
    }
	// Sending the transform of estimated camera position to world frame
	transformStamped.header.stamp = ros::Time::now();
	transformStamped.header.frame_id = "world";
	transformStamped.child_frame_id = "camera";
	transformStamped.transform.translation.x = transform_worldcamera.getOrigin().x();
	transformStamped.transform.translation.y = transform_worldcamera.getOrigin().y();
	transformStamped.transform.translation.z = transform_worldcamera.getOrigin().z();
	transformStamped.transform.rotation.x = transform_worldcamera.getRotation().w();
	transformStamped.transform.rotation.y = transform_worldcamera.getRotation().z();
	transformStamped.transform.rotation.z = transform_worldcamera.getRotation().y();
	transformStamped.transform.rotation.w = transform_worldcamera.getRotation().x();
	br.sendTransform(transformStamped);	 	
     
	ros::spinOnce();
	rate.sleep();
  }
  return 0;
};