#include "vector.hh"

#include <cmath>

vector3 :: vector3( double X , double Y , double Z )
{
    x = X ; y = Y ; z = Z ;
}

void  vector3 :: normalize()
{
    if( x == 0 && y == 0 && z == 0 ) return ;
    else {
        double length = sqrt( x * x + y * y + z * z ) ;
        x /= length ; y /= length ; z /= length ;
    }
}

vector3& vector3 :: operator = ( const vector3& rhs )
{
    x = rhs.x ; y = rhs.y ; z = rhs.z ;
    return *this ;
}

vector3 vector3 :: operator + ( const vector3& rhs )
{
    vector3 Vector ;
    Vector.x = x + rhs.x ;
    Vector.y = y + rhs.y ;
    Vector.z = z + rhs.z ;
    return Vector ;
}

vector3 vector3 :: operator - ( const vector3& rhs )
{
    vector3 Vector ;
    Vector.x = x - rhs.x ;
    Vector.y = y - rhs.y ;
    Vector.z = z - rhs.z ;
    return Vector ;
}

vector3 vector3 :: operator * ( const vector3& rhs )
{
    vector3 Vector ;
    Vector.x = y * rhs.z - z * rhs.y ;
    Vector.y = z * rhs.x - x * rhs.z ;
    Vector.z = x * rhs.y - y * rhs.x ;
    return Vector ;
}

vector3 vector3 :: operator * ( const double& value )
{
    vector3 Vecter ;
    Vecter.x = x * value ;
    Vecter.y = y * value ;
    Vecter.z = z * value ;
    return Vecter ;
}

vector3 vector3 :: operator / ( const double& value )
{
    vector3 Vecter ;
    Vecter.x = x / value ;
    Vecter.y = y / value ;
    Vecter.z = z / value ;
    return Vecter ;
}

void  vector3 :: Rotate( double alpha , vector3 dir )
{
    dir.normalize() ;
    double n1 = dir.x , n2 = dir.y , n3 = dir.z ;
    double X = x , Y = y , Z = z ;
    x =   X * ( n1 * n1 + ( 1 - n1 * n1 ) * cos( alpha ) )
        + Y * ( n1 * n2 * ( 1 - cos( alpha ) ) - n3 * sin( alpha ) )
        + Z * ( n1 * n3 * ( 1 - cos( alpha ) ) + n2 * sin( alpha ) ) ;

    y =   X * ( n1 * n2 * ( 1 - cos( alpha ) ) + n3 * sin( alpha ) )
        + Y * ( n2 * n2 + ( 1 - n2 * n2 ) * cos( alpha ) )
        + Z * ( n2 * n3 * ( 1 - cos( alpha ) ) - n1 * sin( alpha ) ) ;

    z =   X * ( n1 * n3 * ( 1 - cos( alpha ) ) - n2 * sin( alpha ) )
        + Y * ( n2 * n3 * ( 1 - cos( alpha ) ) + n1 * sin( alpha ) )
        + Z * ( n3 * n3 + ( 1 - n3 * n3 ) * cos( alpha ) ) ;
}

double vector3 :: dot( const vector3& V )
{
    double result = x * V.x + y * V.y + z * V.z ;
    return result ;
}

