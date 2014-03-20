#include <iostream>
#include "vector.hh"
#include <string.h>
using namespace std ;

int  main()
{
	vector3 vector ;
	vector.x = 2 ; vector.y = 4 ; vector.z = 6 ;
	cout << vector.x << " " << vector.y << " " << vector.z  << endl ; 
	vector.normalize() ;
	cout << vector.x << " " << vector.y << " " << vector.z  << endl ; 
	return 0 ;
}  
