#pragma once
#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <v2I_communication/read_vector.h>
#include <robot.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#ifndef CONVERSION_H
#define CONVERSION_H

using namespace std;

class Conversion
{
	public:
		Conversion(){
			newvector_pub = nh.advertise<v2I_communication::read_vector>("readVectornew", 5);
			donevector_pub = nh.advertise<v2I_communication::read_vector>("readVectordone", 5);
			read_sub = nh.subscribe<std_msgs::String>("read", 5, &Conversion::read_callback, this);
		}

		void read_callback(const std_msgs::String::ConstPtr& msg){
			vect.clear();
			vect.resize(0);
			request = msg->data;
			stringstream ss(request);
			while (ss >> i)
			{
				vect.push_back(i);
        			if (ss.peek() == ',')
				{
            				ss.ignore();
				}
			}
			if(vect[0] == 1 && vect[4] == 1)
			{
				vectormsg.data = vect;
				donevector_pub.publish(vectormsg);
			}

			if(vect[0] == 1 && vect[4] == 0)
			{
				vectormsg.data = vect;
				newvector_pub.publish(vectormsg);
			}
		}

	private:
		ros::NodeHandle nh;
		ros::Publisher newvector_pub;
		ros::Publisher donevector_pub;
		ros::Subscriber read_sub;
		v2I_communication::read_vector vectormsg;
		vector<int> vect;
		string request;
		int i;
};
#endif
