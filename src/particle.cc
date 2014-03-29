#include "particle.hh"

particle :: particle()
{
    mass = 1 ;
}

particle :: particle( vector3 Position , vector3 Velocity )
{
    position = Position ;
    velocity = Velocity ;
    mass = 1 ;
}

particle :: particle( vector3 Position , vector3 Velocity , double Mass )
{
    position = Position ;
    velocity = Velocity ;
    mass = Mass ;
}
