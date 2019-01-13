#include <stdio.h>     
#include <stdlib.h>
#include <time.h> 
#include "gl/glut.h"   
#include "visuals.h"   

 
int main(int argc, char* argv[])
{ 
  glutInit(&argc, argv);
     
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(1000,800);
  glutInitWindowPosition(400,150);
  glutCreateWindow("Solar");
   
  Setup();
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  glutIdleFunc(Idle);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(Special_Keys);
 
 
  glutMainLoop();
  return 0; 
}  