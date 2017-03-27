#ifndef PERLIN_H
#define PERLIN_H

#include "ofVec2f.h"
#include "ofVec3f.h"

class Perlin
{
public:
	Perlin( uint8_t aOctaves = 4 );
	Perlin( uint8_t aOctaves, int32_t aSeed );
    
	void	setSeed( int32_t aSeed );
	uint8_t	getOctaves() const { return mOctaves; }
	void	setOctaves( uint8_t aOctaves ) { mOctaves = aOctaves; }
    
	/// Class Perlin look: fractal Brownian motion by summing 'mOctaves' worth of noise
	float	fBm( float v ) const;
	float	fBm( const ofVec2f &v ) const;
	float	fBm( float x, float y ) const { return fBm( ofVec2f( x, y ) ); }
	float	fBm( const ofVec3f &v ) const;
	float	fBm( float x, float y, float z ) const { return fBm( ofVec3f( x, y, z ) ); }
    
	/// Derivative of fractal Brownian motion, corresponding with the values returned by fBm()
    //	float	dfBm( float v ) const;
	ofVec2f	dfBm( const ofVec2f &v ) const;
	ofVec2f	dfBm( float x, float y ) const { return dfBm( ofVec2f( x, y ) ); }
	ofVec3f	dfBm( const ofVec3f &v ) const;
	ofVec3f	dfBm( float x, float y, float z ) const { return dfBm( ofVec3f( x, y, z ) ); }
    
	/// Calculates a single octave of noise
	float	noise( float x ) const;
	float	noise( float x, float y ) const;
	float	noise( float x, float y, float z ) const;
    
	/// Calculates the derivative of a single octave of noise
    //	float	dnoise( float x ) const;
	ofVec2f	dnoise( float x, float y ) const;
	ofVec3f	dnoise( float x, float y, float z ) const;
    
private:
	void	initPermutationTable();
    
	float grad( int32_t hash, float x ) const;
	float grad( int32_t hash, float x, float y ) const;
	float grad( int32_t hash, float x, float y, float z ) const;
    
	uint8_t		mOctaves;
	int32_t		mSeed;
    
	uint8_t		mPerms[512];
};

#endif //PERLIN_H
