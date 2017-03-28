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
#include "window.h"

#include "kid.h"
#include "scenarii.h"

#include "effect.h"

#define DEBUG

class ofApp : public ofBaseApp
{
	public:
		void setup();
        void exit();
		void update();
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
};
