#!/bin/sh

xterm  -e "source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 7
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects_node; ($SHELL)" &
