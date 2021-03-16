cmake_minimum_required(VERSION 3.0.2)
project(ar_kinect_project)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  message_generation
  rospy
  pcl_conversions
  pcl_ros
  sensor_msgs
  cv_bridge
  ar_track_alvar_msgs
  tf
  tf2_ros

)

generate_messages(
  DEPENDENCIES
   std_msgs
 )


catkin_package(
)
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable (random_direction src/random_direction.cpp)
target_link_libraries (random_direction ${catkin_LIBRARIES})
add_dependencies(random_direction ${${PROJECT_NAME}_EXPORTED_TARGETS} 
${catkin_EXPORTED_TARGETS})

add_executable (ros_manager src/ros_manager.cpp)
target_link_libraries (ros_manager ${catkin_LIBRARIES})
add_dependencies(ros_manager ${${PROJECT_NAME}_EXPORTED_TARGETS} 
${catkin_EXPORTED_TARGETS})

add_executable(float32_to_pointcloud2 src/float32_to_pointcloud2.cpp)
target_link_libraries(float32_to_pointcloud2 ${catkin_LIBRARIES})

add_executable (cloud_to_rgb src/cloud_to_rgb.cpp)
target_link_libraries (cloud_to_rgb ${catkin_LIBRARIES})
add_dependencies(cloud_to_rgb ${${PROJECT_NAME}_EXPORTED_TARGETS} 
${catkin_EXPORTED_TARGETS})

add_executable (track_pose src/track_pose.cpp)
target_link_libraries (track_pose ${catkin_LIBRARIES})
add_dependencies(track_pose ${${PROJECT_NAME}_EXPORTED_TARGETS} 
${catkin_EXPORTED_TARGETS})

add_executable (tag0_cast src/tag0_cast.cpp)
target_link_libraries (tag0_cast ${catkin_LIBRARIES})
add_dependencies(tag0_cast ${${PROJECT_NAME}_EXPORTED_TARGETS} 
${catkin_EXPORTED_TARGETS})

