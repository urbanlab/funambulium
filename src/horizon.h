//
//  horizon.h
//  funambulus
//
//  Created by Benjamin Petit on 24/03/2017.
//
//

#ifndef horizon_h
#define horizon_h

#include "feathers.h"

class Horizon
{

public:    

    Horizon()
    {
        
    }
    
    void setup(string path,bool interactive = false)
    {
        _interactive = interactive;
        
        cout<<"\tHORIZON: "<<path+"/HORIZON.mp4"<<endl;
        _bg.load(path+"/HORIZON.mp4");
        
        if(_interactive)
            _bg.setLoopState(OF_LOOP_NONE);
        else
            _bg.setLoopState(OF_LOOP_NORMAL);
        
        _pos = 0.0;
    }
    
    void start()
    {
        _bg.play();
        _bg.setPosition(0.0);
        _bg.setPaused(false);
        _pos = 0.0;
    }
    
    void stop()
    {
        //_bg.stop();
        _bg.setPosition(0.0);
        _bg.setPaused(true);
        _pos = 0.0;
    }
    
    void update(float pos)
    {
        pos = ofClamp(pos,0.0,1.0);
        pos = ofMap(pos,S()._posIn,S()._posOut,0.0,1.0,true);
        
        if(pos > _pos)
            _pos = pos*(1-S()._smoothPos) + _pos * S()._smoothPos;
        
        if(_interactive)
        {
            if(_pos < _bg.getPosition())
                _bg.setPaused(true);
            else
                _bg.setPaused(false);
        }
        
        //_bg.setPosition(_pos);
        _bg.update();
    }
    
    void draw()
    {
        ofPushMatrix();
        
        ofTranslate(RES_X/2.0,RES_Y/2.0);
        ofRotateZ(90);
        ofTranslate(-RES_Y/2.0,-RES_X/2.0);
        
        _bg.draw(0,0,RES_Y,RES_X);
        
        ofPopMatrix();
    }
    
    void drawDebug()
    {
        ofSetColor(ofColor::blue);
        ofDrawRectangle(0,0,RES_X*_pos,10.0);
    }
    
public:
    
    bool _interactive;
    
    ofVideoPlayer _bg;
    
    float _pos;
};

#endif /* horizon_h */
