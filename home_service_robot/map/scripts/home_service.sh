#!/bin/sh

export TURTLEBOT_GAZEBO_WORLD_FILE=`rospack find my_robot`/world/myWorld.world
export TURTLEBOT_GAZEBO_MAP_FILE=`rospack find maps`/map.yaml

xterm  -e "source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 7
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e " rviz -d `rospack find rvizConfig`/config.rviz" &
sleep 5
xterm -e " rosrun pick_objects pick_objects_node" &
sleep 5
xterm -e " rosrun add_markers add_markers_node" &
