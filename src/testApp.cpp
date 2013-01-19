#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    setupOpenNI();
    
    //send all the joints positions for both the world and screen positions
    //ableton_OSCSender.setup(HOST,ABLETON_PORT,JOINT_TO_SEND_ALL_JOINTS,JOINT_TO_SEND_ALL_JOINTS);
    
    //send the head and left elbow just to the host and port.
    ableton_OSCSender.setup(HOST,PORT,JOINT_TO_SEND_HEAD|JOINT_TO_SEND_LEFT_ELBOW,JOINT_TO_SEND_NONE);
    
}


//--------------------------------------------------------------
void testApp::setupOpenNI()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
    
    // set properties for all user masks and point clouds
    openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    openNIDevice.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
}

//--------------------------------------------------------------
void testApp::update()
{
    openNIDevice.update();
    
    
    ableton_OSCSender.send(openNIDevice);
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    glScalef(0.25, 0.25, 0.25);

    // draw debug (ie., image, depth, skeleton)
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    ofPushMatrix();
    glScalef(0.25, 0.25, 0.25);

    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++)
    {
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        
        // draw the mask texture for this user
        user.drawMask();
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event)
{
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit()
{
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}



