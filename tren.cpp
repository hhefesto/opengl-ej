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

void createView (int w, int h) {
    GLfloat fAspect = (GLfloat) w / (GLfloat) h; // Aspect ratio
    // Prevent A Divide By Zero By
    if (h == 0)
    {
	h = 1;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Setting up orthographic projection or gluPerspective
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
    //        x, y, z, ver x, y, z , 
    //  if (w <= h) glOrtho (-10.0, 10.0, -10 / fAspect, 10.0 / fAspect, 10.0, -10.0);
    //  else glOrtho (-10 * fAspect, 10.0 * fAspect, -10.0, 10.0, 10.0, -10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    printf("CREATEVIEW OK\n");
}

void init() {
    // Set background to black
    glShadeModel(GL_FLAT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f );
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //glEnable(GL_NORMALIZE);

    //float light_pos[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    float light_pos[4] = { -5.0f, 5.0f, 7.0f, 1.0f };
    float light_Ka[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float light_Kd[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float light_Ks[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

    printf("INIT OK\n");
}

void dibujaFlecha()
{
    glBegin(GL_TRIANGLES);								// Drawing Using Triangles

    glVertex3f( 0.0f, 2.0f, -5);					// Top
    glVertex3f(-2.0f, 0.0f, -5);					// Bottom Left
    glVertex3f( 2.0f, 0.0f, -5);					// Bottom Right

    glEnd();											// Finished Drawing The Triangle


    glBegin(GL_QUADS);									// Draw A Quad
    glVertex3f(-1.0f, 0.0f, -5.0f);					// Top Left
    glVertex3f( 1.0f, 0.0f, -5.0f);					// Top Right
    glVertex3f( 1.0f,-1.0f, -5.0f);					// Bottom Right
    glVertex3f(-1.0f,-1.0f, -5.0f);					// Bottom Left
    glEnd();											// Done Drawing The Quad

}

void ej6()
{
    glRotatef(45.0f,0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 5.0f, 0.0f);
    dibujaFlecha();
    glLoadIdentity();

    glRotatef(45.0f + 90.0f,0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 5.0f, 0.0f);
    dibujaFlecha();
    glLoadIdentity();

    glRotatef(45.0f + 180.0f,0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 5.0f, 0.0f);
    dibujaFlecha();
    glLoadIdentity();

    glRotatef(45.0f + 270.0f,0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 5.0f, 0.0f);
    dibujaFlecha();
}


void figure() {
    // flecha

    ej6();

    // SOL
    //GLUquadric *q = gluNewQuadric();
    //  glRotatef(alfa, 0, 1, 1);
    //glRotatef(alfa, 0, 1, 0);
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

    //glTranslate(x,y,z);
    //glRotate(alfa, x in 1 or 0, y in 1 or 0, z in 1 or 0);
    //glScale(x, y, z);

    // glMaterialf(GL_BACK, GL_DIFFUSE, 10);
    // glMaterialf(GL_BACK, GL_AMBIENT, 10);
    // glMaterialf(GL_BACK, GL_SPECULAR, 10);
    // glMaterialf(GL_BACK, GL_SHININESS, 10);
    //gluSphere(q, 3, 10, 10);

    //  glDisable(GL_LIGHT0);
    //gluCylinder(q, 3, 5, 10, 50, 50);
    //  gluDisk(q, 0, 4, 40, 40);
    // glBegin(GL_QUADS);
    // glVertex3f(-2,2,0);
    // glVertex3f(-2,-2,0);
    // glVertex3f(2,-2,0);
    // glVertex3f(2,2,0);
    // glEnd();
    //alfa += 0.5f;

    //     glBegin(GL_TRIANGLES);								// Drawing Using Triangles
    // glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
    // glVertex3f( 0.0f, 1.0f, -5);					// Top
    // glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Green
    // glVertex3f(-1.0f,-1.0f, -5);					// Bottom Left
    // glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
    // glVertex3f( 1.0f,-1.0f, -5);					// Bottom Right
    // glEnd();											// Finished Drawing The Triangle

    // alfa += 0.5f;


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
    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    init();
    glutTimerFunc(100, timer, 0);
    glutMainLoop();

    return 0;
}
// tres vistas(física, proyección, modelo)
//matrices de transformación (rot, translación, escala)
//matriz afin
