#ifndef __MESH
#define __MESH

#include <vector>
#include "vertex.h"
#include "halfEdge.h"
#include "face.h"
#include <string>
//#include <GL/glut.h>


using namespace std ;

class Vertex ;
class HalfEdge ;
class Face ;

class Mesh
{
public:
        vector <Vertex*> vertices;
        vector <HalfEdge*> hedges ;
        vector <Face*> faces;
        Mesh();
        ~Mesh();
//MeshAttribut attributs ;
};


#endif
