#include "fluid.hh"
#include <iostream>
#include <math.h>
using namespace std ;

const double PI = 3.1415926 ;

fluid :: fluid()
{
    FPS = 24 ;
    time = 0 ;
    time_step = ( 1.0 / FPS ) / 50.0 ;
    h = 1 ;
}

void  fluid :: next_frame()
{
    for( int i = 0 ; i < 50 ; i ++ )
        next_moment() ;
    surface_reconstruct() ;
}


void  fluid :: next_moment()
{
    for( vector<particle> :: iterator iter = particles.begin() ; iter != particles.end() ; ++iter )
    {
        (*iter).density = get_density( *iter ) ;
    }

    for( vector<particle> :: iterator iter = particles.begin() ; iter != particles.end() ; ++ iter )
    {
        (*iter).position = (*iter).position + (*iter).velocity * time_step ;
        (*iter).velocity = (*iter).velocity + get_acceleration( *iter ) * time_step ;
    }
    time += time_step ;
}

double  fluid :: get_distance( const particle& a , const particle& b )
{
    double dis ;
    dis =  ( a.position.x - b.position.x ) * ( a.position.x - b.position.x )
          +( a.position.y - b.position.y ) * ( a.position.y - b.position.y )
          +( a.position.z - b.position.z ) * ( a.position.z - b.position.z ) ;
    dis = sqrt( dis ) ;
    return dis ;
}

double  fluid :: get_density( particle& P )
{
    double density = 0 ;
    double W ;
    for( vector<particle> :: iterator iter = particles.begin() ; iter != particles.end() ; ++iter )
    {
        double r = get_distance( P , *iter ) ;
        if( r > h ) W = 0 ;
        else        W = 315 * pow( ( h * h - r * r ) , 3 ) / ( 64 * PI * pow( h , 9 ) ) ;
        density += (*iter).mass * W  ;
    }
    return density ;
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
	vector3 tension( 0 , 0 , 0 ) ;
	vector3 Force ;
	double r ;
	for( vector< particle > :: iterator iter = particles.begin() ; iter != particles.end() ; iter ++ )
	{
		r = get_distance( P , *iter ) ;
		if( r > h ) continue ;

        Force = ( (*iter).position - P.position ) * ( k * cos( PI * r / ( 2 * h ) ) / r ) ;
        tension = tension + Force ;
	}
	return tension ;
}

vector3 fluid :: get_viscosity( const particle& P )
{
	vector3 viscosity( 0 , 0 , 0 ) ;
	double r , W ;
	for( vector< particle > :: iterator iter = particles.begin() ; iter != particles.end() ; iter ++ )
	{
		r = get_distance( P , *iter ) ;
		if( r > h ) W = 0 ;
		else 		W = 45 * ( h - r ) / ( PI * pow( h , 6 ) ) ;
		viscosity = viscosity + ( (*iter).velocity - P.velocity ) * u * P.mass * W / P.density ;
	}
	return viscosity ;
}

vector3 fluid :: get_external_force( const particle& P )
{
}

void  fluid :: surface_reconstruct()
{
}
