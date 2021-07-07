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
/* Example to draw a single triangle in 3D space */
/* The actual data will omit the v's and f's numbers as they aren't needed. We can just index what we have. */
/* "v1" x2550 y620 z78 "v2" x220 y43 z12 "v3" x510 y13 z28 "f1" v1 v2 v3 */
/* The raw data will look like this... */
/* 'v' 2550 620 78 'v' 220 43 12 'v' 510 13 28 'f' 1 2 3 'E' 'O' 'F' */
/* EOF is for End Of Face */
unsigned int * sceneHeap;
/*************************************/
/* All positions will be int and all angles will be float */
/* Camera viewpoint stuff. */
float cameraXpos;
float cameraYpos;
float cameraZpos;
float normalCalc[3];
float cameraFocalLength;
float cameraXYangle;
float cameraYZangle;
/*************************************/

int xPos = 0;
int yPos = 0;

int main()
{
    //initialize
    int totalPixs = rgbChannelInit (width,height);
    int initPix = 0;
    int sceneHeapSize = 0;
    //draw a solid background color.
    while (initPix < totalPixs){
        imagered[initPix] = 123;
        imagegreen[initPix] = 101;
        imageblue[initPix] = 235;
        initPix++;
    }
    //test scene.
    sceneHeapSize = sceneInit(3, 1);
    sceneHeap[0] = 'v';
    sceneHeap[1] = 2550;
    sceneHeap[2] = 620;
    sceneHeap[3] = 78;
    sceneHeap[4] = 'v';
    sceneHeap[5] = 220;
    sceneHeap[6] = 43;
    sceneHeap[7] = 12;
    sceneHeap[8] = 'v';
    sceneHeap[9] = 510;
    sceneHeap[10] = 13;
    sceneHeap[11] = 28;
    sceneHeap[12] = 'f';
    sceneHeap[13] = 1;
    sceneHeap[14] = 2;
    sceneHeap[15] = 3;

    //setup the camera
    cameraXpos = 0;
    cameraYpos = 0;
    cameraZpos = 0;
    cameraFocalLength = width * 100; //make it square.
    cameraXYangle = 0; //angles in degrees.
    cameraYZangle = 0; //0,0 makes it face forward along the y axis.

    /******* Test ********/
    /*float vt0[] = {0.5,0.2,0.8};
    float vt1[] = {0.1,0.1,0.3};
    float vt2[] = {0.7,0.6,0.5};*/
    float vt0[] = {5,2,8};
    float vt1[] = {1,1,3};
    float vt2[] = {7,6,5};
    /**With this test, The Normal Should Equal X0.66148, Y-0.63272, Z-0.40264 Using someone else's normal web based calc.**/
    getNormalOfPlane(vt0, vt1, vt2);
    cout << "Test Normal. \n";
    cout << "X " << normalCalc[0] << "\n";
    cout << "Y " << normalCalc[1] << "\n";
    cout << "Z " << normalCalc[2] << "\n";
    /******* End Test ********/


    //Done rendering, now write it to a file.
    pngmake(1, width, height);
    rgbChannelCleanup();
    return 0;
}

void getNormalOfPlane(float v0[3], float v1[3], float v2[3]){
    /** e1 = v1 - v0 and e2 = v2 - v0 **/
    float e1[3];
    float e2[3];
    int i = 0;
    while(i<2){
        e1[i] = v1[i] - v0[i];
        i++;
    }
    i = 0;
    while(i<2){
        e2[i] = v2[i] - v0[i];
        i++;
    }
/** Vector3D out; out.x=a[1]*b[2]-a[2]*b[1]; out.y=a[2]*b[0]-a[0]*b[2]; out.z=a[0]*b[1]-a[1]*b[0]; return out; }` **/
    normalCalc[0] = (e1[1] * e2[2]) - (e1[2] * e2[1]);
    normalCalc[1] = (e1[2] * e2[0]) - (e1[0] * e2[2]);
    normalCalc[2] = (e1[0] * e2[1]) - (e1[1] * e2[0]);
}

//This initializer only accepts triangular faces.
unsigned int sceneInit(int totalVerts, int totalFaces){
    unsigned int ramEater = ((totalVerts * 4) + (totalFaces * 4));
    sceneHeap = new unsigned int [ramEater]; //chomp
    return ramEater;
}

