/*
 * Created by Shuhei Kozasa 2018/10/30
 *
 * A very simple publisher. 
 *
 *
 *
 *
 *
 *
 *
 * 
 */

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <math.h>

#include <iostream>

int main(int argc, char **argv){
    ros::init(argc, argv, "circles_vel");
    ros::NodeHandle n;

    geometry_msgs::Twist vel;
    int linear_, angular_;
    double l_scale, a_scale;
    int check = 0;

    ros::Publisher vel_pub_ = n.advertise<geometry_msgs::Twist>("cmd_vel", 1, true);
    ros::Rate loop_rate(10);

    while(ros::ok()){
        linear_ = 1;
        l_scale = 0.2;
        angular_ = 1;
        a_scale = 0.6;
        
        vel.linear.x = linear_*l_scale;
        vel.angular.z = angular_*a_scale;
        if(vel.linear.x < 0.5 && check == 0){
            vel.linear.x += 0.1;
            vel_pub_.publish(vel);
            if(vel.linear.x==0.5){
                check = 1;
            }
        }
        if(vel.linear.x > -0.5 && vel.linear.x > 0.5){
            vel.linear.x -= 0.1;
            vel_pub_.publish(vel);
            if(vel.linear.x == -0.5){
                check = 0;
            }
        }


        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
