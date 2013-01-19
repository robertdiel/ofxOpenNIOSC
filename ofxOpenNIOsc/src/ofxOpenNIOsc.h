/*
 * ofxOpenNIOsc.h
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

#ifndef __ofxOpenNIOsc__h
#define __ofxOpenNIOsc__h

#include <iostream>
#include "ofxOsc.h"
#include "ofxOpenNI.h"



enum Joint_To_Send
{
    JOINT_TO_SEND_NONE                      = 0,
    JOINT_TO_SEND_TORSO                     = 1 << 0,
    JOINT_TO_SEND_NECK                      = 1 << 1,
    JOINT_TO_SEND_HEAD                      = 1 << 2,
    
    // left arm + shoulder
    JOINT_TO_SEND_LEFT_SHOULDER             = 1 << 3,
    JOINT_TO_SEND_LEFT_ELBOW                = 1 << 4,
    JOINT_TO_SEND_LEFT_HAND                 = 1 << 5,
    
    // right arm + shoulder
    JOINT_TO_SEND_RIGHT_SHOULDER            = 1 << 6,
    JOINT_TO_SEND_RIGHT_ELBOW               = 1 << 7,
    JOINT_TO_SEND_RIGHT_HAND                = 1 << 8,
    
    // left leg
    JOINT_TO_SEND_LEFT_HIP                  = 1 << 9,
    JOINT_TO_SEND_LEFT_KNEE                 = 1 << 10,
    JOINT_TO_SEND_LEFT_FOOT                 = 1 << 11,
    
    // right leg
    JOINT_TO_SEND_RIGHT_HIP                 = 1 << 12,
    JOINT_TO_SEND_RIGHT_KNEE                = 1 << 13,
    JOINT_TO_SEND_RIGHT_FOOT                = 1 << 14,
};


typedef uint16 Joints_To_Send_BitMask;

const Joints_To_Send_BitMask JOINT_TO_SEND_ALL_JOINTS = JOINT_TO_SEND_TORSO | JOINT_TO_SEND_NECK |
                                                        JOINT_TO_SEND_HEAD | JOINT_TO_SEND_LEFT_SHOULDER |
                                                        JOINT_TO_SEND_LEFT_ELBOW | JOINT_TO_SEND_LEFT_HAND|
                                                        JOINT_TO_SEND_RIGHT_SHOULDER | JOINT_TO_SEND_RIGHT_ELBOW|
                                                        JOINT_TO_SEND_RIGHT_HAND | JOINT_TO_SEND_LEFT_HIP |
                                                        JOINT_TO_SEND_LEFT_KNEE | JOINT_TO_SEND_LEFT_FOOT|
                                                        JOINT_TO_SEND_RIGHT_HIP | JOINT_TO_SEND_RIGHT_KNEE|
                                                        JOINT_TO_SEND_RIGHT_FOOT;

const string JointsOSCNameArray[] =
{
    "/torso",
    "/neck",
    "/head",
    "/leftshoulder",
    "/leftelbow",
    "/lefthand",
    "/rightshoulder",
    "/rightelbow",
    "/righthand",
    "/lefthip",
    "/leftknee",
    "/leftfoot",
    "/righthip",
    "/rightknee",
    "/rightfoot"
};

class ofxOpenNIOsc
{
    
private:
    Joints_To_Send_BitMask worldJointsToSend;
    Joints_To_Send_BitMask screenJointsToSend;
    ofxOscSender       sender;
    
    void sendOSCJoint(string name, int id, int x, int y, int z);
    void sendOSCData(ofxOpenNI& openNIDevice,bool worldPosition);
    
    string LOG_NAME;


public:
    ofxOpenNIOsc();
    ofxOpenNIOsc(string __host, uint16 __port,
                 Joints_To_Send_BitMask __worldJointsToSend = JOINT_TO_SEND_NONE,
                 Joints_To_Send_BitMask __screenJointsToSend = JOINT_TO_SEND_NONE );
    ~ofxOpenNIOsc();
    
    void setup(string __host, uint16 __port,
               Joints_To_Send_BitMask __worldJointsToSend = JOINT_TO_SEND_NONE,
               Joints_To_Send_BitMask __screenJointsToSend = JOINT_TO_SEND_NONE );
    void send(ofxOpenNI& openNIDevice);
    
    inline void setWorldJointsToSend(Joints_To_Send_BitMask __worldJointsToSend)
                                    { worldJointsToSend = __worldJointsToSend; }
    inline void setScreenJointsToSend(Joints_To_Send_BitMask __screenJointsToSend)
                                    { screenJointsToSend = __screenJointsToSend; }
    inline Joint getJointFromJointToSendBitMask(Joint_To_Send jts)
    {
        Joint retVal = JOINT_UNKOWN;
        switch (jts)
        {
            case JOINT_TO_SEND_NONE:
                retVal = JOINT_UNKOWN;
                break;
                
            case JOINT_TO_SEND_TORSO:
                retVal = JOINT_TORSO;
                break;
                
            case JOINT_TO_SEND_NECK:
                retVal = JOINT_NECK;
                break;
            case JOINT_TO_SEND_HEAD:
                retVal = JOINT_HEAD;
                break;
                
                // left arm + shoulder
            case JOINT_TO_SEND_LEFT_SHOULDER:
                retVal = JOINT_LEFT_SHOULDER;
                break;
            case JOINT_TO_SEND_LEFT_ELBOW:
                retVal = JOINT_LEFT_ELBOW;
                break;
            case JOINT_TO_SEND_LEFT_HAND:
                retVal = JOINT_LEFT_HAND;
                break;
                
                // right arm + shoulder
            case JOINT_TO_SEND_RIGHT_SHOULDER:
                retVal = JOINT_RIGHT_SHOULDER;
                break;
            case JOINT_TO_SEND_RIGHT_ELBOW:
                retVal = JOINT_RIGHT_ELBOW;
                break;
            case JOINT_TO_SEND_RIGHT_HAND:
                retVal = JOINT_RIGHT_HAND;
                break;
                
                // left leg
            case JOINT_TO_SEND_LEFT_HIP:
                retVal = JOINT_LEFT_HIP;
                break;
            case JOINT_TO_SEND_LEFT_KNEE:
                retVal = JOINT_LEFT_KNEE;
                break;
            case JOINT_TO_SEND_LEFT_FOOT:
                retVal = JOINT_LEFT_FOOT;
                break;
                
                
                // right leg
            case JOINT_TO_SEND_RIGHT_HIP:
                retVal = JOINT_RIGHT_HIP;
                break;
            case JOINT_TO_SEND_RIGHT_KNEE:
                retVal = JOINT_RIGHT_KNEE;
                break;
            case JOINT_TO_SEND_RIGHT_FOOT:
                retVal = JOINT_RIGHT_FOOT;
                break;
        }
        return retVal;
    }

    inline string getJointNameFromJointToSendBitMask(Joint_To_Send jts,bool worldPosition)
    {
        string retVal = "UNKNOWN";
        switch (jts)
        {
            case JOINT_TO_SEND_NONE:
                retVal = "UNKNOWN";
                break;
                
            case JOINT_TO_SEND_TORSO:
                retVal = (worldPosition == true) ? "/torso_world_pos" : "/torso_screen_pos";
                break;

            case JOINT_TO_SEND_NECK:
                retVal = (worldPosition == true) ? "/neck_world_pos" : "/neck_screen_pos";
                break;
            case JOINT_TO_SEND_HEAD:
                retVal = (worldPosition == true) ? "/head_world_pos" : "/head_screen_pos";
                break;
                
                // left arm + shoulder
            case JOINT_TO_SEND_LEFT_SHOULDER:
                retVal = (worldPosition == true) ? "/leftshoulder_world_pos" : "/torso_screen_pos";
                break;
            case JOINT_TO_SEND_LEFT_ELBOW:
                retVal = (worldPosition == true) ? "/leftelbow_world_pos" : "/leftelbow_screen_pos";
                break;
            case JOINT_TO_SEND_LEFT_HAND:
                retVal = (worldPosition == true) ? "/lefthand_world_pos" : "/lefthand_screen_pos";
                break;
                
                // right arm + shoulder
            case JOINT_TO_SEND_RIGHT_SHOULDER:
                retVal = (worldPosition == true) ? "/rightshoulder_world_pos" : "/rightshoulder_screen_pos";
                break;
            case JOINT_TO_SEND_RIGHT_ELBOW:
                retVal = (worldPosition == true) ? "/rightelbow_world_pos" : "/rightelbow_screen_pos";
                break;
            case JOINT_TO_SEND_RIGHT_HAND:
                retVal = (worldPosition == true) ? "/righthand_world_pos" : "/righthand_screen_pos";
                break;
                
                // left leg
            case JOINT_TO_SEND_LEFT_HIP:
                retVal = (worldPosition == true) ? "/lefthip_world_pos" : "/lefthip_screen_pos";
                break;
            case JOINT_TO_SEND_LEFT_KNEE:
                retVal = (worldPosition == true) ? "/leftknee_world_pos" : "/leftknee_screen_pos";
                break;
            case JOINT_TO_SEND_LEFT_FOOT:
                retVal = (worldPosition == true) ? "/leftfoot_world_pos" : "/leftfoot_screen_pos";
                break;

                
                // right leg
            case JOINT_TO_SEND_RIGHT_HIP:
                retVal = (worldPosition == true) ? "/righthip_world_pos" : "/righthip_screen_pos";
                break;
            case JOINT_TO_SEND_RIGHT_KNEE:
                retVal = (worldPosition == true) ? "/rightknee_world_pos" : "/rightknee_screen_pos";
                break;
            case JOINT_TO_SEND_RIGHT_FOOT:
                retVal = (worldPosition == true) ? "/rightfoot_world_pos" : "/rightfoot_screen_pos";
                break;
        }
        return retVal;
    }

};

#endif /* defined(__LightCubeExperimentalOpenNI__ofxOpenNIOsc__) */
