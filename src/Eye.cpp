//
//  Eye.cpp
//  Goggles
//
//  Created by Elie Zananiri on 2014-03-09.
//
//

#include "Eye.h"

//--------------------------------------------------------------
int Eye::kGrabberWidth  = 640;
int Eye::kGrabberHeight = 360;

//--------------------------------------------------------------
Eye::Eye()
{
    mDeviceID = -1;
    mROI.set(0, 0, kGrabberWidth, kGrabberHeight);
    
    mOverlayZ = -150.0f;
    mRotation = 0;
    bFlip = false;
    
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
    mPostProcessing.setFlip(bFlip);
    
    beginOverlay();
    mPostProcessing.begin();
    {
        ofSetColor(ofColor::white);
        mGrabber.draw(0, 0);
    }
    mPostProcessing.end();
    endOverlay();
}

//--------------------------------------------------------------
void Eye::draw()
{
    if (!mGrabber.isInitialized()) return;
    
    ofPushMatrix();
    mOverlayTarget.getTextureReference().bind();
    {
        ofRotate(mRotation, 0, 0, 1);
        
        mOverlayMesh.draw();
    }
    mOverlayTarget.getTextureReference().unbind();
    ofPopMatrix();
}

//--------------------------------------------------------------
void Eye::debug(int x, int y , float scale)
{
    if (!mGrabber.isInitialized()) return;
    
    ofPushStyle();
    ofPushMatrix();
    {
        ofTranslate(x, y);
        ofScale(scale, scale);
        
        ofSetColor(ofColor::white);
        mGrabber.draw(0, 0);
    
        ofSetColor(ofColor::red);
        ofNoFill();
        ofRect(mROI);
    }
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void Eye::beginOverlay()
{
	if (mOverlayTarget.getWidth() != mGrabber.getWidth() || mOverlayTarget.getHeight() != mGrabber.getHeight()) {
		mOverlayTarget.allocate(mGrabber.getWidth(), mGrabber.getHeight(), GL_RGBA, 4);
	}
	
	mOverlayMesh.clear();
	ofRectangle overlayrect = ofRectangle(mROI.width * -0.5f, mROI.height * -0.5f, mROI.width, mROI.height);
	mOverlayMesh.addVertex(ofVec3f(overlayrect.getMinX(), overlayrect.getMinY(), mOverlayZ));
	mOverlayMesh.addVertex(ofVec3f(overlayrect.getMaxX(), overlayrect.getMinY(), mOverlayZ));
	mOverlayMesh.addVertex(ofVec3f(overlayrect.getMinX(), overlayrect.getMaxY(), mOverlayZ));
	mOverlayMesh.addVertex(ofVec3f(overlayrect.getMaxX(), overlayrect.getMaxY(), mOverlayZ));
    
	mOverlayMesh.addTexCoord(ofVec2f(mROI.x, mROI.y + mROI.height));
	mOverlayMesh.addTexCoord(ofVec2f(mROI.x + mROI.width, mROI.y + mROI.height));
	mOverlayMesh.addTexCoord(ofVec2f(mROI.x, mROI.y));
	mOverlayMesh.addTexCoord(ofVec2f(mROI.x + mROI.width, mROI.y));
	
	mOverlayMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	
	mOverlayTarget.begin();
    ofClear(0, 0);
	
    ofPushView();
    ofPushMatrix();
}

//--------------------------------------------------------------
void Eye::endOverlay()
{
    ofPopMatrix();
    ofPopView();
    mOverlayTarget.end();
}
