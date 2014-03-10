//
//  Eye.h
//  Goggles
//
//  Created by Elie Zananiri on 2014-03-09.
//
//

#pragma once

#include "ofMain.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class Eye
{
public:
    Eye();
    ~Eye();
    bool setup(int deviceID);
    
    void update();
    void draw(int x, int y, int width = kGrabberWidth, int height = kGrabberHeight);
    
    float& roiX();
    float& roiY();
    float& roiWidth();
    float& roiHeight();
    
    static int kGrabberWidth;
    static int kGrabberHeight;

protected:
    ofVideoGrabber mGrabber;
    int mDeviceID;
    
    ofRectangle mROI;
};

