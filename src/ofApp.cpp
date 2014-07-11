#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofVideoGrabber grabber;
    vector<ofVideoDevice> devices = grabber.listDevices();
    for (int i = 0; i < devices.size(); i++) {
        cout << i << ": " << devices[i].deviceName << " // " << devices[i].hardwareName << endl;
    }
    
    oculusRift.setup();
    
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
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofPushMatrix();
    ofTranslate(ofGetWidth(), 0);
    ofRotate(90, 0, 0, 1);
//    ofTranslate(0, ofGetHeight());
//    ofRotate(-90, 0, 0, 1);
    {
//        postProcessing.begin();
        eyeLeft.draw(0, 0, ofGetHeight(), ofGetWidth() * 0.5f);
//        postProcessing.end();
//        ofTranslate(0, ofGetWidth() * 0.5f);
//        postProcessing.begin();
        eyeRight.draw(0, ofGetWidth() * 0.5f, ofGetHeight(), ofGetWidth() * 0.5f);
//        postProcessing.end();
    }
    ofPopMatrix();
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
    else {
        // Make sure all render passes are identical for both eyes.
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
