//
//  window.h
//  funambulus
//
//  Created by Benjamin Petit on 23/03/2017.
//
//

#ifndef window_h
#define window_h

#include "ofxQuadWarp.h"

class WWindow
{
    
public:
    
    WWindow()
    {
    }
    
    void setup(ofPoint pos, ofPoint size, ofPoint totalSize)
    {
        _pos = pos;
        _size = size;
        _totalSize = totalSize;
        
        update();
        
        _fbo.allocate(_totalSize.x*_size.x,_totalSize.y*_size.y,GL_RGBA);
        
        int w = _totalSize.x*_size.x;
        int h = _totalSize.y*_size.y;
        
        _warper.setSourceRect(ofRectangle(0, 0,w,h));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
        _warper.setTopLeftCornerPosition(ofPoint(_x,_y));             // this is position of the quad warp corners, centering the image on the screen.
        _warper.setTopRightCornerPosition(ofPoint(_x+_w,_y));        // this is position of the quad warp corners, centering the image on the screen.
        _warper.setBottomLeftCornerPosition(ofPoint(_x,_y+_h));      // this is position of the quad warp corners, centering the image on the screen.
        _warper.setBottomRightCornerPosition(ofPoint(_x+_w,_y+_h)); // this is position of the quad warp corners, centering the image on the screen.
        _warper.setup();
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
        beginWarp();
        ofSetColor(255);
        //_fbo.draw(_x,_y,_w,_h);
        _fbo.draw(0,0);
        endWarp();        
    }
    
    void beginWarp()
    {
        //======================== get our quad warp matrix.
        
        ofMatrix4x4 mat = _warper.getMatrix();
        
        //======================== use the matrix to transform our fbo.
        
        ofPushMatrix();
        ofMultMatrix(mat);
    }
    
    void endWarp()
    {
        ofPopMatrix();
    }
    
    void drawUnwarped()
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
        
        if(S()._warped)
        {
            ofSetColor(ofColor::magenta);
            _warper.drawQuadOutline();
            ofSetColor(ofColor::yellow);
            _warper.drawCorners();
            ofSetColor(ofColor::magenta);
            _warper.drawHighlightedCorner();
            ofSetColor(ofColor::red);
            _warper.drawSelectedCorner();
        }
    }
    
public:
    
    ofPoint _pos;
    ofPoint _size;
    ofPoint _totalSize;
    
    float _x,_y,_w,_h;
    
    ofFbo _fbo;
    
    ofxQuadWarp _warper;
};

#endif /* window_h */
