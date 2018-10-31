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
    // int check = 0;
    bool check = false;

    ros::Publisher vel_pub_ = n.advertise<geometry_msgs::Twist>("cmd_vel", 1, true);
    ros::Rate loop_rate(1);

    while(ros::ok()){
        linear_ = 1;
        l_scale = 0.1;
        angular_ = 1;
        a_scale = 0.3;
        
        vel.linear.x = linear_*l_scale;
        vel.angular.z = angular_*a_scale;

        if(vel.linear.x < 0.5 && check!=true){
            vel.linear.x += 0.1;
            if(vel.linear.x==0.5){
                check = true;
            }
        }
        if(vel.linear.x > -0.5 && check!=false){
            vel.linear.x -= 0.1;
            if(vel.linear.x==-0.5){
                check = false;
            }
        }

        vel_pub_.publish(vel);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
