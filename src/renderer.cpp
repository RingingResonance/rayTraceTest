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
    C_mapObjStatic O_mapStuff = C_mapObjStatic(5,5);
    O_mapStuff.faces[1] = 0;
    return 0;
}

/** Pretty self explanatory. Get the normal vector of a plane with 3 verts **/
void getNormalOfPlane(double v0[3], double v1[3], double v2[3]){

    /** e1 = v1 - v0 and e2 = v2 - v0 **/
    double e1[3];
    double e2[3];
    double normalVect[3];

    for(int i=0;i<3;++i)e1[i] = v1[i] - v0[i];
    for(int i=0;i<3;++i)e2[i] = v2[i] - v0[i];

/** Vector3D out; out.x=a[1]*b[2]-a[2]*b[1]; out.y=a[2]*b[0]-a[0]*b[2]; out.z=a[0]*b[1]-a[1]*b[0]; return out; }` **/
    normalVect[0] = (e1[1] * e2[2]) - (e1[2] * e2[1]);
    normalVect[1] = (e1[2] * e2[0]) - (e1[0] * e2[2]);
    normalVect[2] = (e1[0] * e2[1]) - (e1[1] * e2[0]);

//Scale 0 - 1
    /** `float length = std::sqrt( vector.x*vector.x + vector.y*vector.y + vector.z*vector.z );` **/
    double length = 0;
    length = sqrt((normalVect[0] * normalVect[0]) + (normalVect[1] * normalVect[1]) + (normalVect[2] * normalVect[2]));
    /** Scale each vector **/
    for(int i=0;i<3;++i) normalVect[i] = normalVect[i] * (1 / length);
    //return  normalVect;
}
