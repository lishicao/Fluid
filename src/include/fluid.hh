#ifndef FLUID_HH_INCLUDED
#define FLUID_HH_INCLUDED

#include <vector>
#include "particle.hh"
#include "face.hh"

using namespace std ;

class fluid
{
	public :
		vector < particle > particles ;		// particles are particle in fluid
		vector < face > objects ;			// objects are mesh of solid
        vector < face > surface ;			// surface is mesh of fluid

        vector3 field_force ;

        double  time , time_step , h  ;     // h is randius of kernel
        double  u , k , B ; 				// u is viscosity friction , k is surface tension friction , B is pressure friction
        double  stable_density ;
        int     FPS ;

	public :
        fluid() ;
		void     next_frame() ;
    private :
        void     next_moment() ;
        void     surface_reconstruct() ;
        double   get_distance( const particle& , const particle& ) ;
        double   get_density( particle& ) ;
        vector3  get_acceleration( const particle& ) ;
        vector3  get_pressure( const particle& ) ;
        vector3  get_tension( const particle& ) ;
        vector3  get_viscosity( const particle& ) ;
        vector3  get_external_force( particle ) ;
} ;

#endif
