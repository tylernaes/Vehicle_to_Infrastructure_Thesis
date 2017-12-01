/**/
#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

serial::Serial ser;

void write_callback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO_STREAM("Writing to serial port" << msg->data);
    ser.write(msg->data);
}

int main (int argc, char** argv){
    ros::init(argc, argv, "sample_base_test_node");
    ros::NodeHandle nh;

    ros::Subscriber read_sub = nh.subscribe("read", 1000, write_callback);
    ros::Publisher write_pub = nh.advertise<std_msgs::String>("write", 1000);



    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }

    ros::Rate loop_rate(5);
    while(ros::ok()){

        ros::spinOnce();

        if(ser.available()){
            ROS_INFO_STREAM("Reading from serial port");
            std_msgs::String result;
            result.data = ser.read(ser.available());
	    
            read_pub.publish(result);
        }
        loop_rate.sleep();

    }
}

