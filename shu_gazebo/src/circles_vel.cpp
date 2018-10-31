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

// #define VEL_MAX 0.3
// #define VEL_MIN -0.3

int main(int argc, char **argv){
    ros::init(argc, argv, "circles_vel");
    ros::NodeHandle n;

    geometry_msgs::Twist vel;
    int linear_, angular_;
    double l_scale, a_scale;
    // int check = 0;
    bool check = false;
    linear_ = 1;
    l_scale = 0.0;
    angular_ = 1;
    a_scale = 0.3;
     
    vel.linear.x = linear_*l_scale;
    vel.angular.z = angular_*a_scale;

    ros::Publisher vel_pub_ = n.advertise<geometry_msgs::Twist>("cmd_vel", 1, true);
    ros::Rate loop_rate(1);


    while(ros::ok()){

       if(vel.linear.x < 0.3  && check!=true){
            vel.linear.x += 0.1;
            printf("section1:vel_x = %f \n",vel.linear.x);
            if(vel.linear.x==0.3){
                check = true;
                printf("check mark true \n");
            }
        }

        if(vel.linear.x > -0.3 && check!=false){
            vel.linear.x -= 0.1;
            printf("section2: vel_x = %f \n",vel.linear.x);
            if(vel.linear.x==-0.3){
                check = false;
                printf("check mark false \n");
            }
        }

        
        vel_pub_.publish(vel);

        // ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
