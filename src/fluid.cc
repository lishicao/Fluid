#include "fluid.hh"
#include <math.h>
#include <iostream>

using namespace std ;

const double PI = 3.1415926 ;


fluid :: fluid()
{
    FPS = 24 ;
    Time = 0 ;
    time_step = ( 1.0 / FPS ) / 50.0 ;
    h = 0.3 ;
    u = 0.1 ;
    k = 0.01 ;
    B = 500 ;
    stable_density = 1000  ;
    field_force = vector3( 0 , 0 , 0 ) ;
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
    Time += time_step ;
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



double  fluid :: get_density( particle P )
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


/*vector3 fluid :: get_pressure( particle P )
{
    vector3 pressure( 0 , 0 , 0 ) ;
    vector3 Force , direction ;
    double  W , r , pi , pj ;
    pi = B * ( pow( ( P.density / stable_density ) , 7 ) - 1 ) ;
    for( vector<particle> :: iterator iter = particles.begin() ; iter != particles.end() ; iter ++ )
    {
        direction = P.position - (*iter).position ;
        direction.normalize() ;
        r = get_distance( P , *iter ) ;
        pj = B * ( pow( ( (*iter).density / stable_density ) , 7 ) - 1 ) ;
        if( r > h ) continue ;
        if( r < 0.00001 ) continue ;
        W = ( -45 * ( h - r ) * ( h - r ) ) / ( PI * pow( h , 6 ) ) ;
        Force = direction * ( - (*iter).mass * ( pi + pj ) * W / ( 2 * (*iter).density ) ) ;
        pressure += Force ;
    }
    return pressure ;
}*/


vector3 fluid :: get_pressure( particle P )
{
    vector3 pressure( 0 , 0 , 0 ) ;
    vector3 Force , direction ;
    double  W , r , pi , pj ;
    pi = B * ( pow( ( P.density / stable_density ) , 7 ) - 1 ) ;
    for( vector<particle> :: iterator iter = particles.begin() ; iter != particles.end() ; iter ++ )
    {
        direction = P.position - (*iter).position ;
        direction.normalize() ;
        r = get_distance( P , *iter ) ;
        pj = B * ( pow( ( (*iter).density / stable_density ) , 7 ) - 1 ) ;
        if( r > h ) continue ;
        if( r < 0.00001 ) continue ;
        W = ( -45 * ( h - r ) * ( h - r ) ) / ( PI * pow( h , 6 ) ) ;
        Force = direction * ( - (*iter).mass * W * ( pi / ( P.density * P.density ) + pj / ( (*iter).density * (*iter).density ) ) ) ;
        pressure += Force ;
    }
    return pressure ;
}



vector3 fluid :: get_tension( const particle& P )
{
	vector3 tension( 0 , 0 , 0 ) ;
	vector3 Force , direction ;
	double r , W ;
	for( vector< particle > :: iterator iter = particles.begin() ; iter != particles.end() ; iter ++ )
	{
		r = get_distance( P , *iter ) ;
		if( r > h ) continue ;
		if( r < 0.00001 ) continue ;
		W = 315 * ( pow( ( h * h - r * r ) , 3 ) ) / ( 64 * PI * pow( h , 9 ) )  ;
		direction = (*iter).position - P.position ;
		direction.normalize() ;
        Force = direction * ( P.mass * W * k )  ;
        tension = tension + Force ;
	}
	return tension ;
}

/*
vector3 fluid :: get_tension( const particle& P )
{
	vector3 tension( 0 , 0 , 0 ) ;
	vector3 Force , direction ;
	double r ;
	for( vector< particle > :: iterator iter = particles.begin() ; iter != particles.end() ; iter ++ )
	{
		r = get_distance( P , *iter ) ;
		if( r > h ) continue ;
		if( r < 0.00001 ) continue ;
		direction = ( (*iter).position - P.position ) ;
		direction.normalize() ;
 	    Force = ( (*iter).position - P.position ) * ( k * cos( PI * r / ( 2 * h ) ) / r ) ;
    	tension = tension + Force ;
	}
	return tension ;
}
*/



vector3 fluid :: get_viscosity( const particle& P )
{
	vector3 viscosity( 0 , 0 , 0 ) ;
	vector3 Force ;
	double r , W ;
	for( vector< particle > :: iterator iter = particles.begin() ; iter != particles.end() ; iter ++ )
	{
		r = get_distance( P , *iter ) ;
		if( r < 0.00001 ) continue ;
		if( r > h ) continue ;
		W = 45 * ( h - r ) / ( PI * pow( h , 6 ) ) ;
		Force = ( (*iter).velocity - P.velocity ) * u * P.mass * W / P.density ;
		viscosity = viscosity + Force ;
	}
	return viscosity ;
}



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
        if( r < 0.00000001 ) continue ;
        Normal = (*iter).get_normal() ;

        // obtain a projection of point P on face *iter
        p1 = P.position + Normal * r ;
        p2 = P.position - Normal * r ;
        if( ( (*iter).point1 - p1 ).length() < ( (*iter).point1 - p2 ).length() ) point = p1 ;
        else point = p2 ;

        // if the projection is in the face *iter (a trangle)
        Nor1 = ( (*iter).point1 - point ).cross( (*iter).point2 - (*iter).point1 ) ;
        Nor2 = ( (*iter).point2 - point ).cross( (*iter).point3 - (*iter).point2 ) ;
        if( Nor1.x*Nor2.x < 0 || Nor1.y*Nor2.y < 0 || Nor1.z*Nor2.z < 0 ) continue ;

        Nor1 = Nor2 ;
        Nor2 = ( (*iter).point3 - point ).cross( (*iter).point1 - (*iter).point3 ) ;
        if( Nor1.x*Nor2.x < 0 || Nor1.y*Nor2.y < 0 || Nor1.z*Nor2.z < 0 ) continue ;

        /*
         *  obtain the pressure
         */
        if( ( (*iter).point1 - p1 ).length() < ( (*iter).point1 - p2 ).length() )
        {
            Normal.x = -Normal.x ;
            Normal.y = -Normal.y ;
            Normal.z = -Normal.z ;
        }
        if( r < h )
          Force = Normal * ( B * ( pow( ( h / r ) , 7 ) - 1 ) )  ;
		//Force = Normal * ( B * pow( ( 0.1 / r ) , 7 ) ) ;
        //else Force = vector3( 0 , 0 , 0 ) ;

        external_force += Force ;
    }
    return external_force ;
}



void  fluid :: surface_reconstruct()
{
}
