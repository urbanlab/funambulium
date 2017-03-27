//
//  fishes.h
//  funambulus
//
//  Created by Benjamin Petit on 27/03/2017.
//
//

#ifndef fishes_h
#define fishes_h

#include "particles.h"

#include <valarray>

#include "ofxMovieClip.h"
#include "perlin.h"

#define SCALE 0.5

#define ALPHASMOOTH 0.02
#define DIRSMOOTH 0.96

#define FISH1 "poisson1"
#define FISH2 "poisson2"
#define FISH3 "poisson3"
#define FISH4 "poisson4"

class FishSettings
{
    
public:
    
    FishSettings()
    {
        _alphaSmooth = ALPHASMOOTH;
        
        _boundsRadius = MIN(S()._xRes,S()._yRes)/2.0;
        
        _radius = 20.0;
        
        _tailLength = 10;
        
        _decayFactor = 0.99;
        _smoothFactor = 0.99;
        
        _maxSpeed		= ofRandom(2.0,5.0);
        _maxSpeedSqrd	= _maxSpeed * _maxSpeed;
        _minSpeed		= ofRandom(1.0,1.5);
        _minSpeedSqrd	= _minSpeed * _minSpeed;
        
        _center = ofVec2f(S()._xRes/2.0,S()._yRes/2.0);
        _maxDistanceToCenter = MIN(S()._xRes,S()._yRes)/2.0;
        _pullStrengthToCenter = 0.9;
        
        _perlin = Perlin(4);
    }
    
    void setup()
    {
        _maxFishes = 1;
        _maxPredators = 0;
    }
    
    void setupGui()
    {
        gui.addSlider("FishBoundRadius",_boundsRadius,0.0,MIN(S()._xRes,S()._yRes)/2.0);
        gui.addSlider("FishAlphaSmooth",_alphaSmooth,0.0,0.5);
        
        gui.addTitle("Controller");
        gui.addSlider("MaxFishes",_maxFishes,0,2048,"/controller/maxparticles");
        gui.addSlider("MaxPredators",_maxPredators,0,2048,"/controller/maxpredators");
        gui.addSlider("ZoneRadius",_zoneRadius,0,500,"/controller/zoneradius");
        gui.addSlider("LowTresh",_lowThresh,0,1.0,"/controller/lowtresh");
        gui.addSlider("HighTresh",_highThresh,0,1.0,"/controller/hightresh");
        gui.addSlider("AttractStrength",_attractStrength,0.0,0.5,"/controller/attractstrength");
        gui.addSlider("RepulseStrength",_repelStrength,0.0,0.5,"/controller/repulsestrength");
        gui.addSlider("AlignStrength",_alignStrength,0.0,0.5,"/controller/alignstrength");
        
        gui.addToggle("PullToCenter", _pullToCenter, "/controller/pulltocenter");
        gui.addToggle("BoundToCircle", _boundedToCircle, "/controller/boundtocircle");
        
        gui.addSlider("ScalePerlin",_scalePerlin,0.0,1.0,"/controller/scaleperlin");
        gui.addSlider("MulPerlin",_mulPerlin,0.0,1.0,"/controller/mulperlin");
        
        gui.addTitle("Particles");
        gui.addSlider("Radius",_radius,0.0,500.0,"/particles/radius");
        gui.addSlider("TailLength",_tailLength,0,100,"/particles/taillength");
        gui.addSlider("SmoothFactor",_smoothFactor,0.0,1.0,"/particles/smoothfactor");
        gui.addSlider("DecayFactor",_decayFactor,0.0,1.0,"/particles/decayfactor");
        gui.addSlider("MinSpeed",_minSpeed,0.0,5.0,"/particles/minspeed");
        gui.addSlider("MaxSpeed",_maxSpeed,0.0,50.0,"/particles/maxspeed");
        
        gui.addSlider("MaxDistToCenter",_maxDistanceToCenter,0.0,MIN(S()._xRes,S()._yRes)/2.0,"/particles/maxdisttocenter");
        gui.addSlider("PullStrengthToCenter",_pullStrengthToCenter,0.0,0.1,"/particles/pullstrengthtocenter");
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
    static FishSettings& get()
    {
        static FishSettings s;
        return s;
    }
    
public:
    
    float _alphaSmooth;
    
    float _boundsRadius;
    
    int _maxFishes;
    int _maxPredators;
    
    float _maxSpeed;
    float _maxSpeedSqrd;
    float _omaxSpeed;
    float _minSpeed;
    float _minSpeedSqrd;
    float _ominSpeed;
    
    float _radius;
    
    float _decayFactor;
    float _smoothFactor;
    
    int _tailLength;
    
    ofVec2f _center;
    float _maxDistanceToCenter;
    float _pullStrengthToCenter;
    
    bool _boundedToCircle;
    bool _pullToCenter;
    
    //Controller values
    float _zoneRadius;
    float _lowThresh;
    float _highThresh;
    float _attractStrength;
    float _repelStrength;
    float _alignStrength;
    
    float _repulseStrength;
    float _repulseMaxDist;
    
    Perlin _perlin;
    float _scalePerlin;
    float _mulPerlin;
};

//Allow easy access to zone settings
inline FishSettings& FS()
{
    return FishSettings::get();
}

//class Species
//{
//    
//public:
//    Species(string dir,string name)
//    {
//        setup(dir,name);
//    }
//    
//    ~Species()
//    {
//    }
//    
//    void setup(string dir,string name)
//    {
//        _imgSeq.loadAndCreateSequence(dir.c_str(),name.c_str());
//        _hasImgSeq = _imgSeq.assetCollectionSize>0;
//    }
//    
//public:
//    
//    ofxTextureImageSequenceLoader _imgSeq;
//    bool _hasImgSeq;
//};


class Fish
{
    
public:
    Fish(float x, float y, float vx, float vy)
    {
        setup(x,y,vx,vy);
    }
    
    ~Fish()
    {
    }
    
    void setup(float x, float y, float vx, float vy)
    {
        _alive = true;
        _alpha = 1.0;
        
        _pos = ofVec2f(x,y);
        _vel = ofVec2f(vx,vy);
        _velNormal = _vel.normalized();
        _acc = ofVec2f(0.0,0.0);
        
        _crowdFactor = 0.0;
        
        _hunger = 1.0;
        _fear = 0.0;
        
        _isHungry = true;
        _isDead = false;
        
        _hasClip = false;
    }
    
    void update()
    {
        //        _crowdFactor -= ( _crowdFactor - ( 1.0f - _nbNeighbors * 0.01f ) ) * 0.1f;
        //        _crowdFactor = ofClamp(_crowdFactor, 0.5, 1.0);
        //
        //        _fear -= ( _fear - 0.0f ) * 0.2f;
        //
        //        _hunger += 0.001f;
        //        _hunger = ofClamp(_hunger, 0.0f, 1.0f );
        //
        //        if(_hunger > 0.5f) _isHungry = true;
        
        ofVec2f vel;
        vel = _vel + _acc;
        _vel += (vel-_vel)*FS()._smoothFactor;
        
        float vLengthSqrd = _vel.lengthSquared();
        
        if(vLengthSqrd!=0)
            _velNormal = _vel.normalized();
        
        if( vLengthSqrd > FS()._maxSpeedSqrd )
        {
            _vel = _velNormal * FS()._maxSpeed;
            
        }
        else if( vLengthSqrd < FS()._minSpeedSqrd )
        {
            _vel = _velNormal * FS()._minSpeed;
        }
        
        _pos += _vel;
        
        _right = _velNormal.getPerpendicular();
        _right.normalize();
        
        _tail.push_back(_pos);
        while(_tail.size()>FS()._tailLength)
            _tail.pop_front();
        
        _tailVel.push_back(_velNormal);
        while(_tailVel.size()>FS()._tailLength)
            _tailVel.pop_front();
        
        _tailRight.push_back(_right);
        while(_tailRight.size()>FS()._tailLength)
            _tailRight.pop_front();
        
        _vel *= FS()._decayFactor;
        _acc = ofVec2f(0.0);
        
        _neighborPos = ofVec2f(0.0);
        _nbNeighbors = 0;
        
        //        if(_hasClip)
        //            _clip.frameSpeed = ofMap(vLengthSqrd,FS()._minSpeedSqrd,FS()._maxSpeedSqrd,0.0,1.0);
    }
    
    void addNeighborPos(ofVec2f pos)
    {
        _neighborPos += pos;
        _nbNeighbors++;
    }
    
    void pullToCenter()
    {
        ofVec2f dirToCenter   = _pos - FS()._center;
        float distToCenter  = dirToCenter.length();
        
        //TODO: Tester sans la condition
        //if( distToCenter > FS()._maxDistanceToCenter )
        {
            _vel -= dirToCenter.normalized() * ( ofMap(distToCenter,0.0,FS()._maxDistanceToCenter,0.0,1.0) * FS()._pullStrengthToCenter );
        }
    }
    
    void repulseFromCenter()
    {
        ofVec2f dirToCenter   = _pos - FS()._center;
        float distToCenter  = dirToCenter.length();
        //TODO: Tester sans la condition
        //if( distToCenter > FS()._maxDistanceToCenter )
        {
            _vel += dirToCenter.normalized() * ( ofMap(distToCenter,0.0,FS()._maxDistanceToCenter,0.0,1.0) * FS()._pullStrengthToCenter );
        }
    }
    
    void attract(ofVec2f center)
    {
        //    ofVec2f dirToCenter   = _pos - center;
        //    float distToCenter  = dirToCenter.length();
        //
        //    if( distToCenter < _maxDistanceToCenter / 2.0 )
        //    {
        //        _vel -= dirToCenter.normalized() * ( distToCenter * _pullStrengthToCenter * 10.0 );
        //    }
    }
    
    void repulse(ofVec2f center)
    {
        ofVec2f dirToCenter   = _pos - center;
        float distToCenter  = dirToCenter.length();
        //TODO: Tester sans la condition
        if( distToCenter < FS()._repulseMaxDist )
        {
            _vel += dirToCenter.normalized() * ( ofMap(distToCenter,0.0,FS()._repulseMaxDist,1.0,0.0) * FS()._repulseStrength *10.0 );
        }
    }
    
    //TODO: A compléter!
    //TODO: Faire des poissons qui réaparraissent de l'autre côté du cercle...
    void boundToCircle()
    {
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
            _clip.drawFrame(-FS()._radius/2.0,-FS()._radius/2.0,FS()._radius,FS(). _radius);
            
            ofPopMatrix();
            
            //        ofSetColor(0, 0, 255, 255);
            //        ofLine(_pos.x, _pos.y, _pos.z, _pos.x + _velNormal.x*50.0  , _pos.y + _velNormal.y*50.0, _pos.z + _velNormal.z*50.0);
            //        ofSetColor(0, 255, 0, 255);
            //        ofLine(_pos.x, _pos.y, _pos.z, _pos.x + _right.x*50.0, _pos.y + _right.y*50.0, _pos.z + _right.z*50.0);
            
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
    
    float _alpha;
    
    ofVec2f _pos;
    ofVec2f _right;
    
    ofVec2f _vel;
    ofVec2f _velNormal;
    ofVec2f _acc;
    
    list<ofVec2f> _tail;
    list<ofVec2f> _tailVel;
    list<ofVec2f> _tailRight;
    
    ofVec2f _neighborPos;
    float _nbNeighbors;
    
    float _hunger;
    float _fear;
    
    bool _isHungry;
    bool _isDead;
    
    float _crowdFactor;
    
    ofxTextureMovieClip _clip;
    bool _hasClip;
    
    bool _alive;
};

class Fishes : public Particles
{
    
public:
    Fishes()
    :Particles()
    {
    }
    
    virtual void setup(string path)
    {
        FS().setup();
        
        _species.push_back(Species(path+"/"+FISH1,"Fish1"));
        _species.push_back(Species(path+"/"+FISH2,"Fish2"));
        _species.push_back(Species(path+"/"+FISH3,"Fish3"));
        _species.push_back(Species(path+"/"+FISH4,"Fish4"));
        
        _currentSpecies = 0;
        
        reload();
    }
    
    virtual void reload()
    {
        _fishes.clear();
    }
    
    void addRandomFishes(int amt)
    {
        for(int i=0; i<amt; i++)
        {
            ofVec2f randPosVec = ofVec2f(ofRandom(0.0,S()._xRes),ofRandom(0.0,S()._yRes));
            ofVec2f pos = randPosVec;
            ofVec2f randVelVec = ofVec2f(ofRandom(FS()._minSpeed,FS()._maxSpeed),ofRandom(FS()._minSpeed,FS()._maxSpeed));
            ofVec2f vel = randVelVec * FS()._boundsRadius;
            
            addFish(pos,vel);
            //addFish(ofVec2f(S()._xRes/2.0,S()._yRes/2.0),vel);
        }
    }
    
    Fish* addFish(ofVec2f pos, ofVec2f vel)
    {
        _fishes.push_back(Fish(pos.x,pos.y, vel.x,vel.y));
        
        if(_species[_currentSpecies]._hasImgSeq)
        {
            _fishes.back()._hasClip = true;
            _fishes.back()._clip.init(&_species[_currentSpecies]._imgSeq,1.0);
            _currentSpecies++;
            _currentSpecies %= _species.size();
        }
        else
        {
            _fishes.back()._hasClip = false;
        }
        
        return &(_fishes.back());
    }
    
    void addRandomPredators(int amt)
    {
        for(int i=0; i<amt; i++)
        {
            ofVec2f randPosVec = ofVec2f(ofRandom(0.0,S()._xRes),ofRandom(0.0,S()._yRes));
            ofVec2f pos = randPosVec;
            ofVec2f randVelVec = ofVec2f(ofRandom(FS()._minSpeed,FS()._maxSpeed),ofRandom(FS()._minSpeed,FS()._maxSpeed));
            ofVec2f vel = randVelVec * FS()._boundsRadius;
            
            addPredator(pos,vel);
            //addPredator(ofVec2f(S()._xRes/2.0,S()._yRes/2.0),vel);
        }
    }
    
    void addPredator(ofVec2f pos, ofVec2f vel)
    {
        _predators.push_back(Fish(pos.x,pos.y, vel.x,vel.y));
        _predators.back()._hasClip = false;
    }
    
    virtual void setupGui()
    {
        FS().setupGui();
    }
    
    virtual void update(vector<Augmenta::Person*>& people)
    {
        FS().update();
        
        for(auto p : people)
        {
            repulseParticles(ofVec2f(p->centroid.x*S()._xRes,p->centroid.y*S()._yRes));
        }
        
        while(_fishes.size()<FS()._maxFishes)
        {
            addRandomFishes(1);
        }
        
        while(_fishes.size()>FS()._maxFishes)
            _fishes.pop_front();
        
        while(_predators.size()<_maxPredators)
        {
            addRandomPredators(1);
        }
        
        while(_predators.size()>_maxPredators)
            _predators.pop_front();
        
        if(FS()._pullToCenter)
            pullToCenter();
        
        if(FS()._boundedToCircle)
            boundToCircle();
        
        applyForceToPredators();
        applyForceToParticles();
        
        for(list<Fish>::iterator it = _fishes.begin(); it != _fishes.end(); it++)
        {
            it->update();
        }
        
        for( list<Fish>::iterator p = _predators.begin(); p != _predators.end(); ++p )
        {
            p->update();
        }
    }
    
    void pullToCenter()
    {
        for( list<Fish>::iterator p = _fishes.begin(); p != _fishes.end(); ++p )
        {
            p->pullToCenter();
        }
        for( list<Fish>::iterator p = _predators.begin(); p != _predators.end(); ++p )
        {
            p->pullToCenter();
        }
    }
    
    void boundToCircle()
    {
        for( list<Fish>::iterator p = _fishes.begin(); p != _fishes.end(); ++p )
        {
            p->boundToCircle();
        }
        for( list<Fish>::iterator p = _predators.begin(); p != _predators.end(); ++p )
        {
            p->boundToCircle();
        }
    }
    
    void applyForceToParticles()
    {
        float twoPI = M_PI * 2.0f;
        _particleCentroid = ofVec2f(0.0);
        _nbParticles = _fishes.size();
        
        list<Fish>::iterator p1;
        
        // save iterators to an array named items
        int iSize = _fishes.size();
        //vector<Particle*> items;
        //items.reserve(iSize);
        std::valarray<Fish*> items(iSize);
        int l=0;
        for( p1 = _fishes.begin(); p1 != _fishes.end(); ++p1)
        {
            items[l] = &(*p1);
            //        cout<<items[l]->_pos;
            l++;
        }
#pragma omp parallel for default(shared)
        for (int i = 0; i < iSize; i++)
            //for( p1 = _fishes.begin(); p1 != _fishes.end(); ++p1)
        {
            
            
            Fish* p1 = items[i];
            //list<Fish>::iterator p2 = p1;
#pragma omp parallel for default(shared)
            for(int j = i+1; j < iSize; j++)
                //for( ++p2; p2 != _fishes.end(); ++p2 )
            {
                Fish* p2 = items[j];
                ofVec2f dir = p1->_pos - p2->_pos;
                float distSqrd = dir.lengthSquared();
                //float zoneRadiusSqrd = _zoneRadius * _zoneRadius;
                float zoneRadiusSqrd = FS()._zoneRadius * p1->_crowdFactor * FS()._zoneRadius * p2->_crowdFactor;
                if( distSqrd < zoneRadiusSqrd ){			// Neighbor is in the zone
                    float percent = distSqrd/zoneRadiusSqrd;
                    p1->addNeighborPos( p2->_pos );
                    p2->addNeighborPos( p1->_pos );
                    dir.normalize();
                    if( percent < FS()._lowThresh ){			// Separation
                        float F = ( FS()._lowThresh/percent - 1.0f ) * FS()._repelStrength;
                        dir *= F;
                        
                        p1->_acc += dir;
                        p2->_acc -= dir;
                    } else if( percent < FS()._highThresh ){	// Alignment
                        float threshDelta		= FS()._highThresh - FS()._lowThresh;
                        float adjustedPercent	= ( percent - FS()._lowThresh )/threshDelta;
                        float F					= ( 1.0 - ( cos( adjustedPercent * twoPI ) * -0.5f + 0.5f ) ) * FS()._alignStrength;
                        
                        p1->_acc += p2->_velNormal * F;
                        p2->_acc += p1->_velNormal * F;
                        
                    } else {								// Cohesion
                        float threshDelta		= 1.0f - FS()._highThresh;
                        float adjustedPercent	= ( percent - FS()._highThresh )/threshDelta;
                        float F					= ( 1.0 - ( cos( adjustedPercent * twoPI ) * -0.5f + 0.5f ) ) * FS()._attractStrength;
                        
                        dir *= F;
                        
                        p1->_acc -= dir;
                        p2->_acc += dir;
                    }
                }
            }
            
            _particleCentroid += p1->_pos;
            
            //ADD PERLIN NOISE
            //float speed = p1->_vel.squareLength();
            //float mul = ofMap(speed,0.0,_maxSpeed*_maxSpeed,0.0,10.0,true);
            
            ofVec2f perlin = FS()._perlin.dfBm(p1->_pos * FS()._scalePerlin / 10.0) * FS()._mulPerlin;
            p1->_acc += perlin;// * mul;
            
            
            //            // CHECK WHETHER THERE IS ANY PARTICLE/PREDATOR INTERACTION
            //            float eatDistSqrd = FS()._zoneRadius / 2.0;
            //            float predatorZoneRadiusSqrd = FS()._zoneRadius * FS()._zoneRadius * 5.0f;
            //
            //            for( list<Fish>::iterator predator = _predators.begin(); predator != _predators.end(); ++predator )
            //            {
            //                ofVec2f dir = p1->_pos - predator->_pos;
            //                float distSqrd = dir.lengthSquared();
            //
            //                if( distSqrd < predatorZoneRadiusSqrd )
            //                {
            //                    //				if( distSqrd > eatDistSqrd )
            //                    //                {
            //					float F = ( predatorZoneRadiusSqrd/distSqrd - 1.0f ) * 0.1f;
            //					p1->_fear += F * 0.1f;
            //					dir = dir.normalized() * F;
            //					p1->_acc += dir;
            //					if( predator->_isHungry )
            //						predator->_acc += dir * 0.04f * predator->_hunger;
            //                    //				}
            //                    //                else
            //                    //                {
            //                    //					p1->_isDead = true;
            //                    //					predator->_hunger = 0.0f;
            //                    //					predator->_isHungry = false;
            //                    //				}
            //                }
            //            }
            
            
        }
        
        _particleCentroid /= (float)_nbParticles;
    }
    
    void applyForceToPredators()
    {
        float twoPI = M_PI * 2.0f;
        _predatorCentroid = ofVec2f(0.0);
        _nbPredators = _predators.size();
        
        for( list<Fish>::iterator p1 = _predators.begin(); p1 != _predators.end(); ++p1 )
        {
            list<Fish>::iterator p2 = p1;
            
            for( ++p2; p2 != _predators.end(); ++p2 )
            {
                ofVec2f dir = p1->_pos - p2->_pos;
                float distSqrd = dir.lengthSquared();
                //float zoneRadiusSqrd = _zoneRadius * _zoneRadius;
                float zoneRadiusSqrd = FS()._zoneRadius * p1->_crowdFactor *FS(). _zoneRadius * p2->_crowdFactor;
                if( distSqrd < zoneRadiusSqrd ){			// Neighbor is in the zone
                    float percent = distSqrd/zoneRadiusSqrd;
                    dir.normalize();
                    p1->addNeighborPos( p2->_pos );
                    p2->addNeighborPos( p1->_pos );
                    
                    if( percent < FS()._lowThresh ){			// Separation
                        float F = ( FS()._lowThresh/percent - 1.0f ) * FS()._repelStrength;
                        dir *= F;
                        
                        p1->_acc += dir;
                        p2->_acc -= dir;
                    } else if( percent < FS()._highThresh ){	// Alignment
                        float threshDelta		= FS()._highThresh - FS()._lowThresh;
                        float adjustedPercent	= ( percent - FS()._lowThresh )/threshDelta;
                        float F					= ( 1.0 - ( cos( adjustedPercent * twoPI ) * -0.5f + 0.5f ) ) * FS()._alignStrength;
                        
                        p1->_acc += p2->_velNormal * F;
                        p2->_acc += p1->_velNormal * F;
                        
                    } else {								// Cohesion
                        float threshDelta		= 1.0f - FS()._highThresh;
                        float adjustedPercent	= ( percent - FS()._highThresh )/threshDelta;
                        float F					= ( 1.0 - ( cos( adjustedPercent * twoPI ) * -0.5f + 0.5f ) ) * FS()._attractStrength;
                        
                        dir *= F;
                        
                        p1->_acc -= dir;
                        p2->_acc += dir;
                    }
                }
            }
            
            _predatorCentroid += p1->_pos;
            
            //float speed = p1->_vel.squareLength();
            //float mul = ofMap(speed,0.0,_maxSpeed*_maxSpeed,0.0,10.0,true);
            
            ofVec2f perlin = FS()._perlin.dfBm(p1->_pos *FS()._scalePerlin / 10.0) * FS()._mulPerlin;
            p1->_acc += perlin;// * mul;
            
        }
        _predatorCentroid /= (float)_nbPredators;
    }
    
    void attractParticles(ofVec2f attractor)
    {
        for( list<Fish>::iterator p = _fishes.begin(); p != _fishes.end(); ++p )
        {
            p->attract(attractor);
        }
        for( list<Fish>::iterator p = _predators.begin(); p != _predators.end(); ++p )
        {
            p->attract(attractor);
        }
    }
    void repulseParticles(ofVec2f repulsor)
    {
        for( list<Fish>::iterator p = _fishes.begin(); p != _fishes.end(); ++p )
        {
            p->repulse(repulsor);
        }
        for( list<Fish>::iterator p = _predators.begin(); p != _predators.end(); ++p )
        {
            p->repulse(repulsor);
        }
    }
    
    virtual void draw()
    {
        for(list<Fish>::iterator it = _fishes.begin(); it != _fishes.end(); it++)
        {
            ofSetColor(ofColor::white);
            it->draw();
        }
    }
    
    virtual void drawDebug()
    {
        for(list<Fish>::iterator it = _fishes.begin(); it != _fishes.end(); it++)
        {
            ofSetColor(ofColor::white);
            it->drawDebug();
        }
    }
    
public:
    
    vector<Species> _species;
    int _currentSpecies;
    
    list<Fish> _fishes;
    list<Fish> _predators;
    
    ofVec2f _particleCentroid;
    float _nbParticles;
    
    int _maxParticles;
    
    ofVec2f _predatorCentroid;
    float _nbPredators;
    
    int _maxPredators;
};

#endif /* fishes_h */
