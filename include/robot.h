#pragma once
#ifndef ROBOT_H
#define ROBOT_H

using namespace std;

class Robot {

	public:
		Robot();

		~Robot();

		//Mutator Functions:
		void set_vehicle_id(int value){
			vehicle_id = value;
		}
		void set_current_location(int value){
			current_location = value;
		}
		void set_desired_location(int value){
			desired_location = value;
		}

		void set_priority(int value){
			priority = value;
		}

		void set_status(int value){
			status = value;
		}
/*		
		void set_closed_paths(vector<int> closevector){
			if(closevector[0] == 1){
				p1_2 = true;
			}
			if(closevector[1] == 1){
				p1_3 = true;
			}
			if(closevector[2] == 1){
				p1_4 = true;
			}
			if(closevector[3] == 1){
				p2_1 = true;
			}
			if(closevector[4] == 1){
				p2_3 = true;
			}
			if(closevector[5] == 1){
				p2_4 = true;
			}
			if(closevector[6] == 1){
				p3_1 = true;
			}
			if(closevector[7] == 1){
				p3_2 = true;
			}
			if(closevector[8] == 1){
				p3_4 = true;
			}
			if(closevector[9] == 1){
				p4_1 = true;
			}
			if(closevector[10] == 1){
				p4_2 = true;
			}
			if(closevector[11] == 1){
				p4_3 = true;
			}
		}
*/

		void open_all(){
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

		void close_1_2(){ //left turn
			p1_2 = 1;
			p2_3 = 1;
			p2_4 = 1;
			p3_1 = 1;
			p3_2 = 1;
			p3_4 = 1;
			p4_1 = 1;
			p4_2 = 1;
			p4_3 = 1;  //not necessary but just to be safe depending on the size of the intersection
		}

		void close_1_3(){ //straight through
			p1_3 = 1;
			p2_3 = 1;
			p2_4 = 1;
			p3_4 = 1;
			p4_1 = 1;
			p4_2 = 1;
			p4_3 = 1;
		}

		void close_1_4(){ //right turn
			p1_4 = 1;
			p2_3 = 1;  //not necessary but just to be safe depending on the size of the intersection
			p2_4 = 1;
			p3_4 = 1;
		}

		void close_2_1(){ //right turn
			p2_1 = 1;
			p3_1 = 1;
			p3_4 = 1;  //not necessary but just to be safe depending on the size of the intersection
			p4_1 = 1;
		}

		void close_2_3(){ //left turn
			p1_2 = 1;
			p1_3 = 1;
			p1_4 = 1;  //not necessary but just to be safe depending on the size of the intersection
			p2_3 = 1;
			p3_1 = 1;
			p3_4 = 1;
			p4_1 = 1;
			p4_2 = 1;
			p4_3 = 1;
		}

		void close_2_4(){ //straight through
			p1_2 = 1;
			p1_3 = 1;
			p1_4 = 1;
			p2_4 = 1;
			p3_1 = 1;
			p3_4 = 1;
			p4_1 = 1;
		}

		void close_3_1(){ //straight through
			p1_2 = 1;
			p2_1 = 1;
			p2_3 = 1;
			p2_4 = 1;		
			p3_1 = 1;
			p4_1 = 1;
			p4_2 = 1;
		}

		void close_3_2(){ //right turn
			p1_2 = 1;
			p3_2 = 1;
			p4_1 = 1;  //not necessary but just to be safe depending on the size of the intersection
			p4_2 = 1;
		}
		
		void close_3_4(){ //left turn
			p1_2 = 1;
			p1_3 = 1;
			p1_4 = 1;
			p2_1 = 1; //not necessary but just to be safe depending on the size of the intersection
			p2_3 = 1;
			p2_4 = 1;
			p3_4 = 1;
			p4_1 = 1;
			p4_2 = 1;
		}

		void close_4_1(){ //left turn
			p1_2 = 1;
			p1_3 = 1;
			p2_1 = 1;
			p2_3 = 1;
			p2_4 = 1;
			p3_1 = 1;
			p3_2 = 1;  //not necessary but just to be safe depending on the size of the intersection
			p3_4 = 1;
			p4_1 = 1;		
		}

		void close_4_2(){ //straight through
			p1_2 = 1;
			p1_3 = 1;
			p2_3 = 1;
			p3_1 = 1;
			p3_2 = 1;
			p3_4 = 1;
			p4_2 = 1;
		}

		void close_4_3(){ //right turn
			p1_2 = 1;  //not necessary but just to be safe depending on the size of the intersection			
			p1_3 = 1;
			p2_3 = 1;
			p4_3 = 1;
		}

		void close_roads(){
			int cp = current_location;
			int dp = desired_location;
			if(cp == 1 && dp == 2){
				close_1_2();
				cout << "close_1_2 called" << endl;
			}

			if(cp == 1 && dp == 3){
				close_1_3();
				cout << "close_1_3 called" << endl;
			}

			if(cp == 1 && dp == 4){
				close_1_4();
				cout << "close_1_4 called" << endl;
			}

			if(cp == 2 && dp == 1){
				close_2_1();
				cout << "close_2_1 called" << endl;
			}

			if(cp == 2 && dp == 3){
				close_2_3();
				cout << "close_2_3 called" << endl;
			}

			if(cp == 2 && dp == 4){
				close_2_4();
				cout << "close_2_4 called" << endl;
			}

			if(cp == 3 && dp == 1){
				close_3_1();
				cout << "close_3_1 called" << endl;
			}

			if(cp == 3 && dp == 2){
				close_3_2();
				cout << "close_3_2 called" << endl;
			}

			if(cp == 3 && dp == 4){
				close_3_4();
				cout << "close_3_4 called" << endl;
			}

			if(cp == 4 && dp == 1){
				close_4_1();
				cout << "close_4_1 called" << endl;
			}

			if(cp == 4 && dp == 2){
				close_4_2();
				cout << "close_4_2 called" << endl;
			}

			if(cp == 4 && dp == 3){
				close_4_3();
				cout << "close_4_3 called" << endl;
			}

		}


		//Accessor Functions:
		int get_vehicle_id(){
			return vehicle_id;
		}
		int get_current_location(){
			return current_location;
		}
		int get_desired_location(){
			return desired_location;
		}
		int get_priority(){
			return priority;
		}
		vector<int> get_road_status(){
			road_status.resize(12);
			road_status[0] = p1_2;
			road_status[1] = p1_3;
			road_status[2] = p1_4;
			road_status[3] = p2_1;
			road_status[4] = p2_3;
			road_status[5] = p2_4;
			road_status[6] = p3_1;
			road_status[7] = p3_2;
			road_status[8] = p3_4;
			road_status[9] = p4_1;
			road_status[10] = p4_2;
			road_status[11] = p4_3;
			return road_status;
		}




	private:
		int vehicle_id;
		int current_location;
		int desired_location;
		int status;
		int priority;
		int p1_2, p1_3, p1_4, p2_1, p2_3, p2_4, p3_1, p3_2, p3_4, p4_1, p4_2, p4_3;
		int i;
		vector<int> road_status;




};
Robot::Robot(){
}

Robot::~Robot(){
}

#endif 
