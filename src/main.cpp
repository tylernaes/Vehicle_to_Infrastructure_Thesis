#include <main.h>

int main (int argc, char** argv)
{
	ros::init(argc, argv, "main_node");
	Main main;
	while(ros::ok())
	{
		ros::spin();
	}
	ros::shutdown();		
	return 0;
}   
