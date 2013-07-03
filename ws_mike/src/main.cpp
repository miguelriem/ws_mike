#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include <ws_referee/custom.h>

//Global variable dsfsdf
std::string _name="mike";
ros::Publisher chatter_pub;

//void chatterCallback(const std_msgs::String::ConstPtr& msg_in)
void chatterCallback(const ws_referee::custom::ConstPtr& msg_in)
{
	//ROS_INFO("%s: heard: [%s]", _name.c_str(), msg_in->data.c_str());
	ROS_INFO("%s: Received msg",_name.c_str());

	//Publish new msg
	//std_msgs::String msg_out;
	ws_referee::custom msg_out;

	//msg_out.data = "hello world";
	msg_out.dist = 0.5;
	msg_out.sender = _name;
	msg_out.winner = "";
	chatter_pub.publish(msg_out);
	ROS_INFO("%s: will publish a message",_name.c_str());
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, _name);
	ros::NodeHandle n;
	//chatter_pub = n.advertise<std_msgs::String>("player_out", 1);
	chatter_pub = n.advertise<ws_referee::custom>("player_out", 1);

	ros::Subscriber sub = n.subscribe("player_in", 1, chatterCallback);
	ros::Rate loop_rate(2);

	ROS_INFO("%s: node started",_name.c_str());
	int count = 0;
	while (ros::ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}


	return 0;
}
