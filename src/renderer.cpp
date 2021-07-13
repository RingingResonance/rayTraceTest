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
    C_3DObj* O_mapStuff[16];//create O_mapStuff pinter.
    O_mapStuff[0] = new C_3DObj(3,1);
    C_nCalc O_calcultron;   //create a normals calc object.
    O_mapStuff[0]->verts[0] = -11;//x
    O_mapStuff[0]->verts[1] = 11;//y
    O_mapStuff[0]->verts[2] = -11;//z
    O_mapStuff[0]->verts[3] = 11;//x
    O_mapStuff[0]->verts[4] = 11;//y
    O_mapStuff[0]->verts[5] = -11;//z
    O_mapStuff[0]->verts[6] = 0;//x
    O_mapStuff[0]->verts[7] = 11;//y
    O_mapStuff[0]->verts[8] = 11;//z
    O_mapStuff[0]->faces[0] = 0;//V1
    O_mapStuff[0]->faces[1] = 1;//V2
    O_mapStuff[0]->faces[2] = 2;//V3
    O_mapStuff[0]->numOfFaces = 1;  //One face for this test.
    O_calcultron.normalsCalc(O_mapStuff, 0, 0);   //Calculate normals of an object.
    cout << "\n Normals \n" << O_mapStuff[0]->normals[0] << "\n" << O_mapStuff[0]->normals[1] << "\n" << O_mapStuff[0]->normals[2] << "\n";
    return 0;
}

    /** Calculate Normals. **/
    /** ThreadCount of 0 or 1 means only 1 single thread. **/
void C_nCalc::normalsCalc(C_3DObj* O_objIn, int threadNum, int threadCount){
    unsigned int faceIndex = 0;
    unsigned int vertIndex = 0;
    double workingVert[3][3];
    int f = threadNum;  //Start index at thread number.

    /** Process each face with it's own thread unless 'threadNum' == 0 **/
    while(f < O_objIn[0]->numOfFaces){
        for(int i=0;i<3;++i){
            vertIndex = O_objIn[0]->faces[(faceIndex * 3) + i];
            for(int n=0;n<3;++n){
                workingVert[n][i] = O_objIn[0]->verts[(vertIndex * 3) + n];
            }
        }
        /** e1 = v1 - v0 and e2 = v2 - v0 **/
        double e1[3];
        double e2[3];

        for(int i=0;i<3;++i)e1[i] = workingVert[i][1] - workingVert[i][0];
        for(int i=0;i<3;++i)e2[i] = workingVert[i][2] - workingVert[i][0];

        /** Vector3D out; out.x=a[1]*b[2]-a[2]*b[1]; out.y=a[2]*b[0]-a[0]*b[2]; out.z=a[0]*b[1]-a[1]*b[0]; return out; }` **/
        O_objIn[0]->normals[(f*3)+0] = (e1[1] * e2[2]) - (e1[2] * e2[1]);
        O_objIn[0]->normals[(f*3)+1] = (e1[2] * e2[0]) - (e1[0] * e2[2]);
        O_objIn[0]->normals[(f*3)+2] = (e1[0] * e2[1]) - (e1[1] * e2[0]);

        //Scale 0 - 1
        /** `float length = std::sqrt( vector.x*vector.x + vector.y*vector.y + vector.z*vector.z );` **/
        double length = 0;
        length = sqrt((O_objIn[0]->normals[(f*3)+0] * O_objIn[0]->normals[(f*3)+0]) + (O_objIn[0]->normals[(f*3)+1] * O_objIn[0]->normals[(f*3)+1]) + (O_objIn[0]->normals[(f*3)+2] * O_objIn[0]->normals[(f*3)+2]));
        /** Scale each vector **/
        for(int i=0;i<3;++i) O_objIn[0]->normals[(f*3)+i] = O_objIn[0]->normals[(f*3)+i] * (1 / length);

        /** Skip faces that aren't assigned to this thread **/
        if (threadCount == 0)f++;
        else f = f + threadCount;
    }
}
