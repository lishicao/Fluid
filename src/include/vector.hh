#ifndef VECTOR_HH_INCLUDED
#define VECTOR_HH_INCLUDED

class vector3
{
    public :
        double  x , y , z ;

    public :
        vector3( double , double , double ) ;
        vector3() {} ;
        void  normalize() ;
        vector3& operator= ( const vector3& rhs ) ;
        vector3 operator+ ( const vector3& ) ;
        vector3 operator- ( const vector3& ) ;
        vector3 operator* ( const vector3& ) ;
        vector3 operator* ( const double& ) ;
        vector3 operator/ ( const double& ) ;
        void Rotate( double , vector3 ) ;
        double dot( const vector3& ) ;
} ;

#endif
