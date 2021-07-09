

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
        verts = new double [vertcnt * 3];
        normals = new double [facecnt * 3];
        faces = new unsigned int [facecnt * 3];
    }
};

/** Put the normalsCalc function into a class so we can safely create more than one to support multi-threaded processing. **/
class C_nCalc{
public:
        /** Calculate Normals. **/
    void normalsCalc(C_3DObj O_objIn, int threadNum){
        unsigned int faceIndex = 0;
        unsigned int vertIndex = 0;
        double workingVert[3][3];

        for(int f=0;f<O_objIn.numOfFaces;++f){
            for(int i=0;i<3;++i){
                vertIndex = O_objIn.faces[(faceIndex * 3) + i];
                for(int n=0;n<3;++n){
                    workingVert[n][i] = O_objIn.verts[(vertIndex * 3) + n];
                }
            }
            /** e1 = v1 - v0 and e2 = v2 - v0 **/
            double e1[3];
            double e2[3];

            for(int i=0;i<3;++i)e1[i] = workingVert[i][1] - workingVert[i][0];
            for(int i=0;i<3;++i)e2[i] = workingVert[i][2] - workingVert[i][0];

            /** Vector3D out; out.x=a[1]*b[2]-a[2]*b[1]; out.y=a[2]*b[0]-a[0]*b[2]; out.z=a[0]*b[1]-a[1]*b[0]; return out; }` **/
            O_objIn.normals[(f*3)+0] = (e1[1] * e2[2]) - (e1[2] * e2[1]);
            O_objIn.normals[(f*3)+1] = (e1[2] * e2[0]) - (e1[0] * e2[2]);
            O_objIn.normals[(f*3)+2] = (e1[0] * e2[1]) - (e1[1] * e2[0]);

            //Scale 0 - 1
            /** `float length = std::sqrt( vector.x*vector.x + vector.y*vector.y + vector.z*vector.z );` **/
            double length = 0;
            length = sqrt((O_objIn.normals[(f*3)+0] * O_objIn.normals[(f*3)+0]) + (O_objIn.normals[(f*3)+1] * O_objIn.normals[(f*3)+1]) + (O_objIn.normals[(f*3)+2] * O_objIn.normals[(f*3)+2]));
            /** Scale each vector **/
            for(int i=0;i<3;++i) O_objIn.normals[(f*3)+i] = O_objIn.normals[(f*3)+i] * (1 / length);
        }
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
