#include <conversion.h>

int main (int argc, char** argv)
{
	ros::init(argc, argv, "vector_conversion_node");
	Conversion conversion;


    	v2I_communication::read_vector vectormsg;

	while(ros::ok())
	{
		ros::spin();
	}
	ros::shutdown();		
	return 0;
}   

