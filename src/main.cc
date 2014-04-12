#include <iostream>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "fluid.hh"
using namespace std ;

void  init() ;
void  reshape( int , int ) ;
void  display() ;
void  Timer( int ) ;

double   FPS ;
fluid    Fluid ;
particle temp ;

int  main( int argc , char **argv )
{
    glutInit( &argc , argv ) ;
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ) ;
    glutInitWindowSize( 600 , 600 ) ;
    glutInitWindowPosition( 100 , 100 ) ;
    glutCreateWindow( "FLUID" ) ;
    init() ;
    glutTimerFunc( ( 1000 / ( int )FPS ) , Timer , 1 ) ;
    glutReshapeFunc( reshape ) ;
    glutDisplayFunc( display ) ;
    glutMainLoop() ;
    return 0 ;
}

void  Timer( int value )
{
    glutPostRedisplay();
    glutTimerFunc( int( 1000 / FPS ) , Timer , 1 ) ;
}

void  init()
{
    glClearColor( 0 , 0 , 0 , 0 ) ;

    FPS = Fluid.FPS ;

    for( int i = 0 ; i < 10 ; i ++ )
        for( int j = 0 ; j < 10 ; j ++ )
            for( int k = 0 ; k < 10 ; k ++ )
            {
                temp.position.x = i/10.0 ; temp.position.y = j/10.0 ; temp.position.z = k/10.0 ;
                temp.velocity.x = 0 ; temp.velocity.y = 0 ; temp.velocity.z = 0 ;
                temp.mass = 1 ;
                Fluid.particles.push_back( temp ) ;
            }
}

void  reshape( int w , int h )
{
    glViewport( 0 , 0 , w , h ) ;
    glMatrixMode( GL_PROJECTION ) ;
    glLoadIdentity() ;
    glFrustum( -10 , 10 , -10 , 10 , 1.5 , 20 ) ;
    glMatrixMode( GL_MODELVIEW ) ;
}

void  display()
{
    Fluid.next_frame() ;
    glClear( GL_COLOR_BUFFER_BIT ) ;
    glColor3f( 0 , 0 , 1 ) ;
    glLoadIdentity() ;
    gluLookAt( 0 , 0 , 2 ,
               0 , 0 , 0 ,
               0 , 1 , 0
               ) ;
    glBegin( GL_POINTS ) ;
    for( vector<particle> :: iterator iter = Fluid.particles.begin() ; iter != Fluid.particles.end() ; iter ++ )
    {
        glVertex3f( (*iter).position.x , (*iter).position.y , (*iter).position.z ) ;
    }
    glEnd() ;
    glutSwapBuffers() ;
}
