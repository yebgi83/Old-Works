// apGlutMouse.cpp
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdio.h>

int cube_point[] = 
{
    -1,-1,-1,
    1,-1,-1,
    1, 1,-1,
    -1, 1,-1,
    
    -1,-1, 1,
    1,-1, 1,
    1, 1, 1,
    -1, 1, 1,
};

int cube_index[] =
{
    // ¾Æ·§¸é  
    0,2,1,
    0,3,2,
    // µÞ¸é
    4,5,6,
    4,6,7,
    // ¿·¸é 
    0,5,4,
    0,1,5,
    
    1,6,5,
    1,2,6,
    
    2,7,6,
    2,3,7,
    
    3,4,7,
    3,0,4
};

unsigned char cube_color[] =
{
         255,0,0,
         0,255,0,
         0,0,255,
         255,255,0,
         255,0,255,
         0,255,255
};

void init(void)
{
     glClearColor( 0, 0, 0, 0 );
     glEnable( GL_DEPTH_TEST );
}

void display(void)
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     // gl_Begin : GL_TRIANGLES
     glBegin(GL_TRIANGLES); 
     
     int i, ni = 12;
     for( i = 0; i < ni ; i ++ )
     {
          glColor3ubv( &cube_color[ (i/2)*3 ] );
          
          int a, b, c;
          a = cube_index[i*3];
          b = cube_index[i*3+1];
          c = cube_index[i*3+2];
          glVertex3iv(&cube_point[a*3]);
          glVertex3iv(&cube_point[b*3]);
          glVertex3iv(&cube_point[c*3]);
     }          
     // glEnd
     glEnd();
          
     glutSwapBuffers();
     glFlush();
}

void reshape (int w, int h)
{
     glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glFrustum( -1.0, 1.0, -1.0, 1.0, 1.5, 20.0 );
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glTranslatef( 0, 0, -5 );
     glRotatef( -30, 0, 1, 0 );
}

void keyboard (unsigned char key, int x, int y )
{
     switch(key) 
     {
                 case 27:
                      exit(0);
                      break;
     }
}

void idle(void)
{
     static unsigned int t = 0;
     if( t + 17 < timeGetTime() )
     {
         glRotatef( 3, 1, 0, 0 );
         
         display();
         t = timeGetTime();
     }
     
     Sleep(1);
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize( 400, 400 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow("GLUT sample - simple cube");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}        
