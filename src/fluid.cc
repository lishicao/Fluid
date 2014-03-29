#include "fluid.hh"
#include <iostream>
using namespace std ;

fluid :: fluid()
{
    FPS = 24 ;
    time = 0 ;
    time_step = ( 1.0 / FPS ) / 50.0 ;
}

void  fluid :: next_frame()
{
    for( int i = 0 ; i < 50 ; i ++ )
        next_moment() ;
    surface_reconstruct() ;
}


void  fluid :: next_moment()
{
    for( vector<particle> :: iterator iter = particles.begin() ; iter != particles.end() ; ++ iter )
    {
        (*iter).position = (*iter).position + (*iter).velocity * time_step ;
        (*iter).velocity = (*iter).velocity + get_acceleration( *iter ) * time_step ;
    }
    time += time_step ;
}

vector3 fluid :: get_acceleration( const particle& P )
{
    vector3 net_force , pressure , tension , viscosity , external_force ;

    pressure       = get_pressure( P ) ;
    tension        = get_tension( P ) ;
    viscosity      = get_viscosity( P ) ;
    external_force = get_external_force( P ) ;
    net_force = pressure + tension + viscosity + field_force * P.mass + external_force ;

    return ( net_force / P.mass ) ;
}

vector3 fluid :: get_pressure( const particle& P )
{
}

vector3 fluid :: get_tension( const particle& P )
{
}

vector3 fluid :: get_viscosity( const particle& P )
{
}

vector3 fluid :: get_external_force( const particle& P )
{
}

void  fluid :: surface_reconstruct()
{
}
