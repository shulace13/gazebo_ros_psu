/*
 * This file has been created by Shuhei Kozasa
 * Following the tutorial at
 * www.theconstructsim.com/create-a-ros-sensor-plugin-for-gazebo/
 *
 * There are some places I modified since it didn't work in my env
 * Ubuntu 16.04
 * ROS kinetic
 * gazebo 7.6?
 * 
 */

#include <gazebo/common/Plugin.hh>
#include <ros/ros.h>

#include "gazebo_light_sensor_plugin/light_sensor_plugin.h"

#include <string>

#include <gazebo/sensors/Sensor.hh>
#include <gazebo/sensors/CameraSensor.hh>
#include <gazebo/sensors/SensorTypes.hh>

#include <sensor_msgs/Illuminance.h>

namespace gazebo
{
    // Register this plugin with the simulator
    GZ_REGISTER_SENSOR_PLUGIN(GazeboRosLight)


    //////////////////////////////////////////
    // Constructor
    GazeboRosLight::GazeboRosLight():
        _nh("light_sensor_plugin"),
        _fov(6),
        _range(10)
    {
        _sensorPublisher = _nh.advertise<sensor_msgs::Illuminance>("lightSensor", 1);
    }

    //////////////////////////////////////////
    // Destructor
    GazeboRosLight::~GazeboRosLight()
    {
        ROS_DEBUG_STREAM_NAMED("camera", "Unloaded");
    }

    void GazeboRosLight::Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf)
    {
        // Make sure the ROS node for Gazebo has already been initialized
        if(!ros::isInitialized())
        {
            ROS_FATAL_STREAM("A ROSnode for Gazebo has not been initialized, unable to load plugin. \n Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package. \n");
                return;
        }

        CameraPlugin::Load(_parent, _sdf);
        // copying from CameraPlugin into GazeboRosCameraUtils
        this->parentSensor_ = this->parentSensor;
        this->width_ = this->width;
        this->height_ = this->height;
        this->depth_ = this->depth;
        this->format_ = this->format;
        this->camera_ = this->camera;

        GazeboRosCameraUtils::Load(_parent, _sdf);
    }

    //////////////////////////////////////////
    // Update thecontroller
    void GazeboRosLight::OnNewFrame(const unsigned char *_image,
            unsigned int _width, unsigned int _height, unsigned int _depth,
            const std::string &_format)
    {
        static int seq=0;
        // this->sensor_update_time_ = this->parentSensor_->GetLastUpdateTime();
        this->sensor_update_time_ = this->parentSensor_->LastUpdateTime();

        if(!this->parentSensor->IsActive())
        {
            if((*this->image_connect_count_) > 0 )
                //do this first so there's chance for sensor to run once after activated
                this ->parentSensor->SetActive(true);
        }else{
            if((*this->image_connect_count_) > 0 )
            {
                common::Time cur_time = this->world_->GetSimTime();
                if(cur_time - this->last_update_time_ > this->update_period_)
                {
                    this->PutCameraData(_image);
                    this->PublishCameraInfo();
                    this->last_update_time_ = cur_time;

                    sensor_msgs::Illuminance msg;
                    msg.header.stamp = ros::Time::now();
                    msg.header.frame_id = "";
                    msg.header.seq = seq;

                    int startingPix = _width * ((int)(_height/2) - (int)(_fov/2)) 
                                                                    - (int)(_fov/2);
                    double illum = 0.0;
                    for(int i=0;i<_fov;++i)
                    {
                    int index = startingPix + i*_width;
                    for(int j=0;j<_fov;++j)
                        illum += _image[index+j];
                    }

                    msg.illuminance = illum/(_fov*_fov);
                    msg.variance = 0.0;

                    _sensorPublisher.publish(msg);

                    seq++;
                }
            }
        }
    }
}
