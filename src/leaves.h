//
//  leaves.h
//  funambulus
//
//  Created by Benjamin Petit on 27/03/2017.
//
//

#ifndef leaves_h
#define leaves_h

//
#include "particles.h"

#include "ofxMovieClip.h"

#define LEAF1 "feuille1"
#define LEAF2 "feuille2"

class LeafSettings
{
    
public:
    
    LeafSettings()
    {
        _radius = 20.0;
        
        _decayFactor = 0.99;
        _smoothFactor = 0.99;
        
        _maxSpeed		= ofRandom(2.0,5.0);
        _maxSpeedSqrd	= _maxSpeed * _maxSpeed;
        _minSpeed		= 0.0;
        _minSpeedSqrd	= _minSpeed * _minSpeed;
    }
    
    void setup()
    {
        _maxLeafes = 1;
    }
    
    void setupGui()
    {
        gui.addTitle("Controller");
        
        gui.addSlider("MaxLeafes",_maxLeafes,0,2048,"/controller/maxparticles");
        
        gui.addSlider("Radius",_radius,0.0,500.0,"/particles/radius");
        
        gui.addSlider("SmoothFactor",_smoothFactor,0.0,1.0,"/particles/smoothfactor");
        gui.addSlider("DecayFactor",_decayFactor,0.0,1.0,"/particles/decayfactor");
        
        gui.addSlider("MinSpeed",_minSpeed,0.0,5.0,"/particles/minspeed");
        gui.addSlider("MaxSpeed",_maxSpeed,0.0,50.0,"/particles/maxspeed");
        
        gui.addSlider("RepulseStrength",_repulseStrength,0.0,1.0,"/particles/repulsestrength");
        gui.addSlider("RepulseMaxDist",_repulseMaxDist,0.0,MIN(S()._xRes,S()._yRes)/2.0,"/particles/repulsemaxdist");
    }
    
    void update()
    {
        if(_minSpeed != _ominSpeed || _maxSpeed != _omaxSpeed)
        {
            _minSpeedSqrd=_minSpeed*_minSpeed;
            _maxSpeedSqrd=_maxSpeed*_maxSpeed;
            _ominSpeed = _minSpeed;
            _omaxSpeed = _maxSpeed;
        }
    }
    
    void draw(){}
    
    //Singleton implementation
    static LeafSettings& get()
    {
        static LeafSettings s;
        return s;
    }
    
public:
    
    int _maxLeafes;
    
    float _maxSpeed;
    float _maxSpeedSqrd;
    float _omaxSpeed;
    float _minSpeed;
    float _minSpeedSqrd;
    float _ominSpeed;
    
    float _radius;
    
    float _decayFactor;
    float _smoothFactor;
    
    float _repulseStrength;
    float _repulseMaxDist;
};

//Allow easy access to zone settings
inline LeafSettings& LS()
{
    return LeafSettings::get();
}

class Leaf
{
    
public:
    Leaf(float x, float y, float vx, float vy)
    {
        setup(x,y,vx,vy);
    }
    
    ~Leaf()
    {
    }
    
    void setup(float x, float y, float vx, float vy)
    {
        _pos = ofVec2f(x,y);
        _posInit = _pos;
        _vel = ofVec2f(vx,vy);
        _velNormal = _vel.normalized();
        _acc = ofVec2f(0.0,0.0);
        
        _hasClip = false;
        
        _isRepulsed = false;
    }
    
    void update()
    {
        ofVec2f vel;
        vel = _vel + _acc;
        _vel += (vel-_vel)*LS()._smoothFactor;

        if(!_isRepulsed)
            attract(_posInit);
        
        float vLengthSqrd = _vel.lengthSquared();
        
        if(vLengthSqrd!=0)
            _velNormal = _vel.normalized();
        
        if( vLengthSqrd > LS()._maxSpeedSqrd )
        {
            _vel = _velNormal * LS()._maxSpeed;
            
        }
        else if( vLengthSqrd < LS()._minSpeedSqrd )
        {
            _vel = _velNormal * LS()._minSpeed;
        }
        
        _pos += _vel;
        
        _right = _velNormal.getPerpendicular();
        _right.normalize();
        
        _vel *= LS()._decayFactor;
        _acc = ofVec2f(0.0);
    }
    
    void attract(ofVec2f center)
    {
        ofVec2f dirToCenter   = _pos - center;
        float distToCenter  = dirToCenter.length();
        //TODO: Tester sans la condition
        if( distToCenter > LS()._repulseMaxDist/10.0 )
        {
            _vel -= dirToCenter.normalized() * ( ofMap(distToCenter,0.0,LS()._repulseMaxDist,1.0,0.0) * LS()._repulseStrength*10.0 );
        }
    }
    
    bool repulse(ofVec2f center)
    {
        ofVec2f dirToCenter   = _pos - center;
        float distToCenter  = dirToCenter.length();
        //TODO: Tester sans la condition
        if( distToCenter < LS()._repulseMaxDist )
        {
            _vel += dirToCenter.normalized() * ( ofMap(distToCenter,0.0,LS()._repulseMaxDist,1.0,0.0) * LS()._repulseStrength *10.0 );
            
            _isRepulsed = true;
        }
    }
    
    void draw()
    {
        ofSetColor(ofColor::white);
        
        if(_hasClip)
        {
            ofVec2f Va(1,0);
            ofVec2f Vb(_velNormal);
            
            float angle = Va.angle(Vb);
            
            ofPushMatrix();
            ofTranslate(_pos);
            ofRotate(angle, 0, 0, 1);
            
            ofSetColor(255);
            _clip.drawFrame(-LS()._radius/2.0,-LS()._radius/2.0,LS()._radius,LS(). _radius);
            
            ofPopMatrix();
        }
        else
        {
            drawDebug();
        }
    }
    
    void drawDebug()
    {
        ofSetColor(ofColor::white);
        
        ofSetColor(0, 0, 255, 255);
        ofLine(_pos.x, _pos.y, _pos.x + _velNormal.x*50.0  , _pos.y + _velNormal.y*50.0);
        ofSetColor(0, 255, 0, 255);
        ofLine(_pos.x, _pos.y, _pos.x + _right.x*50.0, _pos.y + _right.y*50.0);
    }
    
public:
    
    ofVec2f _posInit;
    ofVec2f _pos;
    ofVec2f _right;
    
    ofVec2f _vel;
    ofVec2f _velNormal;
    ofVec2f _acc;
    
    ofxTextureMovieClip _clip;
    bool _hasClip;
    
    bool _isRepulsed;
};

class Leaves : public Particles
{
    
public:
    Leaves()
    :Particles()
    {
    }
    
    virtual void setup(string path)
    {
        LS().setup();
        
        _species.push_back(Species(path+"/"+LEAF1,"Leaf1"));
        _species.push_back(Species(path+"/"+LEAF2,"Leaf2"));
        
        _currentSpecies = 0;
        
        reload();
    }
    
    virtual void reload()
    {
        _leaves.clear();
    }
    
    void addRandomLeaves(int amt)
    {
        for(int i=0; i<amt; i++)
        {
            ofVec2f randPosVec = ofVec2f(ofRandom(0.0,S()._xRes),ofRandom(0.0,S()._yRes));
            ofVec2f pos = randPosVec;
            ofVec2f randVelVec = ofVec2f(ofRandom(LS()._minSpeed,LS()._maxSpeed),ofRandom(LS()._minSpeed,LS()._maxSpeed));
            ofVec2f vel = ofVec2f(0.0,0.0);
            
            addLeaf(pos,vel);
        }
    }
    
    Leaf* addLeaf(ofVec2f pos, ofVec2f vel)
    {
        _leaves.push_back(Leaf(pos.x,pos.y, vel.x,vel.y));
        
        if(_species[_currentSpecies]._hasImgSeq)
        {
            _leaves.back()._hasClip = true;
            _leaves.back()._clip.init(&_species[_currentSpecies]._imgSeq,1.0);
            _currentSpecies++;
            _currentSpecies %= _species.size();
        }
        else
        {
            _leaves.back()._hasClip = false;
        }
        
        return &(_leaves.back());
    }
    
    virtual void setupGui()
    {
        LS().setupGui();
    }
    
    virtual void update(vector<Augmenta::Person*>& people)
    {
        LS().update();
        
        while(_leaves.size()<LS()._maxLeafes)
            addRandomLeaves(1);
        while(_leaves.size()>LS()._maxLeafes)
            _leaves.pop_front();
        
        
        for(list<Leaf>::iterator it = _leaves.begin(); it != _leaves.end(); it++)
            it->_isRepulsed = false;
        
        for(auto p : people)
            repulseParticles(ofVec2f(p->centroid.x*S()._xRes,p->centroid.y*S()._yRes));
        
        
        for(list<Leaf>::iterator it = _leaves.begin(); it != _leaves.end(); it++)
            it->update();
    }
    
    void attractParticles(ofVec2f attractor)
    {
        for( list<Leaf>::iterator p = _leaves.begin(); p != _leaves.end(); ++p )
        {
            p->attract(attractor);
        }
    }
    void repulseParticles(ofVec2f repulsor)
    {
        for( list<Leaf>::iterator p = _leaves.begin(); p != _leaves.end(); ++p )
        {
            p->repulse(repulsor);
        }
    }
    
    virtual void draw()
    {
        for(list<Leaf>::iterator it = _leaves.begin(); it != _leaves.end(); it++)
        {
            ofSetColor(ofColor::white);
            it->draw();
        }
    }
    
    virtual void drawDebug()
    {
        for(list<Leaf>::iterator it = _leaves.begin(); it != _leaves.end(); it++)
        {
            ofSetColor(ofColor::white);
            it->drawDebug();
        }
    }
    
public:
    
    vector<Species> _species;
    int _currentSpecies;
    
    list<Leaf> _leaves;
    
    float _nbParticles;
    
    int _maxParticles;
};

#endif /* leaves_h */
