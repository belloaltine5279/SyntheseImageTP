#include "vertex.h"
#include <GL/glut.h>
#include <iostream>
// #include "../armadillo/include/armadillo"


//using namespace arma;
using namespace std;

//=========================================
Vertex::Vertex()
{

	}
Vertex::Vertex(double x, double y, double z)
{
    this->x = x ;
    this->y = y ;
    this->z = z ;
}
Vertex::Vertex(int x, int y, int z,string InitName)
{
    this->x = (double) x ;
    this->y = (double) y ;
    this->z = (double) z ;
    this->name = InitName ;
    this->valence=0;
}

Vertex::~Vertex()
{

        }

bool Vertex::operator==(const Vertex *&v) {
    return (this->x == v->x && this->y == v->y && this->z == v->z) ; 
}