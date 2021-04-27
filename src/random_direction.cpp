#include "ros/ros.h"
#include "std_msgs/String.h"

int main (int argc, char** argv)
{

    ros::init(argc,argv,"random_direction");
    ros::NodeHandle n;

    ros::Publisher pub;
    pub = n.advertise<std_msgs::String>("cmd_dir",1000);

    ros::Rate loop_rate(0.5);
    unsigned dir=0;
    std_msgs::String msg;
    std::string ss;

    while (ros::ok())
    {
	dir=round(4*((double)rand()/(double)RAND_MAX));
	///dir can be 0,1,2,3,4
	switch(dir)
	{
	    case 0: ss="stop";break;
	    case 1: ss="fordwards";break;
	    case 2: ss="backwards";break;
	    case 3: ss="left";break;
	    case 4: ss="right";break;
	}
	
	msg.data=ss;
	
	ROS_INFO("%d ---> %s\n",dir,msg.data.c_str()); 
		
	
	ros::Time timer = ros::Time::now();
	int secs = timer.toSec();
 
	  pub.publish(msg);
	
	loop_rate.sleep(); 
    }
    return 1;
}
