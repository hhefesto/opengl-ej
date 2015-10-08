#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "math3d.h"

float alfa = 0;
static const int FPS = 60;

void dibujaFlecha()
{
    
}

void figure() {
  //  glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
  //  glLoadIdentity();
  glRotatef(alfa, 0, 0, 1);

  glBegin(GL_TRIANGLES);								// Drawing Using Triangles
  glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
  glVertex3f( 0.0f, 1.0f, -5);					// Top
  glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Green
  glVertex3f(-1.0f,-1.0f, -5);					// Bottom Left
  glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
  glVertex3f( 1.0f,-1.0f, -5);					// Bottom Right
  glEnd();											// Finished Drawing The Triangle

  alfa += 0.5f;


  //  glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only

  //  glBegin(GL_QUADS);									// Draw A Quad
  //  glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
  //  glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
  //  glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
  //  glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
  //  glEnd();											// Done Drawing The Quad
}

//handler
void renderScene () {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  figure();

  // Flsuh drawing commands (draws the images on the screen)
  glFlush();
}

void createView (int w, int h) {
  GLfloat fAspect = (GLfloat) w / (GLfloat) h; // Aspect ratio
  if (h == 0)										// Prevent A Divide By Zero By
  {
    h = 1;										// Making Height Equal One
  }

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Setting up orthographic projection or gluPerspective
  gluPerspective(45.0f,(GLflkloat)w/(GLfloat)h,0.1f,100.0f);
  //  if (w <= h) glOrtho (-10.0, 10.0, -10 / fAspect, 10.0 / fAspect, 10.0, -10.0);
  //  else glOrtho (-10 * fAspect, 10.0 * fAspect, -10.0, 10.0, 10.0, -10.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void setup () {
  // Set background to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void timer(int v)
{
  glutPostRedisplay();
  glutTimerFunc(1000/FPS, timer, v);
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800,600);
  glutCreateWindow("Getting Started with 3D");

  glutReshapeFunc(createView);
  glutDisplayFunc(renderScene);
  setup();
  glutTimerFunc(100, timer, 0);
  glutMainLoop();

  return 0;
}
