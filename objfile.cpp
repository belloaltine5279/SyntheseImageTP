#include "objfile.h"
#include <string>
#include <sstream>
#include <map> 
#include "mesh.h"

using namespace std;
//-------------------------------------------
OBJFile::OBJFile(string initFileName)
{
this->fileName = initFileName ;
cout << "dans init OBJFile "<<endl;
}
//-------------------------------------------
OBJFile::OBJFile(void)
{

}
//-------------------------------------------
OBJFile::~OBJFile(void)
{


}
//-------------------------------------------
ostream& operator<<(ostream& os, const OBJFile& OBJf)
{
  
 }
//-------------------------------------------

void OBJFile::readData(void)
{
    string line;
    int nbVertices(0), nbFaces(0) ;
    VStruct *v ; 
    FStruct *f ; 


    ifstream myfile ("test.obj");
        if (myfile.is_open())
        {
          while ( getline (myfile,line) )
          {
              float x,y,z ;
              char carLine;

            cout << line << '\n';
            istringstream istr(line);
            istr >> carLine >> x >> y >> z ;

            switch(carLine){
              case 'v': 
                v->x = x ; 
                v->y = y ; 
                v->z = z ;  
                tabVertices.push_back(v) ; 

                break ; 
              case 'f':
                f->v0 = x ; 
                f->v1 = y ; 
                f->v2 = z ; 
                tabFaces.push_back(f) ; 
                break;  
              default: break ; 

            }

          //**********************************************************
          // AFAIRE
          // ici stoker ces info dans une structure de données
          //**********************************************************
          } //fin while getline
          myfile.close();
        }

        else cout << "Unable to open file";
this->constructTopology();
}
//-----------------------------------------------------

std::map<int, int> face_he(vector<int> lv){
  std::map<int, int> map_he;
  for(int i = 0; i < lv.size()-2; ++i){
      map_he[lv[0+i]] = lv[1+i];
      map_he[lv[1+i]] = lv[2+i];
      map_he[lv[2+i]] = lv[1+i]; 
    }
  }

void effacehalfegdesinliste(std::vector<HalfEdge *> *v , HalfEdge *h) {
  for(vector<HalfEdge *>::iterator it = v->begin() ; it != v->end() ; it++){
      if(*it == h)
        v->erase(it) ; 
  }
}

Mesh * OBJFile::constructTopology(void) 
{
    //**********************************************************
    // AFAIRE
    // ici exploiter les données du fichier OBJ pour construire les tableaux d'indices
    //**********************************************************

Mesh *ExMesh = new Mesh() ; 
Vertex *V  ;
Face *F = new Face();

HalfEdge *he = new HalfEdge(), *HeBord = new HalfEdge(), *he1 = new HalfEdge(), *he2 = new HalfEdge() , *he3 = new HalfEdge() ,*startHe = new HalfEdge() , *heTmp = new HalfEdge(); 
Vertex *v1;
vector <HalfEdge*> tmpHeListeHe ; 

for(int i = 0 ; i < tabVertices.size(); ++i){
  V = new Vertex(tabVertices[i]->x , tabVertices[i]->y , tabVertices[i]->z) ; 
  ExMesh->vertices.push_back(V) ; 
}

  std::vector<int> vx;
  std::map<int, int> maphe; 

  for(auto &f : tabFaces){
    vx.push_back(f->v0) ; 
    vx.push_back(f->v1);
    vx.push_back(f->v2); 

  maphe = face_he(vx) ; 
  for(auto &[key ,value] : maphe){
/*
  F = new Face(new HalfEdge(new Vertex(tabVertices[key]->x, tabVertices[key]->y, tabVertices[key]->z), new Vertex(tabVertices[value]->x , tabVertices[value]->y , tabVertices[value]->z))) ;  
  ExMesh->faces.push_back(F) ; 
  */

  he = new HalfEdge(new Vertex(tabVertices[key]->x , tabVertices[key]->y , tabVertices[key]->z), new Vertex(tabVertices[value]->x , tabVertices[value]->y, tabVertices[value]->z )) ;  

  v1 = new Vertex(tabVertices[key]->x, tabVertices[key]->y, tabVertices[key]->z) ; 
  he->vertex = v1 ;
  if(v1 -> oneHe == NULL)
    v1 -> oneHe -> vertex = v1 ; 
  ExMesh->hedges.push_back(he) ; 
  vx.clear() ;
  }

  he1 = ExMesh->hedges[1] ;
  he2 = ExMesh->hedges[2]; 
  he3 = ExMesh->hedges[3] ; 

  he1->heNext = he2 ; 
  he1->hePrev = he3 ; 
  he2->heNext = he3 ; 
  he2->hePrev = he1 ; 
  he3->heNext = he3 ; 
  he3->hePrev = he2 ; 

  he1->sommetarriver = he2->vertex ; 
  he2->sommetarriver = he3->vertex ; 
  he3->sommetarriver = he1->vertex ; 

  F->oneHe = he1 ; 
  he1->face = he2->face ; 
  he2->face = he3->face ; 
  he3->face = F ;  

  ExMesh->faces.push_back(F) ;
}

//fin pour chaque face 
tmpHeListeHe = ExMesh->hedges ; 


for(auto &arete : ExMesh->hedges){
  bool trouvee = false  ; 
  for(auto &tmparete : tmpHeListeHe){
    if(arete->vertex == tmparete->sommetarriver && arete->sommetarriver == arete->vertex){
      arete->heTwin = tmparete ; 
      tmparete->heTwin = arete ;
      // tmpHeListeHe.erase(tmparete) ; 
      // tmpHeListeHe.erase(arete) ; 
      effacehalfegdesinliste(&tmpHeListeHe, tmparete) ;  
      effacehalfegdesinliste(&tmpHeListeHe, arete) ;   
      trouvee = true ;
    }
  }
  if(trouvee == false){
    HeBord = new HalfEdge() ; 
    HeBord->vertex = arete->heNext->vertex ; 
    arete->heTwin = HeBord ; 
    HeBord->heTwin = arete ; 
    HeBord->face = NULL ; 
  }
}


startHe = new HalfEdge() ; 
heTmp = new HalfEdge() ; 

startHe = HeBord -> heTwin ; 
heTmp = startHe ; 
do{
  heTmp = heTmp->heTwin->heNext ; 
}while(heTmp->face != NULL) ; 


startHe = HeBord->heTwin ; 
heTmp = startHe ; 
do{
  heTmp=heTmp->hePrev->heTwin ;

}while(heTmp->face != NULL) ; 
HeBord->hePrev = heTmp ;

return ExMesh ; 

 /*ExMesh->faces.push_back(F) ; 
  number_face++ ;
  i++ ; 
*/

}


