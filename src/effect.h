//
//  effect.h
//  funambulus
//
//  Created by Benjamin Petit on 28/03/2017.
//
//

#ifndef effect_h
#define effect_h

#include "ofxBounce.h"
#include "ofxRipples.h"

class Effect
{
public:
    
    Effect()
    {
    }
    
    virtual void setup()
    {
    }
    
    virtual void setTexture(ofImage& tex)
    {
    }
    
    virtual void setupGui()
    {
    }
    
    virtual void start()
    {
    }
    
    virtual void stop()
    {
    }
    
    virtual void reset()
    {
    }
    
    virtual void update(vector<Augmenta::Person*>& people)
    {
    }
    
    virtual void draw()
    {
    }
    
    virtual void drawDebug()
    {
    }
    
public:
    
};

class RippleEffect : public Effect
{
    
public:
    
    RippleEffect()
    {
    }
    
    void setup()
    {
        _ripples.allocate(S()._xRes,S()._yRes,GL_RGBA);
        _bounce.allocate(S()._xRes,S()._yRes,GL_RGBA);
    }
    
    void setupGui()
    {
        gui.addTitle("RippleEffect");
        gui.addSlider("Damping",_damping,0.0,1.0);
        gui.addSlider("Size",_size,0.0,100.0);
        gui.addSlider("Velocity",_minVelocity,0.0,1.0);
    }
    
    void setTexture(ofTexture& tex)
    {
        _bounce.setTexture(tex, 1);
    }
    
    virtual void stop()
    {
        _ripples.clear();
        _bounce.clear();
    }
    
    virtual void start()
    {
        setup();
    }
    
    virtual void update(vector<Augmenta::Person*>& people)
    {
        _ripples.damping = _damping;
        
        _ripples.begin();
        ofFill();
        //ofSetColor(ofNoise( ofGetFrameNum() ) * 255 * 5, 255);
        ofSetColor(255);
        for(auto & p : people)
        {
            cout<<p->velocity.length()<<endl;
            if(p->velocity.length() > _minVelocity/10.0)
            {
                ofDrawEllipse(p->centroid.x*S()._xRes,
                              p->centroid.y*S()._yRes,
                              _size,
                              _size);
            }
        }
        _ripples.end();
        _ripples.update();
        
        _bounce<<_ripples;
    }
    
    virtual void draw()
    {
        ofPushMatrix();
        
        //ofTranslate(RES_X/2.0,RES_Y/2.0);
        //ofRotateZ(90);
        //ofTranslate(-RES_Y/2.0,-RES_X/2.0);
        
        _bounce.draw(0.0,0.0,S()._xRes,S()._yRes);
        
        ofPopMatrix();
        
        //_bounce.draw(0.0,0.0,S()._xRes,S()._yRes);
    }
    
    virtual void drawDebug()
    {
        _ripples.draw(0.0,0.0,S()._xRes,S()._yRes);
    }
    
public:
    
    float _damping;
    float _size;
    float _minVelocity;
    
    ofxBounce   _bounce;
    ofxRipples  _ripples;
};

#endif /* effect_h */
