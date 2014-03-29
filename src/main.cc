#include <iostream>
#include <string.h>
#include "fluid.hh"
using namespace std ;

int  main()
{
    fluid Fluid ;
    particle temp ;
    Fluid.field_force.x = 0 ; Fluid.field_force.y = -10 ; Fluid.field_force.z = 0 ;
    for( int i = 0 ; i < 10 ; i ++ )
        for( int j = 0 ; j < 10 ; j ++ )
            for( int k = 0 ; k < 10 ; k ++ )
            {
                temp.position.x = i/10.0 ; temp.position.y = j/10.0 ; temp.position.z = k/10.0 ;
                temp.velocity.x = 0 ; temp.velocity.y = 0 ; temp.velocity.z = 0 ;
                temp.mass = 1 ;
                Fluid.particles.push_back( temp ) ;
            }
    for( int time = 0 ; time != 10 ; time ++ )
        for( int i = 0 ; i < Fluid.FPS ; i ++ )
        {
            Fluid.next_frame() ;
            vector<particle>::iterator iter = Fluid.particles.begin() ;
            cout << (*iter).position.x << " " << (*iter).position.y << " " << (*iter).position.z << endl ;
        }
	return 0 ;
}
