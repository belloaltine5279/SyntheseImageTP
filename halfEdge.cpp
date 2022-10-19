#include "halfEdge.h"
#include <GL/glut.h>
#include <iostream>
// #include "../armadillo/include/armadillo"


//using namespace arma;
using namespace std;

//=========================================
HalfEdge::HalfEdge(void)
{


}
HalfEdge::HalfEdge(Vertex* InitVertex, string initName)
{
    this->vertex = InitVertex ;
    this->name = initName ;
}
//------------------------------------------
HalfEdge::~HalfEdge(void)
{
}

HalfEdge::HalfEdge(Vertex *dep , Vertex *arr){ 

  this->sommetdepart = dep ; 
  this->sommetarriver = arr ;
}


bool HalfEdge::operator==(const HalfEdge &h){
  return (this->sommetdepart == h.sommetdepart && this->sommetarriver == h.sommetarriver) ; 
}