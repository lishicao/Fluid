#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "fluid.hh"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std ;

void  init() ;
void  reshape( int , int ) ;
void  display() ;
void  Timer( int ) ;

int   	 FPS ;
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
    //Fluid.field_force = vector3( 0 , -10 , 0 ) ;
    face obj ;
    obj.point1 = vector3( 0 , -0.5 , 2 ) ;
    obj.point2 = vector3( 2 , -0.5 , -2 ) ;
    obj.point3 = vector3( -2 , -0.5 , -2 ) ;
    //Fluid.objects.push_back( obj ) ;
    for( int i = 0 ; i < 5 ; i ++ )
        for( int j = 0 ; j < 5 ; j ++ )
            for( int k = 0 ; k < 5 ; k ++ )
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
    glFrustum( -1 , 1 , -1 , 1 , 1 , 100 ) ;
    glMatrixMode( GL_MODELVIEW ) ;
}

void  display()
{
    Fluid.next_frame() ;
    glClear( GL_COLOR_BUFFER_BIT ) ;
    glColor3f( 0 , 0 , 1 ) ;
    glLoadIdentity() ;
    gluLookAt( 0 , 0 , 3 ,
               0 , 0 , 0 ,
               0 , 1 , 0
               ) ;
    glBegin( GL_POINTS ) ;
    for( vector<particle> :: iterator iter = Fluid.particles.begin() ; iter != Fluid.particles.end() ; iter ++ )
    {
        glVertex3f( (*iter).position.x , (*iter).position.y , (*iter).position.z ) ;
    }
    glEnd() ;
    glColor3f( 0 , 1 , 1 ) ;
    glPolygonMode( GL_FRONT_AND_BACK , GL_LINE ) ;
    glBegin( GL_POLYGON ) ;
	for( vector<face> :: iterator iter = Fluid.objects.begin() ; iter != Fluid.objects.end() ; iter ++ )
    {
        glVertex3f( (*iter).point1.x , (*iter).point1.y , (*iter).point1.z ) ;
        glVertex3f( (*iter).point2.x , (*iter).point2.y , (*iter).point2.z ) ;
        glVertex3f( (*iter).point3.x , (*iter).point3.y , (*iter).point3.z ) ;
    }
    glEnd() ;
    glutSwapBuffers() ;
}

/*
ofstream fout ;

int  main()
{
    string   filename ;
    fluid    Fluid ;
    particle temp ;
    Fluid.field_force = vector3( 0 , -10 , 0 ) ;
    face obj ;

    obj.point1 = vector3( 0 , -0.5 , 5 ) ;
    obj.point2 = vector3( 5 , -0.5 , -5 ) ;
    obj.point3 = vector3( -5 , -0.5 , -5 ) ;
    Fluid.objects.push_back( obj ) ;
    for( int i = 0 ; i < 15 ; i ++ )
        for( int j = 0 ; j < 15 ; j ++ )
            for( int k = 0 ; k < 15 ; k ++ )
            {
                temp.position.x = i/10.0 ; temp.position.y = j/10.0 ; temp.position.z = k/10.0 ;
                temp.velocity.x = 0 ; temp.velocity.y = 0 ; temp.velocity.z = 0 ;
                temp.mass = 1 ;
                Fluid.particles.push_back( temp ) ;
            }
    for( int i = 0 ; i < 60 ; i ++ )
    {
        for( int j = 0 ; j < Fluid.FPS ; j ++ )
        {
            cout << i << " second  " << j << "'th frame" << endl ;
            string second , frame ;
            if( i >= 10 ) {
                second = ( '0' + i / 10 )  ;
                second+= ( '0' + i % 10 ) ;
            }
            else second =  ( '0' + i ) ;
            if( j >= 10 ) {
                frame = ( '0' + j / 10 ) ;
                frame+= ( '0' + j % 10 ) ;
            }
            else frame =  ( '0' + j ) ;
            filename = "data" ;
            filename += "/" + second + "." + frame ;

            fout.open( filename.c_str() ) ;

            Fluid.next_frame() ;
            for( vector<particle>:: iterator iter = Fluid.particles.begin() ; iter != Fluid.particles.end() ; iter ++ )
            {
                fout << (*iter).position.x << " " << (*iter).position.y << " " << (*iter).position.z << endl ;
            }
            fout.close() ;
        }
    }
    return 0 ;
}*/
