

#ifndef renderer
#define renderer

unsigned int sceneInit(int, int);
void getNormalOfPlane(float*, float*, float*);
extern float normalCalc[3];
/* Example to draw a single triangle in 3D space */
/* The actual data will omit the v's and f's numbers as they aren't needed. We can just index what we have. */
/* "v1" x2550 y620 z78 "v2" x220 y43 z12 "v3" x510 y13 z28 "f1" v1 v2 v3 */
/* The raw data will look like this... */
/* 'v' 2550 620 78 'v' 220 43 12 'v' 510 13 28 'f' 1 2 3*/
extern unsigned int * sceneHeap;
/*************************************/
/* Camera viewpoint stuff. */
extern float cameraXpos;
extern float cameraYpos;
extern float cameraZpos;
extern float cameraFocalLength;
extern float cameraXYangle;
extern float cameraYZangle;
/*************************************/

#endif // ggah
