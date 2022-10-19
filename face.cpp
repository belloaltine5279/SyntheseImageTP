#include "face.h"
#include <GL/glut.h>
#include <iostream>
#include <string>
// #include "../armadillo/include/armadillo"


//using namespace arma;
using namespace std;



Face::Face()
{
}
Face::Face(HalfEdge * InitHe, string initName)
{
    this->oneHe = InitHe;
    this->name = initName ;
     
}

Face::~Face()
{

}
