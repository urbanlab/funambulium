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
    }
    
    void setupGui()
    {
        gui.addTitle("Settings");
        gui.addSlider("SmoothPos",_smoothPos,0.0,1.0);
    }
    
    void update()
    {
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
};

//Allow easy access to zone settings
inline Settings& S()
{
    return Settings::get();
};

#endif /* settings_h */
