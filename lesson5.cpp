#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "math3d.h"
#include <stdio.h>

static const int FPS = 60;
int flagFigure = 0;
int flagTimer = 0;
int flagRenderScene = 0;

float alfa = 0;

void figure() {

  glLoadIdentity();
  GLUquadric *q = gluNewQuadric();
  //  glRotatef(alfa, 0, 1, 1);
  glRotatef(alfa, 0, 1, 0);
  //propiedades del material
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  //  glEnable(GL_CULL_FACE);
  
  float colorFrente[4] = {0,1,0,1};
  float colorSombra[4] = {0,0.5f,0.2f,1};
  float colorReflejo[4] = {1,1,1,1};
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colorFrente);
  glMaterialfv(GL_FRONT, GL_AMBIENT, colorSombra);
  glMaterialfv(GL_FRONT, GL_SPECULAR, colorReflejo);
  glMaterialf(GL_FRONT, GL_SHININESS, 10);

  
  // glMaterialf(GL_BACK, GL_DIFFUSE, 10);
  // glMaterialf(GL_BACK, GL_AMBIENT, 10);
  // glMaterialf(GL_BACK, GL_SPECULAR, 10);
  // glMaterialf(GL_BACK, GL_SHININESS, 10);
  gluSphere(q, 3, 50, 50);

  //  glDisable(GL_LIGHT0);
  //gluCylinder(q, 3, 5, 10, 50, 50);
  //  gluDisk(q, 0, 4, 40, 40);
  // glBegin(GL_QUADS);
  // glVertex3f(-2,2,0);
  // glVertex3f(-2,-2,0);
  // glVertex3f(2,-2,0);
  // glVertex3f(2,2,0);
  // glEnd();
  alfa += 0.5f;

}

//handler
void renderScene () {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  figure();
  // Flsuh drawing commands (draws the images on the screen)
  glFlush();
    if(flagRenderScene == 0)
    {
      flagRenderScene = 1;
      printf("FIGURE OK\n");
    }
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
  gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
  gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
  //  if (w <= h) glOrtho (-10.0, 10.0, -10 / fAspect, 10.0 / fAspect, 10.0, -10.0);
  //  else glOrtho (-10 * fAspect, 10.0 * fAspect, -10.0, 10.0, 10.0, -10.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  printf("CREATEVIEW OK\n");
}

void setup () {
  // Set background to black
  glShadeModel(GL_FLAT);
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f );
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  //float light_pos[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
  float light_pos[4] = { -5.0f, 5.0f, 7.0f, 1.0f };
  float light_Ka[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float light_Kd[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float light_Ks[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

  printf("SETUP OK\n");
}

void timer(int v)
{
  glutPostRedisplay();
  glutTimerFunc(1000/FPS, timer, v);
  if(flagTimer == 0)
    {
      flagTimer = 1;
      printf("TIMER OK\n");
    }
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
