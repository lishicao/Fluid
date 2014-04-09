#ifndef FACE_HH_INCLUDED
#define FACE_HH_INCLUDED

#include "particle.hh"
#include "vector.hh"

class face
{
    public :
        vector3 point1 , point2 , point3 ;
        double  a , b , c , d ;
    public :
        face() ;
        face( vector3 , vector3 , vector3 ) ;
        double  get_distance( const particle& ) ;
        vector3 get_normal() ;
        void    get_equation() ;
} ;

#endif
