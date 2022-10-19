#ifndef OBJFILE_H
#define OBJFILE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mesh.h" 

class Mesh; 
using namespace std;
typedef struct
{
    int vIndex ;
    int heTwinIndex ;
    int faceIndex ;
    int heNextIndex ;
    int hePrevIndex ;
} HeStruct;

typedef struct
{
    double x,y,z ; 
} VStruct;

typedef struct
{
    int v0, v1, v2 ;
} FStruct;

class OBJFile
{
public:
    vector<HeStruct*> tabHalfEdges ;
    vector<FStruct*> tabFaces;
    vector<VStruct*> tabVertices;
    string fileName ;
    Mesh * ExMesh ; 
    OBJFile(void);
    OBJFile(string initFileName);
    ~OBJFile(void);
    void readData(void) ;
    Mesh * constructTopology(void); 
    friend ostream& operator<<(ostream& os, const OBJFile& OBJf) ;
};



#endif // OBJFILE_H
