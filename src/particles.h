//
//  particles.h
//  funambulus
//
//  Created by Benjamin Petit on 24/03/2017.
//
//

#ifndef particles_h
#define particles_h

#include "ofxMovieClip.h"

class Species
{
    
public:
    Species(string dir,string name)
    {
        setup(dir,name);
    }
    
    ~Species()
    {
    }
    
    void setup(string dir,string name)
    {
        _imgSeq.loadAndCreateSequence(dir.c_str(),name.c_str());
        _hasImgSeq = _imgSeq.assetCollectionSize>0;
    }
    
public:
    
    ofxTextureImageSequenceLoader _imgSeq;
    bool _hasImgSeq;
};

class Particles
{
    
public:
    
    Particles()
    {
        
    }
    
    virtual void setup(string path)
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

#endif /* particles_h */
