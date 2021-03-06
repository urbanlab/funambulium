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
#define LEAF3 "feuille3"
#define LEAF4 "feuille4"

class LeafSettings
{
    
public:
    
    LeafSettings()
    {
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
        
        gui.addSlider("RepulseStrength",_repulseStrength,0.0,1.0,"/particles/repulsestrength");
        gui.addSlider("RepulseMaxDist",_repulseMaxDist,0.0,MIN(S()._xRes,S()._yRes)/2.0,"/particles/repulsemaxdist");
    }
    
    void update()
    {
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
    
    float _radius;
    
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
    Leaf(float x, float y)
    {
        setup(x,y);
    }
    
    ~Leaf()
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
        
        ofPoint closestPerson;
        float closestDist = S()._xRes*S()._xRes;
        
        for(auto p : people)
        {
            ofVec2f leafToBlob = p->centroid*ofVec2f(S()._xRes,S()._yRes) - _pos;
            float distance = leafToBlob.lengthSquared();
            
            if(distance < closestDist)
            {
                closestDist = distance;
                closestPerson = leafToBlob;
            }
        }
        
        if(closestDist < S()._xRes*S()._xRes && closestDist < LS()._repulseMaxDist*LS()._repulseMaxDist)
        {
            _pos += -closestPerson.getNormalized() * sqrt(closestDist) * LS()._repulseStrength;
            
            //if(closestDist < LS()._repulseMaxDist * 2.1)
            //    _isRepulsed = true;
        }
        //else
        //if(!_isRepulsed)
        //{
            //ofVec2f currentToOriginal = _pos - _posInit;
            //_pos += -(currentToOriginal * LS()._repulseStrength);
        //}
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
//            _clip.drawFrame(-LS()._radius/2.0,-LS()._radius/2.0,LS()._radius,LS(). _radius);
            _clip->draw(-LS()._radius/2.0,-LS()._radius/2.0,LS()._radius,LS(). _radius);
            
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
        ofDrawCircle(_pos.x,_pos.y,LS()._radius);
    }
    
public:
    
    ofVec2f _posInit;
    ofVec2f _pos;
    float _angle;
    
//    ofxTextureMovieClip _clip;
    ofImage* _clip;
//    bool _hasClip;
    
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
        
        _species.push_back(StaticSpecies(path+"/"+LEAF1+"/f.png"));
        _species.push_back(StaticSpecies(path+"/"+LEAF2+"/f.png"));
        _species.push_back(StaticSpecies(path+"/"+LEAF3+"/f.png"));
        _species.push_back(StaticSpecies(path+"/"+LEAF4+"/f.png"));
        
        _currentSpecies = 0;
        
        _leaves.clear();
    }
    
    virtual void start()
    {
        //_leaves.clear();
    }
    
    virtual void stop()
    {
        _leaves.clear();
    }
    
    void addRandomLeaves(int amt)
    {
        for(int i=0; i<amt; i++)
        {
            ofVec2f randPosVec = ofVec2f(ofRandom(0.0,S()._xRes),ofRandom(0.0,S()._yRes));
            ofVec2f pos = randPosVec;
            
            addLeaf(pos);
        }
    }
    
    Leaf* addLeaf(ofVec2f pos)
    {
        _leaves.push_back(Leaf(pos.x,pos.y));
        
//        if(_species[_currentSpecies]._hasImgSeq)
//        {
//            _leaves.back()._hasClip = true;
//            _leaves.back()._clip
            _leaves.back()._clip = &_species[_currentSpecies]._tex;
            _currentSpecies++;
            _currentSpecies %= _species.size();
//        }
//        else
//        {
//            _leaves.back()._hasClip = false;
//        }
        
        return &(_leaves.back());
    }
    
    virtual void setupGui()
    {
        gui.addTitle("Leaf Particles");
        LS().setupGui();
    }
    
    virtual void update(vector<Augmenta::Person*>& people)
    {
        while(_leaves.size()<LS()._maxLeafes)
            addRandomLeaves(1);
        while(_leaves.size()>LS()._maxLeafes)
            _leaves.pop_front();
        
        for(auto & l : _leaves)
            l.update(people);
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
    
    //vector<Species> _species;
    vector<StaticSpecies> _species;
    int _currentSpecies;
    
    list<Leaf> _leaves;
    
    float _nbParticles;
    
    int _maxParticles;
};

#endif /* leaves_h */
