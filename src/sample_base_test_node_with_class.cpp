#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

serial::Serial ser;

class SubscribeAndPublish
{
public:
    SubscribeAndPublish()
    {
	write_pub = nh.advertise<std_msgs::String>("write", 1000);
	read_sub = nh.subscribe("read", 1000, read_callback);
    }

    void read_callback(const std_msgs::String::ConstPtr& msg)
    {
        ROS_INFO_STREAM("New request: [%s]" << msg->data);
	data = msg->data
	std_msgs::String priority;
	write_pub.publish(priority);
    }   

private:
    ros::NodeHandle nh;
    ros::Publisher write_pub;
    ros::Subscriber read_sub;
    string data;
}

int main (int argc, char** argv){
    ros::init(argc, argv, "sample_base_test_node_with_class");
    SubscribeAndPublish object;

    ros::Rate loop_rate(5);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();}
}

