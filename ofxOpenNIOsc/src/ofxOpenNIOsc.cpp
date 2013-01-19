/*
 * ofxOpenNIOsc.cpp
 *
 * Copyright 2013 (c) Robert Diel 
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "ofxOpenNIOsc.h"

ofxOpenNIOsc::ofxOpenNIOsc()
{
    LOG_NAME = "ofxOpenNIOsc";
}

ofxOpenNIOsc::ofxOpenNIOsc(string __host, uint16 __port,
                           Joints_To_Send_BitMask __worldJointsToSend,
                           Joints_To_Send_BitMask __screenJointsToSend )
{
    LOG_NAME = "ofxOpenNIOsc";

    setup(__host,__port,__worldJointsToSend,__screenJointsToSend);
}

void ofxOpenNIOsc::setup(string __host, uint16 __port,
                        Joints_To_Send_BitMask __worldJointsToSend,
                        Joints_To_Send_BitMask __screenJointsToSend )
{
    ofLogNotice(LOG_NAME) << "sending messages on port " << __port;
    sender.setup( __host, __port );
    
    worldJointsToSend  = __worldJointsToSend;
    screenJointsToSend = __screenJointsToSend;
}

void ofxOpenNIOsc::sendOSCJoint(string name, int id, int x, int y, int z)
{
    if(!(x == 0 && y == 0 && z == 0))
    {
        ofxOscMessage       jointOsc;
        
        jointOsc.setAddress(name);
        jointOsc.addFloatArg(x);
        jointOsc.addFloatArg(y);
        jointOsc.addFloatArg(z);
        sender.sendMessage(jointOsc);
        
        //UNComment if you want to blow out all the messages that you are sending.
        ofLogVerbose(LOG_NAME) << name << ": "<< x << "," << y << "," << z;
        
    }
}
void ofxOpenNIOsc::send(ofxOpenNI& openNIDevice)
{
    if ( openNIDevice.getNumTrackedUsers() != 0)
    {
        if(worldJointsToSend != JOINT_TO_SEND_NONE)
        {
            sendOSCData(openNIDevice, true);
        }
        if(screenJointsToSend != JOINT_TO_SEND_NONE)
        {
            sendOSCData(openNIDevice, false);
        }
    }
}

void ofxOpenNIOsc::sendOSCData(ofxOpenNI& openNIDevice, bool worldPosition)
{
    Joints_To_Send_BitMask bitmask = (worldPosition == true) ? worldJointsToSend : screenJointsToSend;
    
    for (uint16 bit = 1; bitmask >= bit; bit *= 2)
    {
        if (bitmask & bit)
        {
            //if(openNIDevice.)
            Joint whichJoint = getJointFromJointToSendBitMask((Joint_To_Send)bit);
            ofxOpenNIUser & trackedUser = openNIDevice.getTrackedUser(0);
            
            ofxOpenNIJoint& whichNIJoint = trackedUser.getJoint(whichJoint);
            ofPoint whichNIJointPoint = (worldPosition == true) ? whichNIJoint.getWorldPosition() : whichNIJoint.getProjectivePosition();
            
            sendOSCJoint(getJointNameFromJointToSendBitMask((Joint_To_Send)bit,worldPosition), 1, whichNIJointPoint.x, whichNIJointPoint.y, whichNIJointPoint.z);
        }
    }
}

ofxOpenNIOsc::~ofxOpenNIOsc()
{
    
}