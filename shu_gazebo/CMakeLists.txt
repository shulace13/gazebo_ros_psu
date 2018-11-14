cmake_minimum_required(VERSION 2.8.3)
project(shu_gazebo)

find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  geometry_msgs
  roscpp
  rosgraph_msgs
  std_msgs
  std_srvs
  tf
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES shu_gazebo
#  CATKIN_DEPENDS dynamic_reconfigure geometry_msgs roscpp rosgraph_msgs std_msgs std_srvs tf
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(circles_vel src/circles_vel.cpp)
target_link_libraries(circles_vel ${catkin_LIBRARIES})

add_executable(squares_vel src/square.cpp)
target_link_libraries(squares_vel ${catkin_LIBRARIES})
