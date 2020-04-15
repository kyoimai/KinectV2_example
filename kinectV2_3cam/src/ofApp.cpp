#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofSetWindowTitle("KinectV2_cam_easing_system");
    
    kinect[0].open(serial0);
    kinect[1].open(serial1);
    kinect[2].open(serial2);
    
    cam.setTarget({0, 0, 0});
    
    kinectGui.setup("kinectParam");
    kinectGui.setPosition(230, 10);
    kinectGui.add(step.set("step", 2, 1, 20));
    kinectGui.add(bGrid.setup("grid", true));
    kinectGui.add(radius.set("kienctRadius", 200, 0, 2000));
    kinectGui.add(mesh_scale.set("mesh_scale", 300, 100, 500));
    kinectGui.add(kinectY.set("kinectYPosition", vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 300, 300)));
    kinectGui.add(cam_trans_per.set("cam_trans", 20, 10, 70));
    
    globalGui.setup("global_Pamareter");
    globalGui.add(birdView.setup("birdView", false));
    globalGui.add(sceneParam.set("sceneParam", 0, 0, 3));
    
    box.set(10);
    box1.set(10);
    box2.set(10);
}

//--------------------------------------------------------------
void ofApp::update(){
    
//    kinectCamTranslate
    kinectCam[0].setTarget(kinectTarget);
    kinectCam[0].setPosition(radius * cos(ofDegToRad(-90 + 180)), kinectY->x, radius * sin(ofDegToRad(-90 + 180)));
    kinectCam[1].setTarget(kinectTarget);
    kinectCam[1].setPosition(radius * cos(ofDegToRad(30 + 180)), kinectY->y, radius * sin(ofDegToRad(30 + 180)));
    kinectCam[2].setTarget(kinectTarget);
    kinectCam[2].setPosition(radius * cos(ofDegToRad(150 + 180)), kinectY->y, radius * sin(ofDegToRad(150 + 180)));

    if(birdView){
        cam.setTarget(kinectTarget);
        vec3 camDistance = aimCamPosition - nowCamPosition;
        nowCamPosition += camDistance / float(cam_trans_per);
        cam.setPosition(nowCamPosition);
    }
    
    set_kinect();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(birdView) cam_look.begin();
    if(!birdView) cam.begin();
    
    if(bGrid) ofDrawGrid(100.f);
    
    ofRectangle capture_size(0, 0, 19.2, 10.8);
    ofSetColor(255, 0, 0);
    kinectCam[0].drawFrustum(capture_size);
    ofSetColor(0, 255, 0);
    kinectCam[1].drawFrustum(capture_size);
    ofSetColor(0, 0, 255);
    kinectCam[2].drawFrustum(capture_size);
    
    ofSetColor(255);
    if(birdView) cam.drawFrustum();
    
    ofSetColor(255, 255, 255);
    ofDrawBox(0, 0, 0, 20);
    
    ofPushMatrix();
    ofTranslate(kinectCam[0].getPosition());
    ofRotateZDeg(kinectCam[0].getRollDeg());
    ofRotateYDeg(kinectCam[0].getHeadingDeg());
    ofRotateXDeg(kinectCam[0].getPitchDeg());
    box.draw();
    ofScale(-mesh_scale);
    mesh[0].draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(kinectCam[1].getPosition());
    ofRotateZDeg(kinectCam[1].getRollDeg());
    ofRotateYDeg(kinectCam[1].getHeadingDeg());
    ofRotateXDeg(kinectCam[1].getPitchDeg());
    box1.draw();
    ofScale(-mesh_scale);
    mesh[1].draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(kinectCam[2].getPosition());
    ofRotateZDeg(kinectCam[2].getRollDeg());
    ofRotateYDeg(kinectCam[2].getHeadingDeg());
    ofRotateXDeg(kinectCam[2].getPitchDeg());
    box2.draw();
    ofScale(-mesh_scale);
    mesh[2].draw();
    ofPopMatrix();
    
    if(birdView) cam_look.end();
    if(!birdView) cam.end();
    
    ofDisableDepthTest();
    globalGui.draw();
    kinectGui.draw();
    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '0':
            aimCamPosition = kinectCam[0].getPosition();
            break;
            
        case '1':
            aimCamPosition = kinectCam[1].getPosition();
            break;
            
        case '2':
            aimCamPosition = kinectCam[2].getPosition();
            break;
            
            break;
            
        default:
            break;
    }
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

//--------------------------------------------------------------
void ofApp::draw_box(){
    box.draw();
}

//--------------------------------------------------------------
void ofApp::set_kinect(){
// 3点情報と色情報取得
    int xNum = 0, yNum = 0;
    for(int d = 0; d < device; d++){
        for (int y = 0; y < kinect[d].getRegisteredPixels().getHeight(); y+=step){
            yNum++;
            for (int x = 0; x < kinect[d].getRegisteredPixels().getWidth(); x+=step){
                xNum++;
                float dist = kinect[d].getDistanceAt(x, y);
                if(dist < threshold){
                    mesh[d].addVertex(kinect[d].getWorldCoordinateAt(x ,y));
                    mesh[d].addColor(kinect[d].getPixels().getColor(x, y));
                    if (mesh[d].getVertices()[y * (xNum-1) + x].z > 0 && mesh[d].getVertices()[(y + 1) * (xNum-1) + x].z > 0 && mesh[d].getVertices()[(y + 1) * (xNum-1) + (x + 1)].z > 0) {
                        mesh[d].addIndex(y * (xNum-1) + x);
                        mesh[d].addIndex((y + 1) * (xNum-1) + x);
                        mesh[d].addIndex((y + 1) * (xNum-1) + (x + 1));
                    }
                    if (mesh[d].getVertices()[y * (xNum-1) + x].z > 0 && mesh[d].getVertices()[y * (xNum-1) + (x + 1)].z > 0 && mesh[d].getVertices()[(y + 1) * (xNum-1) + (x + 1)].z > 0) {
                        mesh[d].addIndex(y * (xNum-1) + x);
                        mesh[d].addIndex(y * (xNum-1) + (x + 1));
                        mesh[d].addIndex((y + 1) * (xNum-1) + (x + 1));
                        
                    }
                }
            }
        }
    }
}
