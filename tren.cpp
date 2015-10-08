
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

float c=0.0f;


GLfloat         alfa1, alfaS, alfaT ,t;         // Movimientos del Brazo
GLUquadric *q = gluNewQuadric();

void createView (int w, int h) {
    GLfloat fAspect = (GLfloat) w / (GLfloat) h; // Aspect ratio
    if (h == 0)
    {
	h = 1;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
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
    float luzAmb[4]={1,1,1,1};//Intensidad de la luz ambiental
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,luzAmb);
    glEnable(GL_LIGHT0);

    float light_pos[4]={0.0f ,0.0f, 0.0f ,1.0f};
    float light_Ka[4]={0.2f ,0.1f, 0.5f ,1.0f};
    float light_Kd[4]={0.2f ,0.1f, 0.5f ,1.0f};
    float light_Ks[4]={1.0f ,1.0f, 1.0f ,1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

    float vluz[4]={0.3,0.3,0.3,1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,vluz);

    printf("INIT OK\n");
}


void dibujaTren(float angulo)
{
    glPushMatrix();
    gluDisk(q,5.4,5.8,30,30);
    glRotatef(-angulo,0,0,1);
    glTranslated(0,5,0);
    //Bagon 1
    glBegin(GL_QUADS);
    glVertex2f(0,1);
    glVertex2f(0,0);
    glVertex2f(2,0);
    glVertex2f(2,1);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(2,.5);
    glVertex2f(2,0);
    glVertex2f(2.5,0);
    glVertex2f(2.5,.5);
    glEnd();
    //Spot
    float spotDir[]={1.0f,0.0f,0.0f};//White ligthe (x,y,z)
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,20.0f);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,120.0f);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-angulo,0,0,1);
    glTranslated(-2,5,0);
    glBegin(GL_QUADS);
    glVertex2f(0,1);
    glVertex2f(0,0);
    glVertex2f(2,0);
    glVertex2f(2,1);
    glEnd();
    glPopMatrix();
}

void figure()
{
    //Tren
    dibujaTren(alfaS);


    //Esfra1
    glPushMatrix();
    float colorFrente[4]={1,.64,0,1};
    float colorSombra[4]={1,.64,0,1};
    float colorReflejo[4]={1,.64,0,1};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,colorFrente);
    glMaterialfv(GL_FRONT,GL_AMBIENT,colorSombra);
    glMaterialfv(GL_FRONT,GL_SPECULAR,colorReflejo);
    glMaterialf(GL_FRONT,GL_SHININESS,10);
    glTranslatef(-4,0,0);
    glRotatef(2*alfa1,0,1,0);
    gluSphere(q,1,20,20);
    glPopMatrix();
    //Esfera2
    glPushMatrix();
    float colorFrente2[4]={0,.5,.2,1};
    float colorSombra2[4]={0,.5,.2,1};
    float colorReflejo2[4]={0,.5,.2,1};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,colorFrente2);
    glMaterialfv(GL_FRONT,GL_AMBIENT,colorSombra2);
    glMaterialfv(GL_FRONT,GL_SPECULAR,colorReflejo2);
    glMaterialf(GL_FRONT,GL_SHININESS,10);
    glTranslatef(4,0,0);
    glRotatef(2*alfa1,0,1,0);
    gluSphere(q,1,20,20);
    glPopMatrix();
    //Pendejadas
    glPushMatrix();
    float colorFrente3[4]={1,.5,.2,1};
    float colorSombra3[4]={1,.5,.2,1};
    float colorReflejo3[4]={1,.5,.2,1};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,colorFrente3);
    glMaterialfv(GL_FRONT,GL_AMBIENT,colorSombra3);
    glMaterialfv(GL_FRONT,GL_SPECULAR,colorReflejo3);
    glMaterialf(GL_FRONT,GL_SHININESS,10);
    glTranslatef(0,8,0);
    glRotatef(2*alfa1,0,1,0);
    gluSphere(q,1,20,20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-8,0);
    glRotatef(2*alfa1,0,1,0);
    gluSphere(q,1,20,20);
    glPopMatrix();

    alfa1+=0.01f;
    alfaS+=0.05f;

}

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

