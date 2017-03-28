//
//  floor.h
//  funambulus
//
//  Created by Benjamin Petit on 24/03/2017.
//
//

#ifndef floor_h
#define floor_h

#include "ofxMovieClip.h"

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
        
        _pathOn.loadAndCreateSequence(path+"/PATHON","PATHON");
        _pathOff.loadAndCreateSequence(path+"/PATHOFF","PATHOFF");
        _hasPath = (_pathOn.assetCollectionSize>0 && _pathOff.assetCollectionSize>0);
        
        if(_hasPath)
        {
            _clipPathOn.init(&_pathOn,0.3);
            _clipPathOff.init(&_pathOff,0.3);
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
    
    void update(float pos, bool someoneIn = false)
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
        
        //_someoneIn = someoneIn;
        
        if(someoneIn && pos > S()._posIn + S()._sizeInOut && pos < S()._posOut - S()._sizeInOut)
            _someoneIn = true;
        else
            _someoneIn = false;
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
            _bgI.draw(0,0,RES_X,RES_Y);
        }
        
        ofPopMatrix();
        
        if(_hasPath)
        {
            float x = S()._posIn * S()._xRes;// + 0.5 * S()._sizeInOut * S()._yRes;
            float y = 0.0;
            float w = S()._posOut * S()._xRes - x;// - 0.5 * S()._sizeInOut * S()._yRes;
            float h = S()._yRes;
            
            _clipPathOff.drawFrame(x,y,w,h);
            
            if(_someoneIn)
                _clipPathOn.drawFrame(x,y,w,h);
        }
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
    
    ofxTextureImageSequenceLoader _pathOff;
    ofxTextureImageSequenceLoader _pathOn;
    
    ofxTextureMovieClip _clipPathOff;
    ofxTextureMovieClip _clipPathOn;
    
    bool _hasPath;
    
    float _pos;
    bool _someoneIn;
};

#endif /* floor_h */
