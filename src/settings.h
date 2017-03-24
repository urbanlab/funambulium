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

class Settings
{
    
public:
    
    Settings()
    {
    }
    
    void setup()
    {
        _debug = false;
    }
    
    void setupGui()
    {
        gui.addTitle("Settings");
    }
    
    void update()
    {
    }
    
    void drawDebug()
    {
    }
    
    void keyReleased(int key)
    {
        if(key == 'f')
            ofToggleFullscreen();
        if(key == 'd')
            _debug = !_debug;
    }
    
    //Singleton implementation
    static Settings& get()
    {
        static Settings settings;
        return settings;
    }
    
public:
    
    bool _debug;
    
};

//Allow easy access to zone settings
inline Settings& S()
{
    return Settings::get();
};

#endif /* settings_h */
