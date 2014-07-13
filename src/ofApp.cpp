#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofVideoGrabber grabber;
    vector<ofVideoDevice> devices = grabber.listDevices();
    for (int i = 0; i < devices.size(); i++) {
        cout << i << ": " << devices[i].deviceName << " // " << devices[i].hardwareName << endl;
    }
    
    oculusRift.baseCamera = &baseCam;
    oculusRift.setup();
    
    baseCam.begin();
    baseCam.end();
    
    bDebug = false;
    
    gui = new ofxUISuperCanvas("GOGGLES");
    gui->setName("GOGGLES");
    gui->addFPS();
    gui->addToggle("DEBUG", &bDebug);

    gui->addSpacer();
    gui->addLabel("LEFT EYE");
    gui->addIntSlider("LEFT DEVICE ID", 0, 5, 0);
    gui->addSlider("LEFT ROI X", 0, Eye::kGrabberWidth, &eyeLeft.roiX());
    gui->addSlider("LEFT ROI Y", 0, Eye::kGrabberHeight, &eyeLeft.roiY());
    gui->addSlider("LEFT ROI WIDTH", 0, Eye::kGrabberWidth, &eyeLeft.roiWidth());
    gui->addSlider("LEFT ROI HEIGHT", 0, Eye::kGrabberHeight, &eyeLeft.roiHeight());
    gui->addIntSlider("LEFT ROTATION", 0, 359, &eyeLeft.rotation());
    gui->addToggle("LEFT FLIP", &eyeLeft.flip());

    gui->addSpacer();
    gui->addLabel("RIGHT EYE");
    gui->addIntSlider("RIGHT DEVICE ID", 0, 5, 0);
    gui->addSlider("RIGHT ROI X", 0, Eye::kGrabberWidth, &eyeRight.roiX());
    gui->addSlider("RIGHT ROI Y", 0, Eye::kGrabberHeight, &eyeRight.roiY());
    gui->addSlider("RIGHT ROI WIDTH", 0, Eye::kGrabberWidth, &eyeRight.roiWidth());
    gui->addSlider("RIGHT ROI HEIGHT", 0, Eye::kGrabberHeight, &eyeRight.roiHeight());
    
    gui->addIntSlider("RIGHT ROTATION", 0, 359, &eyeRight.rotation());
    gui->addToggle("RIGHT FLIP", &eyeRight.flip());

    gui->addSpacer();
    gui->addLabel("OCULUS RIFT");
    gui->addSlider("OVERLAY Z", -200, 0, &eyeLeft.overlayZ());
    
    gui->addSpacer();
    gui->addLabel("POST PROCESSING");
    for (int i = 0; i < eyeLeft.postProcessing().getPasses().size(); i++) {
        gui->addToggle(ofToUpper(eyeLeft.postProcessing()[i]->getName()), &eyeLeft.postProcessing()[i]->getEnabledRef());
    }

    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
    gui->loadSettings("settings/" + gui->getName() + ".xml");
}

//--------------------------------------------------------------
void ofApp::exit()
{
    gui->saveSettings("settings/" + gui->getName() + ".xml");
    delete gui;
}

//--------------------------------------------------------------
void ofApp::update()
{
    eyeLeft.update();
    eyeRight.update();
    
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
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255);

    oculusRift.draw();
    
    if (bDebug) {
        ofSetColor(255);
        eyeLeft.debug(ofGetWidth() - Eye::kGrabberWidth, 0, 0.5f);
        eyeRight.debug(ofGetWidth() - Eye::kGrabberWidth * 0.5f, 0, 0.5f);
    }
}

//--------------------------------------------------------------
void ofApp::renderScene(Eye& eye)
{
    // Render some debug stuff.
    ofDrawAxis(100);
    
    ofPushMatrix();
    {
        ofRotate(90, 0, 0, -1);
        ofDrawGridPlane(500.0f, 40.0f, false);
    }
	ofPopMatrix();
    
    // Render the overlay
    ofPushStyle();
    ofPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    {
        ofTranslate(baseCam.getPosition());
        ofMatrix4x4 baseRotation;
        baseRotation.makeRotationMatrix(baseCam.getOrientationQuat());
        ofMultMatrix(oculusRift.getOrientationMat() * baseRotation);
        
        eye.draw();
    }
    glPopAttrib();
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs& e)
{
    if (e.getName() == "LEFT DEVICE ID") {
        ofxUIIntSlider *intSlider = (ofxUIIntSlider *)e.widget;
        eyeLeft.setup(intSlider->getValue());
    }
    else if (e.getName() == "RIGHT DEVICE ID") {
        ofxUIIntSlider *intSlider = (ofxUIIntSlider *)e.widget;
        eyeRight.setup(intSlider->getValue());
    }
    else if (e.getName() == "OVERLAY Z") {
        // Copy value to right eye.
        eyeRight.setOverlayZ(eyeLeft.overlayZ());
    }
    else {
        // Copy values to right eye.
        for (int i = 0; i < eyeLeft.postProcessing().getPasses().size(); i++) {
            eyeRight.postProcessing()[i]->setEnabled(eyeLeft.postProcessing()[i]->getEnabled());
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'f') {
        ofToggleFullscreen();
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
