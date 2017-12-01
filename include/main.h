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
#include <iterator>
#include <algorithm>
#include <iostream>
#include <stdio.h>

#ifndef MAIN_H
#define MAIN_H

using namespace std;

class Main
{
	public:
		Main(){
			robot_pub = nh.advertise<std_msgs::String>("write", 5); 
			new_vector_sub = nh.subscribe<v2I_communication::read_vector>("readVectornew", 5, &Main::new_vehicle_callback, this);
			done_vector_sub = nh.subscribe<v2I_communication::read_vector>("readVectordone", 5, &Main::done_vehicle_callback, this);
		}

/*******************
NEW_VEHICLE_CALLBACK
*******************/


		//[1, vID, current_location, desired_location, status]

		void new_vehicle_callback(const v2I_communication::read_vector::ConstPtr& msg){
			//sleep(1);
			cout << "past main_callback" << endl;
			cout << "size of vehicle is: " << vehicle.size() << endl;
			if (vehicle.size() == 0){
				sleep(1);
				cout << "past main_callback if statement" << endl;
				vehicle.resize(1);
				cout << "test 1" << endl;
				vehicle[0].set_vehicle_id(msg->data[1]);
				vehicle[0].set_current_location(msg->data[2]);
				vehicle[0].set_desired_location(msg->data[3]);
				vehicle[0].set_status(msg->data[4]);
				vehicle[0].set_priority(0);
				vehicle[0].open_all();
				vehicle[0].close_roads();
				checkingvector.resize(12);
				checkingvector = vehicle[0].get_road_status();
				for(t = 0; t < 12; t++){
					cout << checkingvector[t] << ",";
				}
				cout << endl;
				checkingvector.clear();
				cout << "test 2" << endl;
				to_vehicles.resize(5);
				to_vehicles[0] = 0;
				to_vehicles[1] = vehicle[0].get_vehicle_id();
				to_vehicles[2] = vehicle[0].get_current_location();
				to_vehicles[3] = vehicle[0].get_desired_location();
				to_vehicles[4] = 1;
				cout << "test 3" << endl;
				publish_to_vehicles();  //publishes string through xbee to all vehicles

			}
			
			else {	//check all vehicles on road and priority for matching closed roads. if match, vehicle must be added to priority list. if no match, vehicle can go.
				sleep(1);
				size = vehicle.size();
				vehicle.resize(size + 1);
				vehicle[size].set_vehicle_id(msg->data[1]);
				vehicle[size].set_current_location(msg->data[2]);
				vehicle[size].set_desired_location(msg->data[3]);
				vehicle[size].set_status(msg->data[4]);

				vehicle[size].open_all();
				cout<< "test 4" << endl;
				vehicle[size].close_roads();
				cout<< "test 5" << endl;
				go = true;
				checkingvector.resize(12);
				establishedvector.resize(12);
				checkingvector = vehicle[size].get_road_status();
				for(r = 0; r < 12; r++){
					cout << checkingvector[r] << ",";
				}
				cout << endl;
				for(j = 0; j < size; j++){
					establishedvector = vehicle[j].get_road_status();
					for(s = 0; s < 12; s++){
						cout << establishedvector[s] << ",";
					}
					cout << endl;
					for(k = 0; k < 12; k++){
						if( (checkingvector[k] == 1) && (establishedvector[k] == 1) ){
							go = false;
							
						}
					}		 
					establishedvector.clear();
				}
				checkingvector.clear();
				cout<< "test 6" << endl;
				
				/* 
				if go = true, it can be sent out without affecting any robots on the road or any in the priority queue
				if go = false, it has to be put at the end of the priority list 
				*/

				if(go == false){
					newpriority = get_highest_priority();
					vehicle[size].set_priority(newpriority);
					newpriority = 0;
					cout<< "test 7" << endl;
					cout << "The vehicle number : " << size << " : has a priority value of: " << vehicle[size].get_priority() << endl;

				}
				if(go == true){
					vehicle[size].set_priority(0);
					to_vehicles.clear();
					to_vehicles.resize(5);
					to_vehicles[0] = 0;
					to_vehicles[1] = vehicle[size].get_vehicle_id();
					to_vehicles[2] = vehicle[size].get_current_location();
					to_vehicles[3] = vehicle[size].get_desired_location();
					to_vehicles[4] = 1;
					cout << "---------------------------to_vehicles[] values----------------------------" << endl;
					for(x = 0; x < 5; x++){
						cout << to_vehicles[x] << ",";
					}
					cout << endl;
					cout << "---------------------------------------------------------------------------" << endl;

					publish_to_vehicles();  //publishes string through xbee to all vehicles
					//cout<< "test 8" << endl;
				}
			}
		}
/***************/


/********************
DONE_VEHICLE_CALLBACK
********************/

		void done_vehicle_callback(const v2I_communication::read_vector::ConstPtr& donemsg){
			sleep(1);
			object_id = donemsg->data[1];//changed donemsg.data[1]

			for(l = 0; l < size; l++){
				test_id = vehicle[l].get_vehicle_id(); //Here we are matching up the ROS's vehicle id's with the id from the done msg.
				if(test_id == object_id){
					object_num = l;
				}
			}
			cout << "object_num is: " << object_num << endl;
			vehicle[object_num].open_all();


			size = vehicle.size();
			car_in_waiting = false;
			for(w =0; w < size; w++){
				if(vehicle[w].get_priority() > 0){
					car_in_waiting = true;
				}
			}
			if(car_in_waiting == true){
				loop = true;
				while(loop == true){
					for(u =0; u < size; u++){
						checkingvector.clear();
						checkingvector = vehicle[u].get_road_status();
						for(v = 0; v < 12; v++){
							cout << checkingvector[v] << ",";
						}
						cout << endl;
					}



					go = true;
					cout<< "test 10" << endl;
	                                cout<< "in done vehicle callback function" << endl;

					//need to find object with priority number 1;
					for(m = 0; m < size; m++){
						if(vehicle[m].get_priority() == 1){
							priority_obj_num = m;
						}
					}

					//Here we are getting the road status for the next priority and comparing them to all the vehicles
					checkingvector = vehicle[priority_obj_num].get_road_status();
					cout << "priority 1 vehicle has a checking vector of: " << endl; //<< checkingvector[0] << endl;
					for(p = 0; p <12; p++){
						cout << checkingvector[p] << ",";
					}
					cout << endl;
	
					cout<< "test 11" << endl;
					cout<< "priority object number is " << priority_obj_num << endl;
					for(n = 0; n < size; n++){
						cout << "Currently checking vehicle[" << n <<"] for closed road matching" << endl;
						if(n != priority_obj_num){
							cout << "not referring to itself... check if on road..." << endl;
							if(vehicle[n].get_priority() == 0){
								cout << "Checking vehicle[" << n << "]'s road closures because it is on road..." << endl;
								establishedvector = vehicle[n].get_road_status();
								//cout << "established vector is: " << establishedvector << endl;
								cout << "established vector of: " << endl; //<< checkingvector[0] << endl;
								for(q = 0; q < 12; q++){
									cout << establishedvector[q] << ",";
								}
								cout << endl;
	//							for (q = establishedvector.begin(); q != establishedvector.end(); ++q)//
	//                               	  				std::cout << *q << ' ';//
	
	
								for(k = 0; k < 12; k++){
									if( (checkingvector[k] == 1) && (establishedvector[k] == 1) ){
										go = false;
										cout << "priority vehicle has a match and can not go yet...go is set to false..." << endl;
									}
								}
							}
						}
						else{
							cout << "priority_obj_num is matched... vehicle is referring to itself... do nothing" << endl;}
					establishedvector.clear();
					}
					checkingvector.clear();
					cout<< "test 12" << endl;
					cout << "status of go is: " << go << endl;
					//Here the state of 'go' was either changed to false or stayed true,
					//If true, we send this vehicle out, close its roads, and change all priority values -1, and recheck the priority list.
					//if false, close while loop, and do nothing.
	
					if(go == true){
						cout<< "test 12.1" << endl;
						//cin.ignore();
						vehicle[priority_obj_num].set_priority(0);
						//to_vehicles.clear();
						to_vehicles[0] = 0;
						to_vehicles[1] = vehicle[priority_obj_num].get_vehicle_id();
						to_vehicles[2] = vehicle[priority_obj_num].get_current_location();
						to_vehicles[3] = vehicle[priority_obj_num].get_desired_location();
						to_vehicles[4] = 1;
						publish_to_vehicles();  //publishes string through xbee to all vehicles
						//delay(10000);
						last = false;
						for(o = 0; o < size; o++){
							if(vehicle[o].get_priority() > 0){
								last = true;
								placeholder = vehicle[o].get_priority();
								placeholder = placeholder - 1;
								vehicle[o].set_priority(placeholder);						
							}
						}
						if(last == false){
							loop = false;
						}
						cout<< "test 13" << endl;
						//loop = false;///
					//cin.ignore();
					}
					else{
						loop = false;
						cout<< "test 14" << endl;
					}
				}
			}
			cout<< "exited done vehicle callback" << endl;
		}
	/*******************/
	
	
	
		int get_highest_priority(){
			priority = 0;
			for(int i = 0; i < size; i++){
				testpriority = vehicle[i].get_priority();
				if(testpriority >= priority){
					priority = testpriority + 1;
				}
			}

			return priority;
		}
 			


		


		void publish_to_vehicles(){
			//sleep(1);
			// Convert all but the last element to avoid a trailing ","
			cout << "size of to_vehicles[] is: " << to_vehicles.size() << endl;
			for(x = 0; x < 5; x++){
				cout << to_vehicles[x] << ",";
			}
			cout << endl;


			copy(to_vehicles.begin(), to_vehicles.end()-1, ostream_iterator<int>(output, ","));
		
			//Now add the last element with no delimiter
			output << to_vehicles.back();
			
			cout << "THIS IS PUBLISHING TO /WRITE: " << output.str() << endl;

			gomsg.data = output.str();
			output.str( string() );
			output.clear();
			
			
			//publish to "write" topic
			robot_pub.publish(gomsg);
			
			
		}

		void roads_on(){
			p1_2 = 0;
			p1_3 = 0;
			p1_4 = 0;
			p2_1 = 0;
			p2_3 = 0;
			p2_4 = 0;
			p3_1 = 0;
			p3_2 = 0;
			p3_4 = 0;
			p4_1 = 0;
			p4_2 = 0;
			p4_3 = 0;	
		}



	private:
		ros::NodeHandle nh;
		ros::Publisher robot_pub;
		ros::Subscriber new_vector_sub;
		ros::Subscriber done_vector_sub;
		vector<Robot> vehicle; 
		int size;
		int p1_2, p1_3, p1_4, p2_1, p2_3, p2_4, p3_1, p3_2, p3_4, p4_1, p4_2, p4_3;
		vector<int> to_vehicles;
		ostringstream output;
		std_msgs::String gomsg;
		v2I_communication::read_vector prioritylist;
		int newpriority;
		int priority;
		int i;
		int j;
		int k;
		int testpriority;
		bool go;
		vector<int> checkingvector, establishedvector;

		/********/
		int object_num;
		//vector<int> donemsg;
		int object_id;
		int test_id;
		int l, m, n, o, p, q, r, s, t, u, v, w, x;
		int priority_obj_num;
		bool loop;
		bool last;
		bool car_in_waiting;		
		int placeholder;
};
#endif
