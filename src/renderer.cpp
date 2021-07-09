/* Genetic algorithm test */

#include <iostream>
#include <thread>
#include <math.h>
#include "renderer.h"
#include "fgetter.h"

using namespace std;

//resolution
#define width 1024
#define height 768

int main()
{
    C_3DObj O_mapStuff = C_3DObj(3,1);//create O_mapStuff
    C_nCalc O_calcultron;   //create a normals calc object.
    O_mapStuff.verts[0] = -11;//x
    O_mapStuff.verts[1] = 11;//y
    O_mapStuff.verts[2] = -11;//z
    O_mapStuff.verts[3] = 11;//x
    O_mapStuff.verts[4] = 11;//y
    O_mapStuff.verts[5] = -11;//z
    O_mapStuff.verts[6] = 0;//x
    O_mapStuff.verts[7] = 11;//y
    O_mapStuff.verts[8] = 11;//z
    O_mapStuff.faces[0] = 0;//V1
    O_mapStuff.faces[1] = 1;//V2
    O_mapStuff.faces[2] = 2;//V3
    O_mapStuff.numOfFaces = 1;  //One face for this test.
    O_calcultron.normalsCalc(O_mapStuff, 0);   //Calculate normals of an object.
    cout << "\n Normals \n" << O_mapStuff.normals[0] << "\n" << O_mapStuff.normals[1] << "\n" << O_mapStuff.normals[2] << "\n";
    return 0;
}
