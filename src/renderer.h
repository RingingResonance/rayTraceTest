

#ifndef renderer
#define renderer

void getNormalOfPlane(double**);

/** This class is for the map's static faces. **/
class C_3DObj{
public:
    double* verts;             /** groups of three, 'xyzxyzxyzxyzxyz... etc.' **/
    double* normals;           /** each face has a precomputed normal, 'xyzxyzxyzxyzxyz... etc.' **/
    unsigned int* faces;       /** each face has three verts, '1 2 3 1 4 2 5 2 1... etc' **/
    unsigned int numOfFaces;   /** Total number of faces. **/
    /** Memory constructor **/
    C_3DObj(int vertcnt, int facecnt){
        this -> verts = new double [vertcnt * 3];
        this -> normals = new double [facecnt * 3];
        this -> faces = new unsigned int [facecnt * 3];
    }
};

/** Put the normalsCalc function into a class so we can safely create more than one to support multi-threaded processing. **/
class C_nCalc{
public:
    void normalsCalc(C_3DObj*, int, int);
};

/** Class for the camera viewport **/
class C_camera{
public:
    double cameraPos[3];        /** xyz **/
    double cameraFocalLength;
    double cameraAngle[2];      /** xy and yz **/
};

#endif // ggah
