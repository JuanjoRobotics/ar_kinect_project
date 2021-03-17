#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/PointStamped.h>

int main(int argc, char** argv){
  
  ros::init(argc, argv, "transformer");
  ros::NodeHandle node;
  tf::TransformListener listener;
  geometry_msgs::TransformStamped transformStamped;
  ros::Rate rate(10.0);
  static tf2_ros::TransformBroadcaster br;

  while (node.ok()){
    
    tf::StampedTransform transform;
    tf::StampedTransform transform_tag0world;
    tf::Transform transform_worldcamera;


    
    try{
      listener.lookupTransform("rgb_mert", "detected_frame", ros::Time(0), transform);
      listener.lookupTransform("world", "tag0", ros::Time(0), transform_tag0world);

    }
    
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }
    
     transform_worldcamera = transform_tag0world*transform;

      transformStamped.header.stamp = ros::Time::now();
      transformStamped.header.frame_id = "world";
      transformStamped.child_frame_id = "camera";
      transformStamped.transform.translation.x = transform_worldcamera.getOrigin().x();
      transformStamped.transform.translation.y = transform_worldcamera.getOrigin().y();
      transformStamped.transform.translation.z = transform_worldcamera.getOrigin().z();
      transformStamped.transform.rotation.x = transform_worldcamera.getRotation().x();
      transformStamped.transform.rotation.y = transform_worldcamera.getRotation().y();
      transformStamped.transform.rotation.z = transform_worldcamera.getRotation().z();
      transformStamped.transform.rotation.w = transform_worldcamera.getRotation().w();
      br.sendTransform(transformStamped);	 

      rate.sleep();
  }
  return 0;
};