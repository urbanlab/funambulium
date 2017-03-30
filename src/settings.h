//
//  settings.h
//  funambulus
//
//  Created by Benjamin Petit on 23/03/2017.
//
//

#ifndef settings_h
#define settings_h

#include "ofxSimpleGuiToo.h"

#include "ofxMovieClip.h"

#define RES_X 1280
#define RES_Y 800

class Settings
{
    
public:
    
    Settings()
    {
    }
    
    void setup()
    {
        _debug = false;
        _warped = false;
        
        _xRes = RES_X;
        _yRes = RES_Y;
        
        _inOn.loadAndCreateSequence("INON","INON");
        _inOff.loadAndCreateSequence("INOFF","INOFF");
        _outOn.loadAndCreateSequence("OUTON","OUTON");
        _outOff.loadAndCreateSequence("OUTOFF","OUTOFF");
        
        _clipInOn.init(&_inOn,0.3);
        _clipInOff.init(&_inOff,0.3);
        _clipOutOn.init(&_outOn,0.3);
        _clipOutOff.init(&_outOff,0.3);
    }
    
    void setupGui()
    {
        gui.addTitle("Settings");
        gui.addSlider("SmoothPos",_smoothPos,0.0,1.0);
        gui.addSlider("PosIn",_posIn,0.0,1.0);
        gui.addSlider("PosOut",_posOut,0.0,1.0);
        gui.addSlider("SizeInOut",_sizeInOut,0.0,1.0);
    }
    
    void update(vector<Augmenta::Person*>& people)
    {
        _someoneInIn = false;
        _someoneInOut = false;
        
        for(auto & p : people)
        {
            if(ofDist(p->centroid.x,p->centroid.y,_posIn,0.5) < _sizeInOut*0.6)
            {
                _someoneInIn = true;
            }
            
            if(ofDist(p->centroid.x,p->centroid.y,_posOut,0.5) < _sizeInOut*0.6)
            {
                _someoneInOut = true;
            }
        }
    }
    
    void drawInOut()
    {
        float s = _sizeInOut*_yRes;
        float xIn = _posIn*_xRes - s*0.5;
        float xOut = _posOut*_xRes - s*0.5;
        float y = 0.5*_yRes - s*0.5;
        
        if(_someoneInIn)
            _clipInOn.drawFrame(xIn,y,s,s);
        else
            _clipInOff.drawFrame(xIn,y,s,s);
            
        if(_someoneInOut)
            _clipOutOn.drawFrame(xOut,y,s,s);
        else
            _clipOutOff.drawFrame(xOut,y,s,s);
    }
    
    void drawDebug()
    {
        
    }
    
    void keyReleased(int key)
    {
        
    }
    
    //Singleton implementation
    static Settings& get()
    {
        static Settings settings;
        return settings;
    }
    
public:
    
    bool _debug;
    bool _warped;
    
    float _smoothPos;
    
    float _xRes;
    float _yRes;
    
    float _posIn;
    float _posOut;
    float _sizeInOut;
    
    bool _someoneInIn;
    bool _someoneInOut;
    
    ofxTextureImageSequenceLoader _inOff;
    ofxTextureImageSequenceLoader _inOn;
    
    ofxTextureMovieClip _clipInOff;
    ofxTextureMovieClip _clipInOn;
    
    ofxTextureImageSequenceLoader _outOff;
    ofxTextureImageSequenceLoader _outOn;
    
    ofxTextureMovieClip _clipOutOff;
    ofxTextureMovieClip _clipOutOn;
};

//Allow easy access to zone settings
inline Settings& S()
{
    return Settings::get();
};

#endif /* settings_h */
