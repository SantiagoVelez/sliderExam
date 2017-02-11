#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxPd.h"

using namespace pd;

class ofApp : public ofBaseApp, public PdReceiver{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxUISuperCanvas *gui;
    void exit();
    void guiEvent(ofxUIEventArgs &e);
    void playTone(int pitch);
    void audioReceived(float * input, int bufferSize, int nChannels);
    void audioRequested(float * output, int bufferSize, int nChannels);
    
    float value = 0.5;
    
    ofxPd pd;
    Patch patch;
    float frec;
    int val;
};
