#!/usr/bin/env python
import rospy
from std_msgs.msg import Int16
#right encoder callback function
def right_callback(data):
    rospy.loginfo( "Right_Encoder %d", data.data)

#left encoder callback function 
def left_callback(data):
    rospy.loginfo( "Left_Encoder %d", data.data)

def encoder_function():

    # In ROS, nodes are uniquely named. If two nodes with the same
    rospy.init_node('encoder', anonymous=True)
    #subscribe the respective encoders
    rospy.Subscriber("/right/encoder", Int16, right_callback)
    rospy.Subscriber("/left/encoder", Int16, left_callback)
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    encoder_function()
