#ifndef FLUID_HH_INCLUDED
#define FLUID_HH_INCLUDED

#include <vector>
#include "particle.hh"
#include "face.hh"

using namespace std ;

class fluid
{
	public :
		vector < particle > particles ;
		vector < face > objects ;
        vector < face > surface ;

        vector3 field_force ;

        double  time , time_step ;
        int     FPS ;

	public :
        fluid() ;
		void     next_frame() ;
    private :
        void     next_moment() ;
        void     surface_reconstruct() ;
        vector3  get_acceleration( const particle& ) ;
        vector3  get_pressure( const particle& ) ;
        vector3  get_tension( const particle& ) ;
        vector3  get_viscosity( const particle& ) ;
        vector3  get_external_force( const particle& ) ;
} ;

#endif
