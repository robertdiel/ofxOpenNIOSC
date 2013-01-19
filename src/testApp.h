#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenNI.h"
#include "ofxOpenNIOsc.h"

#define PORT 12345
#define HOST "localhost"


class testApp : public ofBaseApp
{
    
private:
    ofxOpenNIOsc ableton_OSCSender;
    void setupOpenNI();
    
public:
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
        
};

#endif
