#include "face.hh"
#include <math.h>
using namespace std ;

face :: face()
{
}

face :: face( vector3 Point1 , vector3 Point2 , vector3 Point3 )
{
    point1 = Point1 ;
    point2 = Point2 ;
    point3 = Point3 ;
}

double face :: get_distance( const particle& P )
{
    vector3 Normal , VEC , position ;
    vector3 A , B ;
    double  distance , length , COS ;
    position = P.position ;
    A = point2 - point1 ;
    B = point3 - point1 ;
    Normal = A.cross( B ) ;
    VEC = position - point1 ;
    COS = Normal.dot( VEC ) / ( Normal.length() * VEC.length() )  ;
    length = VEC.length() ;
    distance = fabs( COS ) * length ;
    return distance ;
}

vector3 face :: get_normal()
{
    vector3 Normal , A , B ;
    A = point2 - point1 ;
    B = point3 - point1 ;
    Normal = A.cross( B ) ;
    return Normal ;
}
