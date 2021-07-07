

#ifndef rgeth
#define rgeth

void tgamake(int, int xRes, int yRes);
void pngmake(int, int xRes, int yRes);
int rgbChannelInit (int, int);
void rgbChannelCleanup(void);
int rfileget(void);

extern unsigned int * randombox; //box of random numbers to use for mix
extern unsigned int rbox;
extern unsigned char * imagered;
extern unsigned char * imagegreen;
extern unsigned char * imageblue;
//extern int image[65025];

#endif
