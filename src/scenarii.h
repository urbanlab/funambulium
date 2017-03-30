//
//  scenarii.h
//  funambulus
//
//  Created by Benjamin Petit on 24/03/2017.
//
//

#ifndef scenarii_h
#define scenarii_h

#include "ofxScreenCurtain.h"

#include "floor.h"
#include "horizon.h"

#include "particles.h"
//#include "effect.h"
#include "leaves.h"
#include "fishes.h"

class Scenario
{

public:
    
    Scenario(string path, bool interactiveHorizon = false)
    {
        setup(path, interactiveHorizon);
    }
    
    void setup(string path, bool interactiveHorizon = false)
    {
        cout<<"SCENARIO: "<<path<<endl;
        
        _path = path;
        
        _horizon.setup(_path, interactiveHorizon);
        _earth.setup(_path, interactiveHorizon);
        
        _pos = ofPoint(-0.5,0.5);
        _someoneIn = false;
        
        _particlesFloor = NULL;
        _particlesWall = NULL;
        //_effect = NULL;
        
        _hasEffect = false;
    }
    
    void setupGui()
    {
        gui.addPage(_path);
        //if(_effect != NULL)
        //{
        //    gui.addTitle("Effect");
        //    _effect->setupGui();
        //}
        if(_particlesFloor != NULL)
        {            
            _particlesFloor->setupGui();
        }
        if(_particlesWall != NULL)
        {
            _particlesWall->setupGui();
        }
    }
    
    void start()
    {
        cout<<"\tSTARTING SCENARIO: "<<_path<<endl;
        
        _horizon.start();
        _earth.start();
        if(_particlesFloor != NULL)
            _particlesFloor->start();
        if(_particlesWall != NULL)
            _particlesWall->start();
        //if(_effect != NULL)
        //    _effect->stop();
    }
    
    void stop()
    {
        cout<<"\tSTOPING SCENARIO: "<<_path<<endl;
        
        _horizon.stop();
        _earth.stop();
        if(_particlesFloor != NULL)
            _particlesFloor->stop();
        if(_particlesWall != NULL)
            _particlesWall->stop();
        //if(_effect != NULL)
        //    _effect->stop();
    }
    
    void update(vector<Augmenta::Person*>& people)
    {
        if(people.size() > 0)
        {
            _pos = people[0]->centroid;
            _someoneIn = true;
        }
        else
        {
            _someoneIn = false;
        }
        
        _horizon.update(_pos.x);
        _earth.update(_pos.x,_someoneIn);
        
        if(_particlesFloor != NULL)
            _particlesFloor->update(people);
        if(_particlesWall != NULL)
            _particlesWall->update(people);
        
        //if(_effect != NULL)
        //    _effect->update(people);
    }
    
    void drawFloor()
    {
        _earth.draw();
        
        if(_particlesFloor != NULL)
            _particlesFloor->draw();
        
        //if(_effect != NULL)
        //    _effect->draw();
    }
    
    void drawWall()
    {
        _horizon.draw();
        
        if(_particlesWall != NULL)
            _particlesWall->draw();
    }
    
    void drawDebug()
    {
        
    }
    
public:
    
    string _path;
    
    ofPoint _pos;
    bool _someoneIn;
    
    Particles* _particlesFloor;
    Particles* _particlesWall;
    //Effect* _effect;
    
    Horizon _horizon;
    Floor _earth;
    
    bool _hasEffect;
};

class Scenarii
{
    
public:
    
    Scenarii()
    {
    }
    
    void setup()
    {
        _scenarii.push_back(Scenario("_IDLE"));
        
        _scenarii.push_back(Scenario("0_UNLOCK",true));
        
        _scenarii.push_back(Scenario("1_FORET"));
        _scenarii.back()._particlesFloor = new Leaves;
        _scenarii.back()._particlesFloor->setup("1_FORET");
    
        _scenarii.push_back(Scenario("2_LAC"));
        //_scenarii.back()._effect = new RippleEffect;
        //_scenarii.back()._effect->setup();
        //_scenarii.back()._effect->setTexture(_scenarii.back()._earth._bgI);
        _scenarii.back()._hasEffect = true;
        _scenarii.back()._particlesFloor = new Fishes;
        _scenarii.back()._particlesFloor->setup("2_LAC");
        _scenarii.back()._particlesWall = new Feathers;
        _scenarii.back()._particlesWall->setup("2_LAC");
        
        _scenarii.push_back(Scenario("3_FINAL",true));
        
        _currentScenario = 0;
        _scenarii[_currentScenario].start();
        _started = false;
        
        _curtain.setup(ofColor::black,ofRectangle(0,0,S()._xRes,S()._yRes));
    }
    
    void setupGui()
    {
        for(auto s : _scenarii)
        {
            s.setupGui();
        }
    }
    
    void callStart()
    {
        _curtain.dropCurtain(S()._fadeDuration);
        _callStart = true;
    }
    
    void start()
    {
        cout<<"STARTING EXPERIENCE"<<endl;
        
        _scenarii[_currentScenario].stop();
        
        _currentScenario = 1;
        _started = true;
        
        _scenarii[_currentScenario].start();
        
        _callStart = false;
        
        _curtain.raiseCurtain(S()._fadeDuration,true);
    }
    
    void callStop()
    {
        _scenarii[_currentScenario].stop();
        
        _currentScenario = 0;
        _scenarii[_currentScenario].start();
        
        _started = false;
    }
    
    void stop()
    {
        _currentScenario = 0;
        _scenarii[_currentScenario].start();
        
        _started = false;
    }
    
    void callNext()
    {
        if(_started)
        {
            _curtain.dropCurtain(S()._fadeDuration);
            _callNext = true;
        }
    }
    
    void next()
    {
        if(_started)
        {
            _scenarii[_currentScenario].stop();
            
            _currentScenario++;
            
            if(_currentScenario >= _scenarii.size())
                stop();
            else
                _scenarii[_currentScenario].start();
            
            _curtain.raiseCurtain(S()._fadeDuration,true);
        }
        
        _callNext = false;
    }
    
    void restart()
    {
        stop();
        start();
    }
    
    void update(vector<Augmenta::Person*>& people)
    {
        if(_callStart && _curtain.curtainIsDown())
        {
            start();
        }
        
        if(_started)
        {
            if(_callNext && _curtain.curtainIsDown())
            {
                next();
            }
            
            _scenarii[_currentScenario].update(people);
        }
        else
        {
            _scenarii[0].update(people);
        }
        
        _curtain.update(0.016666f);
    }
    
    void drawFloor()
    {
        //if(_started)
        {
            _scenarii[_currentScenario].drawFloor();
            _curtain.draw();
        }
    }
    
    void drawWall()
    {
        //if(_started)
        {
            _scenarii[_currentScenario].drawWall();
            _curtain.draw();
        }
    }
    
    void drawDebug()
    {

    }
    
public:
    
    vector<Scenario> _scenarii;
    
    int _currentScenario;
    
    bool _started;

    bool _callStart;
    bool _callNext;
    
    ofxScreenCurtain _curtain;
};

#endif /* scenarii_h */
