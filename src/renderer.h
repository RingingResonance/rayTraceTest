

#ifndef renderer
#define renderer

void getNormalOfPlane(double*, double*, double*);

/** This class is for the map's static faces. **/
class C_mapObjStatic{
public:
    double* verts;             /** groups of three, 'xyzxyzxyzxyzxyz... etc.' **/
    double* normals;           /** each face has a precomputed normal, 'xyzxyzxyzxyzxyz... etc.' **/
    unsigned int* faces;       /** each face has three verts, '1 2 3 1 4 2 5 2 1... etc' **/
    unsigned int numOfFaces;   /** Total number of faces. **/
    /** Memory constructor **/
    C_mapObjStatic(int vertcnt, int facecnt){
        verts = new double [vertcnt];
        normals = new double [facecnt * 3];
        faces = new unsigned int [facecnt * 3];
    }
};

/** Class for the camera viewport **/
class C_camera{
public:
    double cameraPos[3];        /** xyz **/
    double cameraFocalLength;
    double cameraAngle[2];      /** xy and yz **/
};

#endif // ggah
