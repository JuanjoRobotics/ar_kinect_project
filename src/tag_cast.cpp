#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "tag_cast");
  ros::NodeHandle node;

  tf2_ros::TransformBroadcaster tfb;
  geometry_msgs::TransformStamped transformStamped;
  geometry_msgs::TransformStamped transformStamped2;
  geometry_msgs::TransformStamped transformStamped3;

  
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
  
  ros::Rate rate(14.0);
  
  while (node.ok()){
    transformStamped.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped);
    
    transformStamped2.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped2);
    
    transformStamped3.header.stamp = ros::Time::now();
    tfb.sendTransform(transformStamped3);
    rate.sleep();
    // printf("sending\n"); //this line can be used as debug to check the correct functioning of this node.
  }

};