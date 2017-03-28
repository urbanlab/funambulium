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
    #ifdef DEBUG
    ofSetFullscreen(false);
    ofSetWindowShape(1280, 400);
    #else
    ofSetFullscreen(true);
    ofSetWindowShape(1280*2, 800);
    #endif
    
    _auReceiver.connect(AU_OSC_PORT);
    //ofxAddAugmentaListeners(this);
    
    _floor.setup(ofPoint(0.0,0.0), ofPoint(0.5,1.0), ofPoint(RES_X*2,RES_Y));
    _wall.setup(ofPoint(0.5,0.0), ofPoint(0.5,1.0), ofPoint(RES_X*2,RES_Y));
    _floor._warper.load("quadwarpfloor.xml");
    _wall._warper.load("quadwarpwall.xml");
    
    S().setup();

    _scenarii.setup();

    _fboEffect.allocate(S()._xRes,S()._yRes,GL_RGBA);
    _effect.setup();
    _effect.setTexture(_fboEffect.getTexture());
    
    gui.setup();
    S().setupGui();
    _effect.setupGui();
    _scenarii.setupGui();
    gui.loadFromXML();
    gui.setDefaultKeys(true);
    
    #ifndef DEBUG
    ofHideCursor();
    //CGDisplayHideCursor(NULL);
    #endif
}

//--------------------------------------------------------------
void ofApp::exit()
{
    _floor._warper.save("quadwarpfloor.xml");
    _wall._warper.save("quadwarpwall.xml");
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Get the person data
    _people = _auReceiver.getPeople();
    
    _scenarii.update(_people);
    
    ofEnableAlphaBlending();
 
    if(_scenarii._scenarii[_scenarii._currentScenario]._hasEffect)
        _fboEffect.begin();
    else
        _floor.begin();
    
    ofClear(0);
    ofSetColor(255);
    
    _scenarii.drawFloor();
    
    if(S()._debug)
    {
        ofSetColor(ofColor::red);
        for (auto p : _people)
        {
            ofDrawCircle(p->centroid.x*S()._xRes, p->centroid.y*S()._yRes, 15);
        }
    }
    
    if(_scenarii._scenarii[_scenarii._currentScenario]._hasEffect)
        _fboEffect.end();
    else
        _floor.end();
    
    if(_scenarii._scenarii[_scenarii._currentScenario]._hasEffect)
    {
        _effect.setTexture(_fboEffect.getTexture());
        _effect.update(_people);
        
        _floor.begin();
        _effect.draw();
        //_fboEffect.draw(0,0,S()._xRes,S()._yRes);
        _floor.end();
    }
    
    _wall.begin();
    
    ofSetColor(255);
    
    _scenarii.drawWall();
    
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
    
    if(S()._warped)
    {
#ifndef DEBUG
    _floor._fbo.draw(0.0,0.0,1280.0*2.0,800.0);
    _wall._fbo.draw(1280.0,0.0,1280.0*2.0,800.0);
#else
    _floor.draw();
    _wall.draw();
#endif
    }
    else
    {
#ifndef DEBUG
        _floor._fbo.drawUnwarped(0.0,0.0,1280.0*2.0,800.0);
        _wall._fbo.drawUnwarped(1280.0,0.0,1280.0*2.0,800.0);
#else
        _floor.drawUnwarped();
        _wall.drawUnwarped();
#endif
    }
    
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
    if(key == 's')
        _scenarii.start();
    if(key == 'r')
        _scenarii.restart();
    if(key == 'n')
        _scenarii.next();
    
    if(key == 'f')
        ofToggleFullscreen();
    
    if(key == 'd')
    {
        S()._debug = !S()._debug;
        
        if(S()._warped)
        {
            if(S()._debug)
            {
                _floor._warper.show();
                _wall._warper.hide();
            }
            else
            {
                _floor._warper.hide();
                _wall._warper.hide();
            }
        }
    }
    
    if(key == 'w')
    {
        if(_floor._warper.isShowing())
        {
            _floor._warper.hide();
            _wall._warper.show();
        }
        else
        {
            _floor._warper.show();
            _wall._warper.hide();
        }
    }
    
    if(key == 'R')
    {
        _floor._warper.reset();
        _wall._warper.reset();
    }
    
    if(key == 'W')
    {
        S()._warped = !S()._warped;
        
        if(S()._warped)
        {
            if(S()._debug)
            {
                _floor._warper.show();
                _wall._warper.hide();
            }
            else
            {
                _floor._warper.hide();
                _wall._warper.hide();
            }
        }
    }
    
    
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
