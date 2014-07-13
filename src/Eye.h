//
//  Eye.h
//  Goggles
//
//  Created by Elie Zananiri on 2014-03-09.
//
//

#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class Eye
{
public:
    Eye();
    ~Eye();
    bool setup(int deviceID);
    
    void update();
    void draw();
    void debug(int x, int y, float scale = 1.0f);
    
    float& roiX() { return mROI.x; }
    float& roiY() { return mROI.y; }
    float& roiWidth() { return mROI.width; }
    float& roiHeight() { return mROI.height; }
    
    void setOverlayZ(float overlayZ) { mOverlayZ = overlayZ; }
    float& overlayZ() { return mOverlayZ; }
    ofMesh& overlayMesh() { return mOverlayMesh; }
    ofFbo& overlayTarget() { return mOverlayTarget; }
    
    ofxPostProcessing& postProcessing() { return mPostProcessing; }
    
    static int kGrabberWidth;
    static int kGrabberHeight;

protected:
    ofVideoGrabber mGrabber;
    int mDeviceID;
    ofRectangle mROI;
    
    void beginOverlay();
    void endOverlay();
    float mOverlayZ;
    ofMesh mOverlayMesh;
    ofFbo mOverlayTarget;
    
    ofxPostProcessing mPostProcessing;
};

