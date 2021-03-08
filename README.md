# ar_kinect_project
A repository for my Degree Final Project (TFG), based on localization using ar_track_alvar. When this package reach it final version it should locate a robot using a kinect or a conventional RGB camera, helped by augmented reality tags. <br/>

# Updates
Version 1.0: first uploaded version. <br/>
- We have two operative CoppeliaSim scenes, one for simulating AR tags and sending kinect rgb/depth information to ROS and other one for sending ground truth and odometry of a robot to ROS.<br/>
- There are nodes for manage CoppeliaSim data and show a coloured point cloud (in RVIZ, for example). This nodes also create TF data.<br/>
- In this version we can't track using coloured pointcloud2 but it works using RGB data.<br/>

# File layout
* coppelia_scenes: Contains CoppeliaSim simulation scenes.
* launch: Contains launch files, such as tracking with/without kinect files and pointcloud2 generator file.
* src: Contains all cpp files necessaries for tracking, transform data and move the robot.

My Float32multiarray_to_pointcloud2 code was taken from: https://github.com/marco-teixeira/float32multiarray_to_pointcloud2 <br/>

# How to install and use
First of all, install ar_track_alvar. [Follow these steps](http://wiki.ros.org/ar_track_alvar) to install it.

To download and use this package do: <br/>

$ cd ~/catkin_ws/src <br/>
$ git clone https://github.com/JuanjoRobotics ar_kinect_project.git <br/>
$ cd ~/catkin_ws <br/>
$ catkin_make <br/>

After successfully catkin_make we are ready to run the following lines: <br/>

Open both scenes and play them, then: <br/>

$ roslaunch ar_kinect_project float32multiarray_to_pointcloud2.launch <br/>
$ rosrun ar_kinect_project cloud_to_rgb
These lines should subscribe to depth and rgb topics, generated by Coppelia scene, and publish one topic with a coloured point cloud (/pcl_out), ready to be visualized using RVIZ. <br/>

At this point we have two options: <br/>
- Using kinect:  <br/>
$ roslaunch ar_kinect_project track_kinect.launch (Not working at the moment) <br/>
- Not using kinect: <br/>
$ roslaunch ar_kinect_project track_no_kinect.launch <br/>
We can see ar_track TF data using RVIZ. <br/>

next, let's see robot movement codes. <br/>
$ rosrun ar_kinect_project random_direction <br/>
$ rosrun ar_kinect_project ros_manager <br/>
These lines will send random values to CoppeliaSim robot, moving it randomly. <br/>
We should see new topics with odometry (/OdometryRobot) and ground truth (/PoseRobot) topics <br/>

# System and Software used

Ubuntu 16.04.7 https://releases.ubuntu.com/16.04/ <br/>
ROS Kinetic http://wiki.ros.org/kinetic <br/>
CoppeliaSim V4.1.0 https://www.coppeliarobotics.com/downloads <br/>

Prueba de git
