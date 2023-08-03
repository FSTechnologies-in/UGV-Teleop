#include <stdio.h>
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <iostream>
#include "modbus.cpp"
#include <unistd.h>
int brake_success=1;
long long forward_interval=0;
long long brake_interval=0;
long long reverse_interval=0;
int  stop_flag=4;
int BRAKE_APPLY_flag=0;
 
/* Limit switch callback function
   Message type -> Boolean
*/
void  callback_limitswitch(const std_msgs::Bool& msg)
{
  /* Disengage the Forward and reverse brake motion for Relay number 7 and 8 */
  modbus(1,MOD8I8O_W_R_OUTPUT_BIT7,PIN_CLR,1);
  modbus(1,MOD8I8O_W_R_OUTPUT_BIT8,PIN_CLR,1);
  BRAKE_APPLY_flag=msg.data;// Limit switch state assign global variable to access main function
  ROS_INFO("Limit Switch Pressed");
  ROS_INFO("%d",BRAKE_APPLY_flag);
  stop_flag=1;
}
/* Limit switch callback function
   Message type -> Boolean
*/
void  brake_callback(const std_msgs::Bool& msg)
  {
    printf("Brake Applied\n\r");
	/* Engage the Ring Red light for Relay Number 4*/
     modbus(1,MOD8I8O_W_R_OUTPUT_BIT4,PIN_SET,1);
    
   brake_success=msg.data;// Brake state assign global variable to access main function
  ROS_INFO("%d", brake_success);
  stop_flag=0;
 
}
int main(int argc, char **argv)
{
  /*
   * The ros::init() function needs to see argc and argv so that it can perform
   */

  
  ros::init(argc, argv, "brake_node");

  /*
   * NodeHandle is the main access point to communications with the ROS system.
   */
  ros::NodeHandle n;
ros::Rate loop_rate(1);
  /*
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   */
  ros::Subscriber brake_vehicle = n.subscribe("/brake/limit_switch", 1, callback_limitswitch);
  ros::Subscriber brake_joystick = n.subscribe("/brake/joystick", 1000, brake_callback);
  
  
   
 
  while(ros::ok())
  {
 /* Once brake callback function is called if condition is execute */
  if( brake_success)
  {
   
    if(stop_flag==0)
    {
		/* Enage Forward break -> Relay Number 7
		   Disengage Reverse Break -> Relay Number 8*/
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT7,PIN_SET,1);
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT8,PIN_CLR,1);
      //sleep(1);
      ROS_INFO("Break on");
      stop_flag=1;
    }
    if(stop_flag==1)
    {
      /* Wait for Some amount of time for Break holding*/
    forward_interval++;
    if(forward_interval>100000000||BRAKE_APPLY_flag)
    {
      //sleep(1);
      ROS_INFO("Break hold");
      BRAKE_APPLY_flag=0;
	  /* Disengage Forward break -> Relay Number 7
		 Disengage Reverse Break -> Relay Number 8*/
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT7,PIN_CLR,1);
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT8,PIN_CLR,1);
      forward_interval=0;
       brake_interval=0;
       reverse_interval=0;
      stop_flag=2;
    }
    }
    if(stop_flag==2)
    {
     brake_interval++;
	 /* Wait for Some amount of time for Break Reverse*/
    if(brake_interval>10000000)
    {
      //sleep(1);
      ROS_INFO("Break rev");
	  /* Disengage Forward break -> Relay Number 7
		 Engage Reverse Break -> Relay Number 8*/
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT7,PIN_CLR,1);
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT8,PIN_SET,1);
       forward_interval=0;
       brake_interval=0;
       reverse_interval=0;
      stop_flag=3;
    }
    }
    if(stop_flag==3)
    {
     reverse_interval++;
	 /* Wait for Some amount of time for Break Stop*/
    if(reverse_interval>10000000)
    {
      ROS_INFO("Break Stops");
	  /* Disengage Forward break -> Relay Number 7
		 Disengage Reverse Break -> Relay Number 8*/
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT7,PIN_CLR,1);
      modbus(1,MOD8I8O_W_R_OUTPUT_BIT8,PIN_CLR,1);
       forward_interval=0;
       brake_interval=0;
       reverse_interval=0;
      stop_flag=4;
	  /* Disengage the Ring Red light for Relay Number 4*/
       modbus(1,MOD8I8O_W_R_OUTPUT_BIT4,PIN_CLR,1);
       brake_success=0;
    }
    }
  }
  /*
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
   ros::spinOnce();
  }
  
    
}
