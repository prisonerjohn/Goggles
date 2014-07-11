#pragma once

#include "ofMain.h"
#include "ofxOculusRift.h"
#include "ofxUI.h"

#include "Eye.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
    void setup();
    void exit();

    void update();
    void draw();

    void guiEvent(ofxUIEventArgs& e);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxOculusRift oculusRift;

    ofxUISuperCanvas *gui;

    Eye eyeLeft;
    Eye eyeRight;
};
