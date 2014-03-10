//
//  Eye.cpp
//  Goggles
//
//  Created by Elie Zananiri on 2014-03-09.
//
//

#include "Eye.h"

int Eye::kGrabberWidth  = 640;
int Eye::kGrabberHeight = 360;

//--------------------------------------------------------------
Eye::Eye()
{
    mDeviceID = -1;
    mROI.set(0, 0, kGrabberWidth, kGrabberHeight);
}

//--------------------------------------------------------------
Eye::~Eye()
{
    mGrabber.close();
}

//--------------------------------------------------------------
bool Eye::setup(int deviceID)
{
    if (deviceID == mDeviceID) return false;
    
    mDeviceID = deviceID;
    if (mGrabber.isInitialized()) {
        mGrabber.close();
    }
    mGrabber.setDeviceID(mDeviceID);
    return mGrabber.initGrabber(kGrabberWidth, kGrabberHeight);
}

//--------------------------------------------------------------
void Eye::update()
{
    if (!mGrabber.isInitialized()) return;
    
    mGrabber.update();
}

//--------------------------------------------------------------
void Eye::draw(int x, int y , int width, int height)
{
    if (!mGrabber.isInitialized()) return;

    ofSetColor(ofColor::white);
    mGrabber.getTextureReference().drawSubsection(x, y, width, height, mROI.x, mROI.y, mROI.width, mROI.height);
//    mGrabber.draw(x, y, width, height);
}

//--------------------------------------------------------------
float& Eye::roiX()
{
    return mROI.x;
}

//--------------------------------------------------------------
float& Eye::roiY()
{
    return mROI.y;
}

//--------------------------------------------------------------
float& Eye::roiWidth()
{
    return mROI.width;
}

//--------------------------------------------------------------
float& Eye::roiHeight()
{
    return mROI.height;
}
