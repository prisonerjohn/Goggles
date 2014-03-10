#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    grabberLeft.setDeviceID(1);
    grabberLeft.initGrabber(640, 360);

    grabberRight.setDeviceID(2);
    grabberRight.initGrabber(640, 360);
}

//--------------------------------------------------------------
void testApp::update(){
    grabberLeft.update();
    grabberRight.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    float ratio = ofGetHeight() / grabberLeft.width;
    
    ofPushMatrix();
    ofTranslate(grabberLeft.height * ratio, 0);
    ofRotate(90, 0, 0, 1);
    grabberLeft.draw(0, 0, grabberLeft.width * ratio, grabberLeft.height * ratio);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(grabberLeft.height * ratio, 0);
    ofTranslate(grabberRight.height * ratio, 0);
    ofRotate(90, 0, 0, 1);
    grabberRight.draw(0, 0, grabberLeft.width * ratio, grabberLeft.height * ratio);
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
