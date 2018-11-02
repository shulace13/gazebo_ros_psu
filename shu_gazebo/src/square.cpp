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

#include <iostream>

nav_msgs::Odometry odom_;
nav_msgs::Odometry odom;

// float VEL_MAX 0.3
// float VEL_MIN -0.3

void straight(geometry_msgs::Twist &vel){
    printf("Straight\n");
    vel.linear.x = 0.2;
    vel.angular.z = 0.0;
}

void stop(geometry_msgs::Twist &vel){
    printf("STOP\n");
    vel.linear.x = 0.0;
    vel.angular.z = 0.0;
}

void turn_right(geometry_msgs::Twist &vel){
    printf("Turn\n");
    vel.linear.x = 0.1;
    vel.angular.z = 0.3;
}

void odom_initCallback(const nav_msgs::Odometry& msg){
    odom_ = msg;
}

void odomCallback(const nav_msgs::Odometry& msg){
    odom = msg;
}


int main(int argc, char **argv){
    ros::init(argc, argv, "squares_vel");
    ros::NodeHandle n;

    geometry_msgs::Twist vel;
    int linear_, angular_;
    double l_scale, a_scale;
    int state = 0;
    linear_ = 1;
    l_scale = 0.0;
    angular_ = 1;
    a_scale = 0.0;
     
    // vel.linear.x = linear_*l_scale;
    // vel.angular.z = angular_*a_scale;

    ros::Publisher vel_pub_ = n.advertise<geometry_msgs::Twist>("cmd_vel", 1, true);
    
    ros::Subscriber odom_init_sub_ = n.subscribe("/odom",10,odom_initCallback);
    geometry_msgs::Pose init_pose;
    init_pose.position.x = odom_.pose.pose.position.x;
    init_pose.position.y = odom_.pose.pose.position.y;
    init_pose.position.z = odom_.pose.pose.position.z;
    ros::Rate loop_rate(3); 

    while(ros::ok()){
                
        printf("Just showing the init pose\nx = %f\ny = %f\nz = %f\n",
                init_pose.position.x, init_pose.position.y, init_pose.position.z);        
 
        ros::Subscriber odom_sub_ = n.subscribe("/odom",10,odomCallback);
        geometry_msgs::Pose new_pose;
        new_pose.position.x = odom.pose.pose.position.x;
        new_pose.position.y = odom.pose.pose.position.y;
        new_pose.position.z = odom.pose.pose.position.z;
        printf("Just showing the new pose\nx = %f\ny = %f\nz = %f\n",
                new_pose.position.x, new_pose.position.y, new_pose.position.z);        
    
       
        if(fabs(new_pose.position.x - init_pose.position.x)<0.5){
            straight(vel);
        }

        if(fabs(new_pose.position.x - init_pose.position.x)>0.5){
            stop(vel);
        }        
        // printf("Here's linear.x = %f\n", vel.linear.x);
        // printf("Publishing Topics\n");
        vel_pub_.publish(vel);

        // ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
