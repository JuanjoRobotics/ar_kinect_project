#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf/tf.h>  
#include <tf/transform_datatypes.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "tag_cast");
  ros::NodeHandle node;

  tf2_ros::TransformBroadcaster tfb;
  geometry_msgs::TransformStamped transformStamped;
  geometry_msgs::TransformStamped transformStamped2;
  geometry_msgs::TransformStamped transformStamped3;
  geometry_msgs::TransformStamped transformStamped4;
  geometry_msgs::TransformStamped transformStamped5;
  geometry_msgs::TransformStamped transformStamped6;
  geometry_msgs::TransformStamped transformStamped7;
  geometry_msgs::TransformStamped transformStamped8;
  geometry_msgs::TransformStamped transformStampedbase;
  geometry_msgs::TransformStamped transformStampedTag;
  tf::Transform transform_worldcamera;
  tf::TransformListener listener;
  tf::StampedTransform CameraTransform;
  tf::StampedTransform TagTransform;
  
  // Tag 1(10)
  transformStamped.header.frame_id = "world";
  transformStamped.child_frame_id = "tag1";
  transformStamped.transform.translation.x = -1.975;
  transformStamped.transform.translation.y = -0.675;
  transformStamped.transform.translation.z = 0.3;
  transformStamped.transform.rotation.x = 0.5;
  transformStamped.transform.rotation.y = 0.5;
  transformStamped.transform.rotation.z = 0.5;
  transformStamped.transform.rotation.w = 0.5;
  
  // Tag 2(13)
  transformStamped2.header.frame_id = "world";
  transformStamped2.child_frame_id = "tag2";
  transformStamped2.transform.translation.x = -1.975;
  transformStamped2.transform.translation.y = 0.325;
  transformStamped2.transform.translation.z = 0.3;
  transformStamped2.transform.rotation.x = 0.5;
  transformStamped2.transform.rotation.y = 0.5;
  transformStamped2.transform.rotation.z = 0.5;
  transformStamped2.transform.rotation.w = 0.5;
  
   // Tag 3(7)
  transformStamped3.header.frame_id = "world";
  transformStamped3.child_frame_id = "tag3";
  transformStamped3.transform.translation.x = 1.75;
  transformStamped3.transform.translation.y = -0.518;
  transformStamped3.transform.translation.z = 0.3;
  transformStamped3.transform.rotation.x = 9.1269612312317e-08;
  transformStamped3.transform.rotation.y = 0.7071071267128;
  transformStamped3.transform.rotation.z = 0.7071071267128;
  transformStamped3.transform.rotation.w = -9.1269612312317e-08;
  
  // Tag 4
  transformStamped4.header.frame_id = "world";
  transformStamped4.child_frame_id = "tag4";
  transformStamped4.transform.translation.x = 2.4249992370605;
  transformStamped4.transform.translation.y = 3.9250001907349;
  transformStamped4.transform.translation.z = 0.3;
  transformStamped4.transform.rotation.x = 0.70710736513138;
  transformStamped4.transform.rotation.y = -9.1269647839454e-08;
  transformStamped4.transform.rotation.z = -9.1269647839454e-08;
  transformStamped4.transform.rotation.w = 0.70710617303848;
  
  // Tag 5 (14)
  transformStamped5.header.frame_id = "world";
  transformStamped5.child_frame_id = "tag5";
  transformStamped5.transform.translation.x = -4.0000004768372;
  transformStamped5.transform.translation.y = 2.4250e+00;
  transformStamped5.transform.translation.z = 0.3;
  transformStamped5.transform.rotation.x = 0.5;
  transformStamped5.transform.rotation.y = 0.5;
  transformStamped5.transform.rotation.z = 0.5;
  transformStamped5.transform.rotation.w = 0.5;

    // Tag 6 (9)
  transformStamped6.header.frame_id = "world";
  transformStamped6.child_frame_id = "tag6";
  transformStamped6.transform.translation.x = -3.9750018119812;
  transformStamped6.transform.translation.y = -1.5250006914139;
  transformStamped6.transform.translation.z = 0.3;
  transformStamped6.transform.rotation.x = 0.5;
  transformStamped6.transform.rotation.y = 0.5;
  transformStamped6.transform.rotation.z = 0.5;
  transformStamped6.transform.rotation.w = 0.5;   

    // Tag 7 (3)
  transformStamped7.header.frame_id = "world";
  transformStamped7.child_frame_id = "tag7";
  transformStamped7.transform.translation.x = -1.7500016689301;
  transformStamped7.transform.translation.y = -4.3500003814697;
  transformStamped7.transform.translation.z = 0.3;
  transformStamped7.transform.rotation.x = -9.6857469600309e-08;
  transformStamped7.transform.rotation.y = 0.707106590271;
  transformStamped7.transform.rotation.z = 0.70710694789886;
  transformStamped7.transform.rotation.w = -9.6857469600309e-08;  

    // Tag 8 (12)
  transformStamped8.header.frame_id = "world";
  transformStamped8.child_frame_id = "tag8";
  transformStamped8.transform.translation.x = 1.7249981164932;
  transformStamped8.transform.translation.y = -1.1000003814697;
  transformStamped8.transform.translation.z = 0.3;
  transformStamped8.transform.rotation.x = 0.70711588859558;
  transformStamped8.transform.rotation.y = 1.0058400334856e-07;
  transformStamped8.transform.rotation.z = -9.8721329777618e-08;
  transformStamped8.transform.rotation.w = 0.70709764957428;
  
  // Base_robot
  transformStampedbase.header.frame_id = "camera";
  transformStampedbase.child_frame_id = "base_robot"; 	
  transformStampedbase.transform.translation.x = 0;
  transformStampedbase.transform.translation.y = -0.1187; //z
  transformStampedbase.transform.translation.z = -0.1650; //x
  transformStampedbase.transform.rotation.x = 0.5;
  transformStampedbase.transform.rotation.y = 0.5;
  transformStampedbase.transform.rotation.z = 0.5;
  transformStampedbase.transform.rotation.w = -0.5;

  
  ros::Rate rate(14.0);
  
  while (node.ok()){
    transformStamped.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped);
    
    transformStamped2.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped2);
    
    transformStamped3.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped3);
    
    transformStamped4.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped4);
    
    transformStamped5.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped5);

    transformStamped6.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped6);
    
    transformStamped7.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped7);
    
    transformStamped8.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped8);
    
    transformStampedbase.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStampedbase);
    
    try{
      // Check tags position and detected tag, then calculate transforms.
      listener.lookupTransform("rgb_mert", "detected_frame", ros::Time(0), CameraTransform);
      listener.lookupTransform("world", "rgb_mert", ros::Time(0), TagTransform);
    }   
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }	 
    
  transform_worldcamera = TagTransform*CameraTransform;
	    
  transformStampedTag.header.frame_id = "world";
  transformStampedTag.child_frame_id = "current_tag";
  transformStampedTag.transform.translation.x = transform_worldcamera.getOrigin().x();
  transformStampedTag.transform.translation.y = transform_worldcamera.getOrigin().y();
  transformStampedTag.transform.translation.z = transform_worldcamera.getOrigin().z();
  transformStampedTag.transform.rotation.x = transform_worldcamera.getRotation().w();
  transformStampedTag.transform.rotation.y = transform_worldcamera.getRotation().z();
  transformStampedTag.transform.rotation.z = transform_worldcamera.getRotation().y();
  transformStampedTag.transform.rotation.w = transform_worldcamera.getRotation().x();
  transformStampedTag.header.stamp = ros::Time::now();
  tfb.sendTransform(transformStampedTag);

    
    rate.sleep();
    // printf("sending\n"); //this line can be used as debug to check the correct functioning of this node.
  }

};