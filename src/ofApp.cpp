//
//  window.h
//  funambulus
//
//  Created by Benjamin Petit on 23/03/2017.
//
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    _auReceiver.connect(AU_OSC_PORT);
    //ofxAddAugmentaListeners(this);
    
    _floor.setup(ofPoint(0.0,0.0), ofPoint(0.5,1.0), ofPoint(1280*2,768));
    _wall.setup(ofPoint(0.5,0.0), ofPoint(0.5,1.0), ofPoint(1280*2,768));
    
    _floor.update();
    _wall.update();
    
    S().setup();
    
    gui.setup();
    S().setupGui();
    gui.loadFromXML();
    gui.setDefaultKeys(true);
    
    #ifndef DEBUG
    ofHideCursor();
    //CGDisplayHideCursor(NULL);
    #endif
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Get the person data
    _people = _auReceiver.getPeople();
    
    ofEnableAlphaBlending();
 
    _floor.begin();
    
    ofSetColor(255);
    
    if(S()._debug)
    {
        ofSetColor(ofColor::red);
        for (auto p : _people)
        {
            ofDrawCircle(p->centroid.x*1280.0, p->centroid.y*800.0, 15);
        }
    }
    
    _floor.end();
    
    _wall.begin();
    
    ofSetColor(255);
    
    if(S()._debug)
    {
        if(S()._debug)
        {
            ofSetColor(ofColor::red);
            for (auto p : _people)
            {
                ofDrawCircle(1280.0/2.0,800.0/2.0,ofMap(p->centroid.x,0.0,1.0,0.0,800.0/2.0));
            }
        }
    }
    
    _wall.end();
    
    ofDisableAlphaBlending();

#ifndef DEBUG
    if(gui.isOn())
    {
        ofShowCursor();
        //CGDisplayShowCursor(NULL);
    }
    else
    {
        if(ofGetFrameNum()%3600 == 0)
        {
            ofSetFullscreen(true);
            ofHideCursor();
            //CGDisplayHideCursor(NULL);
        }
    }
#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofEnableAlphaBlending();
    ofClear(0);
    
    ofSetColor(255);
    
    
#ifndef DEBUG
    _floor._fbo.draw(0.0,0.0,1280.0*2.0,800.0);
    _wall._fbo.draw(1280.0,0.0,1280.0*2.0,800.0);
#else
    _floor.draw();
    _wall.draw();
#endif
    
    if(S()._debug)
    {
        _floor.drawDebug();
        _wall.drawDebug();
    }

    ofDisableAlphaBlending();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    S().keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    _floor.update();
    _wall.update();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
