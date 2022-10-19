
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "halfEdge.h"
#include "vertex.h"
#include "face.h"
#include "mesh.h"
#include <vector>
#include <sstream>
#include"objfile.h"
#include <string>
#include <cstring>


using namespace std ;
void affichage(void);

void clavier(unsigned char touche,int x,int y);
void affiche_repere(void);

void mouse(int, int, int, int);
void mouseMotion(int, int);
//void reshape(int,int);


// variables globales pour OpenGL
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance=0.;


#define NBFACES 6
#define NBVERTICES 7
#define NBHALFEDGES 24
Mesh* ExMesh ;




//----------------------------------------------------------------------------------
void initMesh()
//----------------------------------------------------------------------------------
{
    int tabHe[NBHALFEDGES][5]={  // sommet, he, face, next, prev pour chaque demi-arete
        { 0,18, 0, 1, 2},
        { 2,11, 0, 2, 0},
        { 3,3 , 0, 0, 1},
        { 0, 2, 1, 4, 5},
        { 3, 6, 1, 5, 3},
        { 1,19, 1, 3, 4},
        { 1, 4, 2, 7, 8},
        { 3,17, 2, 8, 6},
        { 4,20, 2, 6, 7},
        { 2,21, 3,10,11},
        { 5,12, 3,11, 9},
        { 3, 1, 3, 9,10},
        { 3,10, 4,13,14},
        { 5,22, 4,14,12},
        { 6,15, 4,12,13},
        { 3,14, 5,16,17},
        { 6,23, 5,17,15},
        { 4, 7, 5,15,16},
        { 2, 0,-1,19,21},
        { 0, 5,-1,20,18},
        { 1, 8,-1,23,19},
        { 5, 9,-1,18,22},
        { 6,13,-1,21,23},
        { 4,16,-1,22,20}   };
    int tabFace[NBFACES] ={0,3,6,9,12,15}; // he pour chaque face
    double tabVertex[NBVERTICES][4] ={          // x,y,z, he pour chaque sommet
                            {0.1,0.4,0,0},
                            {0.3,0.4,0,5},
                            {0,0.2,0,1},
                            {0.2,0.2,0,2},
                            {0.4,0.2,0,8},
                            {0.1,0,0,10},
                            {0.3,0,0,14}};




   ExMesh = new Mesh() ;
    //***********************************************
    // AFAIRE

    for(int i=0;i<NBHALFEDGES;i++)
    {  string c="e"+to_string(i);
      ExMesh->hedges.push_back(new HalfEdge(nullptr,c));
    }
    for(int i=0;i<NBFACES;i++)
    {
      ExMesh->faces.push_back(new Face());
      ExMesh->faces[i]->oneHe=ExMesh->hedges[tabFace[i]];
    }

    for(int i=0;i<NBVERTICES;i++)
    {
    ExMesh->vertices.push_back(new Vertex(tabVertex[i][0],tabVertex[i][1],tabVertex[i][2]));
    ExMesh->vertices[i]->oneHe=ExMesh->hedges[tabVertex[i][3]];
    }


       for(int i=0;i<NBHALFEDGES;i++)
       {

        ExMesh->hedges[i]->vertex=ExMesh->vertices[tabHe[i][0]];
        ExMesh->hedges[i]->heTwin=ExMesh->hedges[tabHe[i][1]];
        ExMesh->hedges[i]->face=ExMesh->faces[tabHe[i][2]];
        ExMesh->hedges[i]->heNext=ExMesh->hedges[tabHe[i][3]];
        ExMesh->hedges[i]->hePrev=ExMesh->hedges[tabHe[i][4]];
       }

    //***********************************************
}



//----------------------------------------------------------------------------------
void initOpenGl()
//----------------------------------------------------------------------------------
{
initMesh();

//lumiere

	glClearColor( .5, .5, 0.5, 0.0 );

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat l_pos[] = { 3.,3.5,3.0,1.0 };
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos);

     glLightfv(GL_LIGHT0,GL_DIFFUSE,l_pos);
     glLightfv(GL_LIGHT0,GL_SPECULAR,l_pos);

     // glDepthFunc(GL_LESS);
     // glEnable(GL_DEPTH_TEST);
     glEnable(GL_COLOR_MATERIAL);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(45.0f,(GLfloat)200/(GLfloat)200,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
//	glScalef(.7,.7,.7);
    gluLookAt(0.,0.,4., 0.,0.,0., 0.,1.,0.);
  //  glTranslatef(0.0,0.0,-5.0);
}
void RedBordure()
{

     int tabINDICEBORD[7]={0,1,4,6,5,2,0};
     for(int i=0;i<NBVERTICES;i++)
     {
      glBegin(GL_LINES);
       glColor3f(1,0.0,0.0);
       double x1=ExMesh->vertices[tabINDICEBORD[i]]->x;double x2=ExMesh->vertices[tabINDICEBORD[(i+1)%NBVERTICES]]->x;
       double y1=ExMesh->vertices[tabINDICEBORD[i]]->y; double y2=ExMesh->vertices[tabINDICEBORD[(i+1)%NBVERTICES]]->y;
       double z1=ExMesh->vertices[tabINDICEBORD[i]]->z;double z2=ExMesh->vertices[tabINDICEBORD[(i+1)%NBVERTICES]]->z;
       glVertex3d(x1,y1,z1);
       glVertex3d(x2,y2,z2);
      glEnd();


    }
}
void calculvalence()
{
  for(int i=0;i<NBVERTICES;i++)
   { int valence=0;
	 for(int j=0;j<NBHALFEDGES;j++)
     {
        if(ExMesh->vertices[i]==ExMesh->hedges[j]->vertex)
		    	valence++;
      }
      printf("la valence du sommet %d est %d\n",i+1,valence);
    }
}
//------------------------------------------------------
void displayHalfEdge(void)
//----------------------------------------------------------------------------------
{
    //**********************************************************************
//Dessin
   for(int i=0;i<NBFACES;i++)
     {
      glBegin(GL_TRIANGLE_STRIP);
       glColor3f(0,i%2,0.0);
       double x1=ExMesh->faces[i]->oneHe->hePrev->vertex->x, x2=ExMesh->faces[i]->oneHe->vertex->x, x3=ExMesh->faces[i]->oneHe->heNext->vertex->x;
       double y1=ExMesh->faces[i]->oneHe->hePrev->vertex->y, y2=ExMesh->faces[i]->oneHe->vertex->y, y3=ExMesh->faces[i]->oneHe->heNext->vertex->y;
       double z1=ExMesh->faces[i]->oneHe->hePrev->vertex->z, z2=ExMesh->faces[i]->oneHe->vertex->z, z3=ExMesh->faces[i]->oneHe->heNext->vertex->z;

       glVertex3d(x1,y1,z1);

       glVertex3d(x2,y2,z2);

       glVertex3d(x3,y3,z3);
      glEnd();
    }
    //mettre les bordure en rouge
RedBordure();

//calcul de la valence
calculvalence();
//**********************************************************************


}
int main(int argc,char **argv)
{

  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(600,600);
  glutCreateWindow("ifs");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(1.0);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);

initOpenGl() ;

/* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}
//------------------------------------------------------
void affiche_repere(void)
{
  glBegin(GL_LINES);
  glColor3f(1.0,0.0,0.0);
  glVertex2f(0.,0.);
  glVertex2f(1.,0.);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(0.0,1.0,0.0);
  glVertex2f(0.,0.);
  glVertex2f(0.,1.);
  glEnd();
   glBegin(GL_LINES);
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.,0.,0.);
  glVertex3f(0.,0.,1.);
  glEnd();
}

//-----------------------------------------------------



//------------------------------------------------------
void affichage(void)
{
	glMatrixMode(GL_MODELVIEW);
  /* effacement de l'image avec la couleur de fond */
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0,0,cameraDistance);
    glRotatef(cameraAngleX,1.,0.,0.)	;
    glRotatef(cameraAngleY,0.,1.,0.);
    //--------------------------------
    affiche_repere();
    //--------------------------------
   displayHalfEdge();
    //--------------------------------

    glPopMatrix();
  /* on force l'affichage du resultat */
  glFlush();
}

//------------------------------------------------------


//------------------------------------------------------
void clavier(unsigned char touche,int x,int y)
{

  switch (touche)
    {
    case '+':
      glutPostRedisplay();
      break;
    case '-':
      glutPostRedisplay();
      break;
    case 'f': //* affichage en mode fil de fer
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
      case 'p': //* affichage du carre plein
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
  case 's' : //* Affichage en mode sommets seuls
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'q' : //*la touche 'q' permet de quitter le programme
      exit(0);
    }

}
void mouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if(state == GLUT_UP)
            mouseMiddleDown = false;
    }
}


void mouseMotion(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}
