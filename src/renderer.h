

#ifndef renderer
#define renderer

double* getNormalOfPlane(double*, double*, double*);

/** This class is for the map's static faces. **/
class C_mapStatic{
public:
    double * verts;             /** groups of three, 'xyzxyzxyzxyzxyz... etc.' **/
    double * normals;           /** each face has a precomputed normal, 'xyzxyzxyzxyzxyz... etc.' **/
    int * faces;                /** each face has three verts, '1 2 3 1 4 2 5 2 1... etc' **/
    unsigned int numOfFaces;    /** Total number of faces. **/
    C_mapStatic(int, int);           /** Constructor **/
};

/** Class for the camera viewport **/
class C_camera{
public:
    double cameraPos[3];        /** xyz **/
    double cameraFocalLength;
    double cameraAngle[2];      /** xy and yz **/
};

#endif // ggah
