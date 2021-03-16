#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "tag0_cast");
  ros::NodeHandle node;

   tf2_ros::TransformBroadcaster tfb;
  geometry_msgs::TransformStamped transformStamped;

  
  transformStamped.header.frame_id = "world";
  transformStamped.child_frame_id = "tag0";
  transformStamped.transform.translation.x = 0.2;
  transformStamped.transform.translation.y = -0.125;
  transformStamped.transform.translation.z = 1.0;
  transformStamped.transform.rotation.x = 0.5;
  transformStamped.transform.rotation.y = 0.5;
  transformStamped.transform.rotation.z = 0.5;
  transformStamped.transform.rotation.w = 0.5;

  ros::Rate rate(14.0);
  while (node.ok()){
    transformStamped.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped);
    rate.sleep();
    printf("sending\n");
  }

};