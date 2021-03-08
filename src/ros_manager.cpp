#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;
void cmd_dirCallback(const std_msgs::String::ConstPtr & msg);

int main (int argc, char **argv)
{
        ros::init(argc,argv,"manager");
        ros::NodeHandle n;
        
        ros::Subscriber sub=n.subscribe ("cmd_dir",1000,cmd_dirCallback);
        
        pub=n.advertise<geometry_msgs::Twist>("cmd_vel",1000);

       // Option 1
       // while (ros::ok())
       // {
       //     ros::spinOnce();
       // }
        
        //Option 2
        ros::spin(); // <--equivalente bucle infinito
}

void cmd_dirCallback(const std_msgs::String::ConstPtr & msg)
{
        ROS_INFO("Received the direction [%s]\n",msg->data.c_str());
        geometry_msgs::Twist vel_msg;
        double linear=0, angular=0;
        
        if (!strcmp(msg->data.c_str(),"stop"))
        {linear=0;angular=0;}
        else if (!strcmp(msg->data.c_str(),"fordwards"))
        {linear=1;angular=0;}
        else if (!strcmp(msg->data.c_str(),"backwards"))
        {linear=-1;angular=0;}
        else if (!strcmp(msg->data.c_str(),"left"))
        {linear=0;angular=1;}
        else if (!strcmp(msg->data.c_str(),"right"))
        {linear=0;angular=-1;}
        
        vel_msg.linear.x=linear;
        vel_msg.angular.z=angular;
        
        ROS_INFO_STREAM("Value: " << vel_msg.linear.x << " " << vel_msg.angular.z);
        
        pub.publish(vel_msg);
        
    
    
    
}