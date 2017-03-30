//
//  window.h
//  funambulus
//
//  Created by Benjamin Petit on 23/03/2017.
//
//

#pragma once

#include "ofMain.h"

#include "ofxAugmenta.h"
#define AU_OSC_PORT 12000

#include "settings.h"
#include "remote.h"
#include "window.h"

#include "kid.h"
#include "scenarii.h"

#include "effect.h"

#include "ofxOsc.h"

#define PORT_IN 12011

#define IP_OUT "192.168.71.125"
#define PORT_OUT 12012

#define DEBUG

class ofApp : public ofBaseApp
{
	public:
		void setup();
        void exit();
		void update();
        void oscRemote();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        Augmenta::Receiver _auReceiver;
        vector<Augmenta::Person*> _people;
    
        WWindow _floor;
        WWindow _wall;
    
        RippleEffect _effect;
        ofFbo _fboEffect;
    
        Kid _kid;
        Scenarii _scenarii;
    
        //OSC REMOTE
        ofxOscReceiver _receiver;
        ofxOscSender _sender;
};
