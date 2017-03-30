//
//  remote.h
//  funambulus
//
//  Created by Benjamin Petit on 30/03/2017.
//
//

#ifndef remote_h
#define remote_h



class OSCMessenger
{
    
public:
    
    OSCMessenger()
    {
    }
    
    void setup()
    {
        
    }
    
    void setupGui()
    {
    }
    
    bool update()
    {
                return false;
    }
    
    void drawDebug()
    {
        
    }
    
    //Singleton implementation
    static OSCMessenger& get()
    {
        static OSCMessenger osc;
        return osc;
    }
    
public:
    
    
};

//Allow easy access to zone settings
inline OSCMessenger& OSC()
{
    return OSCMessenger::get();
};

#endif /* remote_h */
