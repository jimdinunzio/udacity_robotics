#!/bin/sh

export TURTLEBOT_GAZEBO_WORLD_FILE=$HOME/workspace/catkin_ws/src/my_robot/world/myWorld.world
export TURTLEBOT_GAZEBO_MAP_FILE=$HOME/workspace/catkin_ws/src/map/map.yaml

xterm  -e "source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 7
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; rviz -d ~/workspace/catkin_ws/src/map/rvizConfig/config.rviz" &
sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects_node" &
sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; rosrun add_markers add_markers_node" &
