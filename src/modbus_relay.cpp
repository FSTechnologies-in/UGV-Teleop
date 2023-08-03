#include <stdio.h>
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <iostream>
#include "modbus.cpp"
#include <unistd.h>
int count_1=0;
//int modbus();
//	RS485_Modbus_RTU test1(testDevParam);
	//getting modbus pointer variable for local access
	
void frontlightCallback(const std_msgs::Bool& msg)
{
	
    bool light_1=false;
     std_msgs::Bool value;
      light_1= msg.data;
     if(light_1==true)
     {
       count_1++;
     } 
     if(count_1==1 && light_1==true)
     {
      light_1=true;
      value.data=true;
      ROS_INFO("Front top Light :%d",light_1);
	    modbus(1,MOD8I8O_W_R_OUTPUT_BIT8,PIN_SET,3);

     }
     if(count_1==2 && light_1==true)
     {
       
       light_1=false;
        value.data=false;
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT8,PIN_CLR,3);

      ROS_INFO("Front top Light:%d",light_1);
      count_1=0;
     }

}
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */

	
  ros::init(argc, argv, "modbus_motor");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
ros::Rate loop_rate(10);
  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  ros::Subscriber front_top_light_sub = n.subscribe("btn1topic", 1000, frontlightCallback);
  //ros::Subscriber sub = n.subscribe("btn1topic", 1000, frontlightCallback);
  
  
	  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
 
  ros::spin();
 loop_rate.sleep();
  return 0;
}
