/*
 * Created by Shuhei Kozasa 2018/11/02
 *
 * A very simple publisher and subscriber. 
 * Sends command to go in squares
 * 
 * Publishes:
 * /cmd_vel
 *
 * Subscribes:
 * /odom
 *
 * 
 */

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <math.h>
#include <boost/thread.hpp>

#include <iostream>


// float VEL_MAX 0.3
// float VEL_MIN -0.3

boost::mutex mutex_odom;
nav_msgs::Odometry odom;
void odomCallback(const nav_msgs::Odometry& msg){
    boost::mutex::scoped_lock(mutex_odom);
    odom = msg;
}


void straight(geometry_msgs::Twist &vel){
    printf("Straight\n");
    vel.linear.x = 0.2;
    vel.angular.z = 0.0;
}

void turn_left(geometry_msgs::Twist &vel){
    printf("Turn\n");
    vel.linear.x = 0.1;
    vel.angular.z = 0.3;
}

void stop(geometry_msgs::Twist &vel){
    printf("STOP\n");
    vel.linear.x = 0.0;
    vel.angular.z = 0.0;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "squares_vel");
    ros::NodeHandle n;
    ros::Rate rate(10);
    
    geometry_msgs::Twist vel;
    int linear_, angular_;
    double l_scale, a_scale;
    linear_ = 1;
    l_scale = 0.0;
    angular_ = 1;
    a_scale = 0.0;

    bool check_straight, check_turn, check_straight_y;

    // vel.linear.x = linear_*l_scale;
    // vel.angular.z = angular_*a_scale;

    ros::Publisher vel_pub_ = n.advertise<geometry_msgs::Twist>("cmd_vel", 1, true);
    
    // Since we assume that the robot starts from the origin of the world
    // We will take out this section for now (2018/11/02)
    // It was supposed to remember it's initial pose and then
    // we can compare the new pose with this init_pose to determine where the robot is.
    /*
    ros::Subscriber odom_init_sub_ = n.subscribe("/odom",10,odom_initCallback);
    geometry_msgs::Pose init_pose;
    {
        boost::mutex::scoped_lock(mutex_odom_);
        init_pose.position.x = odom_.pose.pose.position.x;
        init_pose.position.y = odom_.pose.pose.position.y;
        init_pose.position.z = odom_.pose.pose.position.z;
    }
    */

    ros::Subscriber odom_sub_ = n.subscribe("/odom",10,odomCallback);

    while(ros::ok()){
                
        // printf("Just showing the init pose\nx = %f\ny = %f\nz = %f\n",
        //        init_pose.position.x, init_pose.position.y, init_pose.position.z);        
        // printf("Just showing the init pose\nx = %f\ny = %f\nz = %f\n",
        //         odom_.pose.pose.position.x, 
        //         odom_.pose.pose.position.y,
        //         odom_.pose.pose.position.z); 

        // geometry_msgs::Pose new_pose;
        nav_msgs::Odometry pose_;
        {
            boost::mutex::scoped_lock(mutex_odom);
            pose_ = odom;
        }
       
        if(pose_.pose.pose.position.x<1.5 && 
                check_straight!=true){
            straight(vel);
        }

        if(pose_.pose.pose.position.x>1.5 &&
                check_turn!=true){
            turn_left(vel);
            check_straight = true;
            // Insert an if thing here to mark the check_turn flag to true
        }

        if(pose_.pose.pose.position.y<1.5 &&
                check_straight_y!=true &&
                check_straight==true &&
                check_turn==true){
            straight(vel);
        }
        
        vel_pub_.publish(vel);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
