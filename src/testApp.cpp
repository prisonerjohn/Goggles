#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    gui = new ofxUISuperCanvas("GOGGLES");
    gui->setName("GOGGLES");
    gui->addFPS();

    gui->addSpacer();
    gui->addLabel("LEFT EYE");
    gui->addIntSlider("LEFT DEVICE ID", 0, 5, 0);
    gui->addSlider("LEFT ROI X", 0, Eye::kGrabberWidth, &eyeLeft.roiX());
    gui->addSlider("LEFT ROI Y", 0, Eye::kGrabberHeight, &eyeLeft.roiY());
    gui->addSlider("LEFT ROI WIDTH", 0, Eye::kGrabberWidth, &eyeLeft.roiWidth());
    gui->addSlider("LEFT ROI HEIGHT", 0, Eye::kGrabberHeight, &eyeLeft.roiHeight());

    gui->addSpacer();
    gui->addLabel("RIGHT EYE");
    gui->addIntSlider("RIGHT DEVICE ID", 0, 5, 0);
    gui->addSlider("RIGHT ROI X", 0, Eye::kGrabberWidth, &eyeRight.roiX());
    gui->addSlider("RIGHT ROI Y", 0, Eye::kGrabberHeight, &eyeRight.roiY());
    gui->addSlider("RIGHT ROI WIDTH", 0, Eye::kGrabberWidth, &eyeRight.roiWidth());
    gui->addSlider("RIGHT ROI HEIGHT", 0, Eye::kGrabberHeight, &eyeRight.roiHeight());

    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    gui->loadSettings("settings/" + gui->getName() + ".xml");
    
    oculusRift.baseCamera = &baseCam;
    oculusRift.setup();
    
    baseCam.begin();
    baseCam.end();
}

//--------------------------------------------------------------
void testApp::exit()
{
    gui->saveSettings("settings/" + gui->getName() + ".xml");
    delete gui;
}

//--------------------------------------------------------------
void testApp::update()
{
    eyeLeft.update();
    eyeRight.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
    if (oculusRift.isSetup()) {
        oculusRift.beginLeftEye();
        {
            renderScene(eyeLeft);
        }
        oculusRift.endLeftEye();
        
        oculusRift.beginRightEye();
        {
            renderScene(eyeRight);
        }
        oculusRift.endRightEye();
        
        ofEnableDepthTest();
        {
            ofSetColor(ofColor::white);
            oculusRift.draw();
        }
        ofDisableDepthTest();
    }
    else {
        baseCam.begin();
        {
            renderScene(eyeLeft);
        }
        baseCam.end();
    }
    
//    eyeLeft.draw(0, 0);
//    eyeRight.draw(Eye::kGrabberWidth, 0);
    
//    float ratio = ofGetHeight() / grabberLeft.width;
//    
//    ofPushMatrix();
//    ofTranslate(grabberLeft.height * ratio, 0);
//    ofRotate(90, 0, 0, 1);
//    grabberLeft.draw(0, 0, grabberLeft.width * ratio, grabberLeft.height * ratio);
//    ofPopMatrix();
//    
//    ofPushMatrix();
//    ofTranslate(grabberLeft.height * ratio, 0);
//    ofTranslate(grabberRight.height * ratio, 0);
//    ofRotate(90, 0, 0, 1);
//    grabberRight.draw(0, 0, grabberLeft.width * ratio, grabberLeft.height * ratio);
//    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::renderScene(Eye &eye)
{
    ofSetColor(120);
	
	ofPushMatrix();
    ofRotate(90, 0, 0, -1);
    ofDrawGridPlane(500.0f, 40.0f, false );
	ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs& e)
{
    if (e.getName() == "LEFT DEVICE ID") {
        eyeLeft.setup(e.getSlider()->getScaledValue());
    }
    else if (e.getName() == "RIGHT DEVICE ID") {
        eyeRight.setup(e.getSlider()->getScaledValue());
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
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
