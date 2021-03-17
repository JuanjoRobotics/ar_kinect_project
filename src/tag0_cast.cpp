#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "tag0_cast");
  ros::NodeHandle node;

   tf2_ros::TransformBroadcaster tfb;
  geometry_msgs::TransformStamped transformStamped;
  geometry_msgs::TransformStamped transformStamped13;
  
  // Tag 0
  transformStamped.header.frame_id = "world";
  transformStamped.child_frame_id = "tag0";
  transformStamped.transform.translation.x = 0.2;
  transformStamped.transform.translation.y = -0.125;
  transformStamped.transform.translation.z = 1.0;
  transformStamped.transform.rotation.x = 0.5;
  transformStamped.transform.rotation.y = 0.5;
  transformStamped.transform.rotation.z = 0.5;
  transformStamped.transform.rotation.w = 0.5;
  
  // Tag 13
  transformStamped13.header.frame_id = "world";
  transformStamped13.child_frame_id = "tag13";
  transformStamped13.transform.translation.x = 1.75;
  transformStamped13.transform.translation.y = -0.518;
  transformStamped13.transform.translation.z = 1.0;
  transformStamped13.transform.rotation.x = -0.5;
  transformStamped13.transform.rotation.y = 0.5;
  transformStamped13.transform.rotation.z = 0.5;
  transformStamped13.transform.rotation.w = 0.5;
  
  ros::Rate rate(14.0);
  
  while (node.ok()){
    transformStamped.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped);
    
    transformStamped13.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped13);
    rate.sleep();
    printf("sending\n");
  }

};