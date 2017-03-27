//
//  scenarii.h
//  funambulus
//
//  Created by Benjamin Petit on 24/03/2017.
//
//

#ifndef scenarii_h
#define scenarii_h

#include "floor.h"
#include "horizon.h"

#include "particles.h"
#include "fishes.h"

class Scenario
{

public:
    
    Scenario(string path)
    {
        setup(path);
    }
    
    void setup(string path)
    {
        cout<<"SCENARIO: "<<path<<endl;
        
        _path = path;
        
        _horizon.setup(_path);
        _earth.setup(_path);
        
        _pos = ofPoint(-0.5,0.5);
    }
    
    void setupGui()
    {
        gui.addPage(_path);
        gui.addTitle("Particles");
        _particles->setupGui();
    }
    
    void start()
    {
        cout<<"\tSTARTING SCENARIO: "<<_path<<endl;
        
        _horizon.start();
        _earth.start();
    }
    
    void stop()
    {
        _horizon.stop();
        _earth.stop();
    }
    
    void update(vector<Augmenta::Person*>& people)
    {
        if(people.size() > 0)
        {
            _pos = people[0]->centroid;
        }
        
        _horizon.update(_pos.x);
        _earth.update(_pos.x);
        
        if(_particles != NULL)
            _particles->update(people);
    }
    
    void drawFloor()
    {
        _earth.draw();
        
        if(_particles != NULL)
            _particles->draw();
    }
    
    void drawWall()
    {
        _horizon.draw();
    }
    
    void drawDebug()
    {
        
    }
    
public:
    
    string _path;
    
    ofPoint _pos;
    
    Particles* _particles;
    
    Horizon _horizon;
    Floor _earth;
    
};

class Scenarii
{
    
public:
    
    Scenarii()
    {
    }
    
    void setup()
    {
        _scenarii.push_back(Scenario("0_UNLOCK"));
        _scenarii.back()._particles = new Fishes;
        _scenarii.back()._particles->setup("0_UNLOCK");
        
        _currentScenario = 0;
        _started = false;
    }
    
    void setupGui()
    {
        for(auto s : _scenarii)
        {
            s.setupGui();
        }
    }
    
    void start()
    {
        cout<<"STARTING EXPERIENCE"<<endl;
        
        _currentScenario = 0;
        _started = true;
        
        _scenarii[_currentScenario].start();
    }
    
    void stop()
    {
        _scenarii[_currentScenario].stop();
        
        _currentScenario = 0;
        _started = false;
    }
    
    void next()
    {
        _scenarii[_currentScenario].stop();
        
        _currentScenario++;
        
        if(_currentScenario >= _scenarii.size())
            stop();
        else
            _scenarii[_currentScenario].start();
    }
    
    void restart()
    {
        stop();
        start();
    }
    
    void update(vector<Augmenta::Person*>& people)
    {
        if(_started)
        {
            _scenarii[_currentScenario].update(people);
        }
    }
    
    void drawFloor()
    {
        if(_started)
        {
            _scenarii[_currentScenario].drawFloor();
        }
    }
    
    void drawWall()
    {
        if(_started)
        {
            _scenarii[_currentScenario].drawWall();
        }
    }
    
    void drawDebug()
    {

    }
    
public:
    
    vector<Scenario> _scenarii;
    
    int _currentScenario;
    
    bool _started;
    
};

#endif /* scenarii_h */
