//
//  floor.h
//  funambulus
//
//  Created by Benjamin Petit on 24/03/2017.
//
//

#ifndef floor_h
#define floor_h

#include "ofxBounce.h"
#include "ofxRipples.h"

class Base
{

public:
    
    Base()
    {
        
    }
    
    void setup()
    {
        
    }
    
    void update()
    {
    }
    
    void draw()
    {
        
    }
    
    void drawDebug()
    {
        
    }
    
public:
    
};

class BaseIn : public Base
{
    
public:
    
    BaseIn()
    {
        
    }
    
    void setup()
    {
        
    }
    
    void update()
    {
    }
    
    void draw()
    {
        
    }
    
    void drawDebug()
    {
        
    }
    
public:
    
};

class BaseOut : public Base
{
    
public:
    
    BaseOut()
    {
        
    }
    
    void setup()
    {
        
    }
    
    void update()
    {
    }
    
    void draw()
    {
        
    }
    
    void drawDebug()
    {
        
    }
    
public:
    
};

class Path
{
    
public:
    
    Path()
    {
        
    }
    
    void setup()
    {
        
    }
    
    void update()
    {
    }
    
    void draw()
    {
        
    }
    
    void drawDebug()
    {
        
    }
    
public:
    
};

class Aura
{
    
public:
    
    Aura()
    {
        
    }
    
    void setup()
    {
        
    }
    
    void update()
    {
    }
    
    void draw()
    {
        
    }
    
    void drawDebug()
    {
        
    }
    
public:
    
};

class Floor
{
    
public:
            
    Floor()
    {
        
    }
    
    void setup(string path, bool video = false)
    {
        _video = video;
        
        if(_video)
        {
            cout<<"\tFLOOR: "<<path+"/EARTH.mp4"<<endl;
            _bgV.load(path+"/EARTH.mp4");
        }
        else
        {
            cout<<"\tFLOOR: "<<path+"/EARTH.png"<<endl;
            _bgI.load(path+"/EARTH.png");
        }
        _pos = 0.0;
    }
    
    void start()
    {
        if(_video)
            _bgV.play();
        _pos = 0.0;
    }
    
    void stop()
    {
        if(_video)
            _bgV.stop();
        _pos = 0.0;
    }
    
    void update(float pos)
    {
        pos = ofClamp(pos,0.0,1.0);
        
        if(pos > _pos)
            _pos = pos*(1-S()._smoothPos) + _pos * S()._smoothPos;
        
        if(_video)
        {
            if(_pos < _bgV.getPosition())
                _bgV.setPaused(true);
            else
                _bgV.setPaused(false);
            
            
            //_bgV.setPosition(_pos);
            _bgV.update();
        }
    }
    
    void draw()
    {
        ofPushMatrix();
        
        if(_video)
        {
            ofTranslate(RES_X/2.0,RES_Y/2.0);
            ofRotateZ(90);
            ofTranslate(-RES_Y/2.0,-RES_X/2.0);
        
            _bgV.draw(0,0,RES_Y,RES_X);
        }
        else
        {
            _bgI.draw(0,0,RES_Y,RES_X);
        }
        
        ofPopMatrix();
    }
    
    void drawDebug()
    {
        ofSetColor(ofColor::blue);
        ofDrawRectangle(0,0,RES_X*_pos,10.0);
    }
    
public:
    
    bool _video;
    
    ofVideoPlayer _bgV;
    ofImage _bgI;
    
    float _pos;
};

#endif /* floor_h */
