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
        gui.addSlider("RadiusInOut",_radiusInOut,0.0,1.0);
        gui.addSlider("FadeDuration",_fadeDuration,0.0,5.0);
        gui.addTitle("Transformation");
        gui.addSlider("RotXMaxAmplitude",_rotXMaxAmplitude,0.0,90.0);
        gui.addSlider("RotXMaxSpeed",_rotXMaxSpeed,0.0,10.0);
        gui.addSlider("RotYMaxAmplitude",_rotYMaxAmplitude,0.0,90.0);
        gui.addSlider("RotYMaxSpeed",_rotYMaxSpeed,0.0,10.0);
        gui.addSlider("ZoomZMaxAmplitude",_zoomZMaxAmplitude,0.0,400.0);
        gui.addSlider("ZoomZMaxSpeed",_zoomZMaxSpeed,0.0,10.0);
    }
    
    void update(vector<Augmenta::Person*>& people)
    {
        _someoneInIn = false;
        _someoneInOut = false;
        
        for(auto & p : people)
        {
            float x = p->centroid.x * _xRes;
            float y = p->centroid.y * _yRes;
            float xIn = _posIn * _xRes;
            float yIn = 0.5 * _yRes;
            float xOut = _posOut * _xRes;
            float yOut = 0.5 * _yRes;
            float s = _sizeInOut * _yRes * _radiusInOut;
            
            if(ofDist(x,y,xIn,yIn) < s)
            {
                _someoneInIn = true;
            }
            
            if(ofDist(x,y,xOut,yOut) < s)
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
    
    float _radiusInOut;
    
    float _fadeDuration;
    
    float _rotXMaxAmplitude;
    float _rotXMaxSpeed;
    float _rotYMaxAmplitude;
    float _rotYMaxSpeed;
    float _zoomZMaxAmplitude;
    float _zoomZMaxSpeed;
};

//Allow easy access to zone settings
inline Settings& S()
{
    return Settings::get();
};

#endif /* settings_h */
