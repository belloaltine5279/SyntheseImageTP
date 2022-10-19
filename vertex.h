#ifndef __VERTEX
#define __VERTEX

#include "halfEdge.h"
#include <string>
//#include <GL/glut.h>
using namespace std;
class HalfEdge ;

class Vertex
{
public :
double x,y,z;
HalfEdge* oneHe ;
string name ;
int valence;
//VertexAttribut attribut ;
Vertex();
Vertex(double x, double y, double z);
Vertex(int x, int y, int z,string InitName);
~Vertex();

bool operator==(const Vertex *&) ; 

};

#endif
