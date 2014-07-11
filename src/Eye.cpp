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
    
//    mPostProcessing.createPass<BleachBypassPass>()->setEnabled(false);
//    mPostProcessing.createPass<BloomPass>()->setEnabled(false);
    mPostProcessing.createPass<ContrastPass>()->setEnabled(false);
    mPostProcessing.createPass<ConvolutionPass>()->setEnabled(false);
//    mPostProcessing.createPass<DofAltPass>()->setEnabled(false);
//    mPostProcessing.createPass<DofPass>()->setEnabled(false);
//    mPostProcessing.createPass<EdgePass>()->setEnabled(false);
    mPostProcessing.createPass<FakeSSSPass>()->setEnabled(false);
//    mPostProcessing<FxaaPass>()->setEnabled(false);
//    mPostProcessing.createPass<GodRaysPass>()->setEnabled(false);
    mPostProcessing.createPass<HorizontalTiltShifPass>()->setEnabled(false);
//    mPostProcessing<KaleidoscopePass>()->setEnabled(false);
//    mPostProcessing.createPass<LimbDarkeningPass>()->setEnabled(false);
//    mPostProcessing.createPass<LUTPass>()->setEnabled(false);
    mPostProcessing.createPass<NoiseWarpPass>()->setEnabled(false);
    mPostProcessing.createPass<PixelatePass>()->setEnabled(false);
    mPostProcessing.createPass<RGBShiftPass>()->setEnabled(false);
    mPostProcessing.createPass<RimHighlightingPass>()->setEnabled(false);
//    mPostProcessing.createPass<SSAOPass>()->setEnabled(false);
    mPostProcessing.createPass<ToonPass>()->setEnabled(false);
    mPostProcessing.createPass<VerticalTiltShifPass>()->setEnabled(false);
    mPostProcessing.createPass<ZoomBlurPass>()->setEnabled(false);
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
    
    if (mPostProcessing.getWidth() != mGrabber.getWidth() || mPostProcessing.getHeight() != mGrabber.getHeight()) {
        mPostProcessing.init(mGrabber.getWidth(), mGrabber.getHeight());
    }
    
    mPostProcessing.begin();
    {
        ofSetColor(ofColor::white);
        mGrabber.draw(0, 0);
    }
    mPostProcessing.end(false);
}

//--------------------------------------------------------------
void Eye::draw(int x, int y , int width, int height)
{
    if (!mGrabber.isInitialized()) return;
    
    ofSetColor(ofColor::white);
    mPostProcessing.getProcessedTextureReference().drawSubsection(x, y, width, height,
                                                                  mROI.x, mROI.y, mROI.width, mROI.height);
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

//--------------------------------------------------------------
ofxPostProcessing& Eye::postProcessing()
{
    return mPostProcessing;
}
