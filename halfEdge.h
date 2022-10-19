#ifndef __HALFEGDE
#define __HALFEGDE

#include "vertex.h"
#include "face.h"
#include "string.h"

//#include "./armadillo/include/armadillo"

//#include <GL/glut.h>

using namespace std ;
class Vertex ;
class Face ;
class Vertex ;

class HalfEdge
{
public:
  Vertex *sommetdepart ;
Vertex* vertex ;
HalfEdge* heNext ;
HalfEdge* hePrev ;
HalfEdge* heTwin ;
Vertex *sommetarriver; 
Face* face ;
string name;
HalfEdge(void);
HalfEdge(Vertex* InitVertex, string initName);
HalfEdge(Vertex* depart , Vertex *arriver) ; 
~HalfEdge(void);

bool operator==(const HalfEdge &) ; 
};




#endif
