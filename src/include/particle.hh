#ifndef PARTICLE_HH_INCLUDED
#define PARTICLE_HH_INCLUDED

#include "vector.hh"

class particle
{
	public :
		vector3 position , velocity ;
		double  mass  ;
    public :
        particle() ;
        particle( vector3 Position , vector3 Velocity ) ;
        particle( vector3 Position , vector3 Velocity , double Mass ) ;
} ;

#endif
