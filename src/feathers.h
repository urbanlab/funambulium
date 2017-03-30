//
//  feathers.h
//  funambulus
//
//  Created by Benjamin Petit on 30/03/2017.
//
//

#ifndef feathers_h
#define feathers_h

#include "particles.h"

#include "ofxMovieClip.h"

#define FEATHER1 "plume1"
#define FEATHER2 "plume2"
#define FEATHER3 "plume3"

class FeatherSettings
{
    
public:
    
    FeatherSettings()
    {
    }
    
    void setup()
    {
        _maxFeathers = 1;
    }
    
    void setupGui()
    {
        gui.addTitle("ControllerF");
        
        gui.addSlider("MaxFeathersF",_maxFeathers,0,2048);
        
        gui.addSlider("RadiusF",_radius,0.0,500.0);
        
        gui.addSlider("RepulseStrengthF",_repulseStrength,0.0,1.0);
        gui.addSlider("AttractStrengthF",_attractStrength,0.0,1.0);
        
        gui.addSlider("VelocityF",_minVelocity,0.0,1.0);
        gui.addSlider("MinPosEffectF",_minPosEffect,0.0,1.0);
    }
    
    void update()
    {
    }
    
    void draw(){}
    
    //Singleton implementation
    static FeatherSettings& get()
    {
        static FeatherSettings s;
        return s;
    }
    
public:
    
    int _maxFeathers;
    
    float _radius;
    
    float _repulseStrength;
    float _attractStrength;
    
    float _minVelocity;
    
    float _minPosEffect;
};

//Allow easy access to zone settings
inline FeatherSettings& PS()
{
    return FeatherSettings::get();
}

class Feather
{
    
public:
    Feather(float x, float y)
    {
        setup(x,y);
    }
    
    ~Feather()
    {
    }
    
    void setup(float x, float y)
    {
        _pos = ofVec2f(x,y);
        _posInit = _pos;
        _angle = ofRandom(0,360);
        
//        _hasClip = false;
        
        _isRepulsed = false;
        
        _clip = NULL;
    }
    
    void update(vector<Augmenta::Person*>& people)
    {
        _isRepulsed = false;
        
        if(people.size() > 0)
        {
            if(people[0]->centroid.x > PS()._minPosEffect)
            {
                float vel = people[0]->velocity.lengthSquared();
                
                ofVec2f featherToCenter = ofPoint(0.5*S()._xRes,0.5*S()._yRes) - _pos;
                float distance = featherToCenter.lengthSquared();
                
                if(vel < (PS()._minVelocity / 10.0) * (PS()._minVelocity / 10.0))
                {
                    if(_pos.x <= 0.0 || _pos.x >= S()._xRes || _pos.y <= 0.0 || _pos.y >= S()._yRes)
                    {
                        
                    }
                    else
                    {
                        _pos += -featherToCenter.getNormalized() * sqrt(distance) * PS()._repulseStrength;
                    }
                    
                    if(_pos.x < 0.0)
                        _pos.x = 0.0;
                    if(_pos.x > S()._xRes)
                        _pos.x = S()._xRes;
                    if(_pos.y < 0.0)
                        _pos.y = 0.0;
                    if(_pos.y > S()._yRes)
                        _pos.y = S()._yRes;
                    
                    _isRepulsed = true;
                }
            }
        }
        if(!_isRepulsed)
        {
            ofVec2f currentToOriginal = _pos - _posInit;
            _pos += -(currentToOriginal * PS()._attractStrength);
        }
    }
    
    void draw()
    {
        ofSetColor(ofColor::white);
        
//        if(_hasClip)
//        {
            ofPushMatrix();
            ofTranslate(_pos);
            ofRotate(_angle, 0, 0, 1);
            
            ofSetColor(255);
            //_clip.drawFrame(-PS()._radius/2.0,-PS()._radius/2.0,PS()._radius,PS(). _radius);
            _clip->draw(-PS()._radius/2.0,-PS()._radius/2.0,PS()._radius,PS(). _radius);
            
            ofPopMatrix();
//        }
//        else
//        {
//            drawDebug();
//        }
    }
    
    void drawDebug()
    {
        ofSetColor(ofColor::white);
        
        ofSetColor(0, 0, 255, 255);
        ofDrawCircle(_pos.x,_pos.y,PS()._radius);
    }
    
public:
    
    ofVec2f _posInit;
    ofVec2f _pos;
    float _angle;
    
//    ofxTextureMovieClip _clip;
//    bool _hasClip;
    ofImage* _clip;
    
    bool _isRepulsed;
};

class Feathers : public Particles
{
    
public:
    Feathers()
    :Particles()
    {
    }
    
    virtual void setup(string path)
    {
        PS().setup();
        
        _species.push_back(StaticSpecies(path+"/"+FEATHER1+"/p.png"));
        _species.push_back(StaticSpecies(path+"/"+FEATHER2+"/p.png"));
        _species.push_back(StaticSpecies(path+"/"+FEATHER3+"/p.png"));
        
        _currentSpecies = 0;
        
        _feathers.clear();
    }
    
    virtual void start()
    {
        //_feathers.clear();
    }
    
    virtual void stop()
    {
        _feathers.clear();
    }
    
    void addRandomFeathers(int amt)
    {
        for(int i=0; i<amt; i++)
        {
            ofVec2f randPosVec = ofVec2f(ofRandom(0.0,S()._xRes),ofRandom(0.0,S()._yRes));
            ofVec2f pos = randPosVec;
            
            addFeather(pos);
        }
    }
    
    Feather* addFeather(ofVec2f pos)
    {
        _feathers.push_back(Feather(pos.x,pos.y));
        
//        if(_species[_currentSpecies]._hasImgSeq)
//        {
//            _feathers.back()._hasClip = true;
//            _feathers.back()._clip.init(&_species[_currentSpecies]._imgSeq,1.0);
            _feathers.back()._clip = &_species[_currentSpecies]._tex;
            _currentSpecies++;
            _currentSpecies %= _species.size();
//        }
//        else
//        {
//            _feathers.back()._hasClip = false;
//        }
        
        return &(_feathers.back());
    }
    
    virtual void setupGui()
    {
        gui.addTitle("Feather Particles");
        PS().setupGui();
    }
    
    virtual void update(vector<Augmenta::Person*>& people)
    {
        while(_feathers.size()<PS()._maxFeathers)
            addRandomFeathers(1);
        while(_feathers.size()>PS()._maxFeathers)
            _feathers.pop_front();
        
        for(auto & l : _feathers)
            l.update(people);
    }
    
    virtual void draw()
    {
        for(list<Feather>::iterator it = _feathers.begin(); it != _feathers.end(); it++)
        {
            ofSetColor(ofColor::white);
            it->draw();
        }
    }
    
    virtual void drawDebug()
    {
        for(list<Feather>::iterator it = _feathers.begin(); it != _feathers.end(); it++)
        {
            ofSetColor(ofColor::white);
            it->drawDebug();
        }
    }
    
public:
    
    //vector<Species> _species;
    vector<StaticSpecies> _species;
    int _currentSpecies;
    
    list<Feather> _feathers;
    
    float _nbParticles;
    
    int _maxParticles;
};


#endif /* feathers_h */
