//
//  window.h
//  funambulus
//
//  Created by Benjamin Petit on 23/03/2017.
//
//

#ifndef window_h
#define window_h

class Window
{
    
public:
    
    Window()
    {
    }
    
    void setup(ofPoint pos, ofPoint size, ofPoint totalSize)
    {
        _pos = pos;
        _size = size;
        _totalSize = totalSize;
        
        _fbo.allocate(_totalSize.x*_size.x,_totalSize.y*_size.y,GL_RGBA);
    }
    
    void update()
    {
        float sw = ofGetWidth();
        float sh = ofGetHeight();
        
        float fw;
        float fh;
        //cout<<sw<<" "<<sh<<" -- "<<_w<<" "<<_h<<endl;
        if(sw > sh)
        {
            fw = sh * _totalSize.x / (float) _totalSize.y;
            fh = sh;
        }
        else
        {
            fw = sw;
            fh = sw * _totalSize.y / (float) _totalSize.x;
        }
        
        _x = (sw - fw) /2.0 + fw * _pos.x;
        _y = (sh - fh) /2.0 + fh * _pos.y;
        _w = fw * _size.x;
        _h = fh * _size.y;
        
        //cout<<sw<<" "<<sh<<" -- "<<fw<<" "<<fh<<" -- "<<_w<<" "<<_h<<endl;
    }
    
    void begin()
    {
        _fbo.begin();
        ofClear(0);
    }
    
    void end()
    {
        _fbo.end();
    }
    
    void draw()
    {
        ofSetColor(255);
        _fbo.draw(_x,_y,_w,_h);
    }
    
    void drawDebug()
    {
        ofSetColor(ofColor::red);
        ofNoFill();
        ofDrawRectangle(_x,_y,_w,_h);
        ofFill();
    }
    
public:
    
    ofPoint _pos;
    ofPoint _size;
    ofPoint _totalSize;
    
    float _x,_y,_w,_h;
    
    ofFbo _fbo;
};

#endif /* window_h */
