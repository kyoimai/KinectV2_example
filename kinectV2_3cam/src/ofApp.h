#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"

#define serial0 "003962142147"
#define serial1 "002873142647"
#define serial2 ""
//serial0 -> centerPosition
//serial1 -> leftPosition
//serial2 -> rightPosition

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
    
//    device num
    static const int device = 3;
    
//    data from kinect
//    std::vector<std::shared_ptr<ofxKinectV2>> kinects;
//    std::vector<ofTexture> texRGB;
//    std::vector<ofTexture> texRGBRegistered;
//    std::vector<ofTexture> texDepth;
    
    
//    kinect
    void set_kinect();
    ofEasyCam cam_look;
    ofEasyCam cam;
    ofEasyCam kinectCam[3];
    int cam_number;
    vec3 kinectTarget = vec3(0, 0, 0);
    vec3 nowCamPosition;
    vec3 aimCamPosition;
    
    ofxKinectV2 kinect[device];
    ofVboMesh mesh[device];

    
//global parameter
    ofxPanel globalGui;
    ofxToggle bGrid;
    ofxToggle birdView;
    ofParameter<int> sceneParam;
    
//kinect parameter
    ofxPanel kinectGui;
    ofParameter<int> step;
    ofParameter<float> threshold;
    ofParameter<float> radius;
    ofParameter<float> mesh_scale;
    ofParameter<float> cam_trans_per;
    ofParameter<vec3> kinectY;
    
//挙動確認用
    ofBoxPrimitive box, box1, box2;
    void draw_box();
};
