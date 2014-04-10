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

/*
TODO
*/

vector3 fluid :: get_pressure( const particle& P )
{
    vector3 pressure( 0 , 0 , 0 ) ;
    vector3 Force ;
    double r ;
    for( vector<particle> :: iterator iter = particles.begin() ; iter != particles.end() ; iter ++ )
    {
        r = get_distance( P , *iter ) ;
        if( r > h ) continue ;
    }
    return pressure ;
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


/*someting todo*/
vector3 fluid :: get_external_force( particle P )
{
    vector3 external_force( 0 , 0 , 0 ) , Force ;
    vector3 Normal , p1 , p2 , point , Nor1 , Nor2 ;
    double  r ;
    for( vector<face> :: iterator iter = objects.begin() ; iter != objects.end() ; iter ++ )
    {

        r = (*iter).get_distance( P ) ;

        /*
         *   if face *iter should push particle P
         */
        if( r > h ) continue ;
        Normal = (*iter).get_normal() ;

        // obtain a projection of point P on face *iter
        p1 = P.position + Normal * r ;
        p2 = P.position - Normal * r ;
        if( ( (*iter).point1 - p1 ).length() < ( (*iter).point1 - p2 ).length() ) point = p1 ;
        else point = p2 ;

        // if the projection is in the face *iter (a trangle)
        Nor1 = ( (*iter).point1 - point ).cross( (*iter).point2 - (*iter).point1 ) ;
        Nor2 = ( (*iter).point2 - point ).cross( (*iter).point3 - (*iter).point2 ) ;
        if( Nor1.x*Nor2.x < 0 || Nor1.y*Nor2.y || Nor1.z*Nor2.z ) continue ;

        Nor1 = Nor2 ;
        Nor2 = ( (*iter).point3 - point ).cross( (*iter).point1 - (*iter).point3 ) ;
        if( Nor1.x*Nor2.x < 0 || Nor1.y*Nor2.y || Nor1.z*Nor2.z ) continue ;

        /*
         *  obtain the pressure
         */
        if( ( (*iter).point1 - p1 ).length() < ( (*iter).point1 - p2 ).length() )
        {
            Normal.x = -Normal.x ;
            Normal.y = -Normal.y ;
            Normal.z = -Normal.z ;
        }
        Force = Normal * ( B * ( pow( ( 0.1 / r ) , 7 ) - 1 ) )  ;

        external_force += Force ;
    }
    external_force += field_force ;
    return external_force ;
}



void  fluid :: surface_reconstruct()
{
}
