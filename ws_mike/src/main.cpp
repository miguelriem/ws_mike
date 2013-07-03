#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include <ws_referee/custom.h>
#include <visualization_msgs/Marker.h>

//Global variable 
std::string _name="mike";
ros::Publisher chatter_pub;
ros::Publisher marker_pub;
double _pos_x;
double _pos_y;

void chatterCallback(const ws_referee::custom::ConstPtr& msg_in)
{
	ROS_INFO("%s: Received msg with dist=%f",_name.c_str(), msg_in->dist);
	_pos_x += msg_in->dist;

	//Publish new msg
	ws_referee::custom msg_out;


	msg_out.dist = 0.5;
	msg_out.sender = _name;
	msg_out.winner = "";
	chatter_pub.publish(msg_out);
	ROS_INFO("%s: I am at %f.  will publish a message",_name.c_str(), _pos_x);

	visualization_msgs::Marker marker;
	marker.header.frame_id = "world";
	marker.header.stamp = ros::Time();
	marker.ns = "";
	marker.id = 0;
	marker.type = visualization_msgs::Marker::SPHERE;
	marker.action = visualization_msgs::Marker::ADD;
	marker.pose.position.x = _pos_x;
	marker.pose.position.y = _pos_y;
	marker.pose.position.z = 0;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = 0.0;
	marker.pose.orientation.w = 1.0;
	marker.scale.x = 0.3;
	marker.scale.y = 0.3;
	marker.scale.z = 0.3;
	marker.color.a = 1.0;
	marker.color.r = 1.0;
	marker.color.g = 0.0;
	marker.color.b = 0.0;
	marker_pub.publish( marker );

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, _name);
	ros::NodeHandle n;
	chatter_pub = n.advertise<ws_referee::custom>("player_out", 1);
	marker_pub = n.advertise<visualization_msgs::Marker>("mike_marker", 1);

	_pos_x = 0;
	_pos_y = 1; //to be read from a param

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
