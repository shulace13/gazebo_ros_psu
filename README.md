# Creating your own gazebo-ros environment

## Install gazebo and ROS
For this repository, we used
* ROS kinetic
* Gazebo 8 (For gym-gazebo it specifies 8.1.1 but using 8.6 for now)(2019/01)

### How to install (gazebo 8)
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
    sudo apt-get update
    sudo apt-get install gazebo8 libgazebo8-dev
Then check your installation via `gazebo` and see if it launches an empty world.

**Notes:** There may be extra dependencies you need to install.

### Install ROS
Install by following [this tutorial](http://wiki.ros.org/kinetic/Installation/Ubuntu)

I recommend installing **desktop-full**

Then proceed to the [following](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment) where you will create your workspace

## Needed ROS Packeges
Get [gazebo_ros_pkgs](https://github.com/ros-simulation/gazebo_ros_pkgs.git)

    cd ~/[catkin_workspace]/src
    git clone https://github.com/ros-simulation/gazebo_ros_pkgs.git -b kinetic-devel
    rosdep update
    rosdep check --from-paths . --ignore-src --rosdistro kinetic

If you see any other packages you need, go ahead and install them

When finished, go back to the top of your workspace and execute the following `catkin_make`
You will also need to clone and make [tutlebot](https://github.com/turtlebot/turtlebot)

## Directory descriptions
Explanations of each directory here.

### diff_drive_gazebo
This is created by following this [site](http://www.theconstructsim.com/how-to-build-a-differential-drive-simulation/).

### gazebo_models
Storing models created by me. 

### gazebo_light_sensor_plugin
Just followed the site [here](http://www.theconstructsim.com/create-a-ros-sensor-plugin-for-gazebo/).

### shu_gazebo
My old workspace.

It contains a launch file where it will open gazebo and spawn a mobile robot.
