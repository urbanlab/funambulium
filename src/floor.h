//
//  floor.h
//  funambulus
//
//  Created by Benjamin Petit on 24/03/2017.
//
//

#ifndef floor_h
#define floor_h

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
    
    void setup(string path)
    {
        cout<<"\tFLOOR: "<<path+"/EARTH.mp4"<<endl;
        _bg.load(path+"/EARTH.mp4");
        
        _pos = 0.0;
    }
    
    void start()
    {
        _bg.play();
        _pos = 0.0;
    }
    
    void stop()
    {
        _bg.stop();
        _pos = 0.0;
    }
    
    void update(float pos)
    {
        pos = ofClamp(pos,0.0,1.0);
        
        if(pos > _pos)
            _pos = pos*(1-S()._smoothPos) + _pos * S()._smoothPos;
        
        if(_pos < _bg.getPosition())
            _bg.setPaused(true);
        else
            _bg.setPaused(false);
        
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
    
    ofVideoPlayer _bg;
    
    float _pos;
};

#endif /* floor_h */
