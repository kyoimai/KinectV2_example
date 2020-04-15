#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"

using namespace glm;

class ofApp : public ofBaseApp{

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
    
//    kienct mesh
    ofxKinectV2 kinect;
    ofVboMesh mesh;
    ofEasyCam cam;
    
//    data from kinect;
    ofTexture texRGB;
    ofTexture texRGBRegistered;
    ofTexture texDepth;
    
//    gui
    ofxPanel gui;
    ofParameter<vec3> position;
    ofParameter<vec3> rotation;
    ofParameter<int> step;
    ofParameter<float> threshold;
    bool bGui = true;
};
