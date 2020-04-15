#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableDepthTest();

//    kinect mesh
    kinect.open();
    
//    data from kinect

//    gui
    gui.setup("KinectParam");
    gui.setPosition(20, 30);
    gui.add(position.set("position", vec3(0., 0., 0.), vec3(-1000., -1000., -1000.), vec3(1000., 1000., 1000.)));
    gui.add(rotation.set("rotation", vec3(0., 0., 0.), vec3(-180., -180., -180.), vec3(180., 180., 180)));
    gui.add(step.set("step", 2, 1, 10));
    gui.add(threshold.set("threshold", 2., 0.1, 5.));
}

//--------------------------------------------------------------
void ofApp::update(){
    if (kinect.isFrameNew()){
        
//            get world color
        texRGB.loadData(kinect.getPixels());
        texRGBRegistered.loadData(kinect.getRegisteredPixels());
        texDepth.loadData(kinect.getDepthPixels());
        
//            clear mesh -> prevent too many mesh vertex
        mesh.clear();
        
        for (int x = 0; x < texRGBRegistered.getWidth(); x += step){
            for (int y = 0; y < texRGBRegistered.getHeight(); y += step){
                
                float dist = kinect.getDistanceAt(x, y);
                
                if(dist < threshold){
                    mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
                    mesh.addColor(kinect.getRegisteredPixels().getColor(x, y));
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    ofDrawGrid(300.f);
    
    ofPushMatrix();
    ofTranslate(position);
    ofRotateXDeg(rotation->x);
    ofRotateYDeg(rotation->y);
    ofRotateZDeg(rotation->z);
    ofScale(-500, -500, -500);
    mesh.draw();
    ofPopMatrix();
    
    cam.end();
    
    ofDisableDepthTest();
    if(bGui) gui.draw();
    ofDrawBitmapStringHighlight("key '1' draw Gui", 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
