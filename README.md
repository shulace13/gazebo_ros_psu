# Creating your own gazebo-ros environment

## Install gazebo and ROS
For this repository, we used
* ROS kinetic
* Gazebo 7

### How to install (gazebo 7)
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
    sudo apt-get update
    sudo apt-get install gazebo7 libgazebo7-dev
Then check your installation via `gazebo` and see if it launches an empty world.

Notes: There may be extra dependencies you need to install.

### Install ROS
Install by following [this tutorial](http://wiki.ros.org/kinetic/Installation/Ubuntu)

I recommend installing **desktop-full**

Then proceed to the [following](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)

## Needed ROS Packeges
Get [gazebo_ros_pkgs](https://github.com/ros-simulation/gazebo_ros_pkgs.git)
    cd ~/[catkin_workspace]/src
    git clone https://github.com/ros-simulation/gazebo_ros_pkgs.git -b kinetic-devel
    rosdep update
    rosdep check --from-paths . --ignore-src --rosdistro kinetic
If you see any other packages you need, go ahead and install them

When finished, go back to the top of your workspace and execute the following
    catkin_make
You will also need to clone and make [tutlebot](https://github.com/turtlebot/turtlebot)


