/* Random Number Get from File */

#include <iostream>
#include <fstream>
#include <string>
#include "fgetter.h"
#include "./lodepng/lodepng.h"

using namespace std;

ifstream randofile;		//global file I/O stuff.
ofstream resultf;

#define infile "randomnums.txt"
char * inputblock;
unsigned char * rgbimage;
int imindex;

unsigned int * randombox; //box of random numbers to use for mix
unsigned int rbox;
unsigned char * imagered;
unsigned char * imagegreen;
unsigned char * imageblue;

int rgbChannelInit (int xRes, int yRes){
    int res = xRes * yRes;
    imagered = new unsigned char [res];
    imagegreen = new unsigned char [res];
    imageblue = new unsigned char [res];
    return res;
}

void rgbChannelCleanup(){
    delete imagered;
    delete imagegreen;
    delete imageblue;
}


/****************************/
/* png image make */
/* Converts the three individual RGB channels into and RGB array for the lodepng library*/
void pngmake(int frameNum, int xRes, int yRes){
    int res = xRes * yRes * 3;
    int i = 0;
    int d = 0;
    //create a new array that's the appropriate size for our resolution. No alpha channel.
    rgbimage = new unsigned char [res];
    //Coppy the RGB data over to an array suitable for the PNG conversion library.
    while (i <= res){
        rgbimage[i] = imagered[d];
        i++;
        rgbimage[i] = imagegreen[d];
        i++;
        rgbimage[i] = imageblue[d];
        i++;
        d++;
    }
    //TODO: number the frame names.
    //lodepng_encode24_file(("./output/frame" + std::to_string(frameNum) + ".png"), rgbimage, xRes, yRes);
    lodepng_encode24_file("./output/frame.png", rgbimage, xRes, yRes);
    //cleanup
    delete rgbimage;
}
/****************************/

/****************************/
/* TGA image format maker. */
unsigned char tgaheader[] = {
00,00,0x2,00,00,00,00,00,00,00,
0xFF,00,0xFF,00,0xFF,00,0x18,0x20
};

unsigned char tgatail[] = {
00,00,00,00,00,00,00,00,0x54,0x52,0x55,
0x45,0x56,0x49,0x53,0x49,0x4F,0x4E,0x2D,
0x58,0x46,0x49,0x4C,0x5,0x2E,00
};

//Write a .tga image to file.
void tgamake(int frameNum, int xRes, int yRes)
{
  int i = 0;
//Open the file.
  //resultf.open (("./output/Generation_" + std::to_string(geno) + "_Board_" + std::to_string(brdnum) + ".tga"), ios::out | ios::binary);
  resultf.open (("./output/frame" + std::to_string(frameNum) + ".tga"), ios::out | ios::binary);

//write the header.
  i = 0;
  while (i < 18)
  {
    resultf << tgaheader[i];
    i++;
  }
//write the RGB data.
  i = 0;
  while (i < 65025)
  {
    resultf << imageblue[i];
    resultf << imagegreen[i];
    resultf << imagered[i];
    i++;
  }
//write the tail
  i = 0;
  while (i < 25)
  {
    resultf << tgatail[i];
    i++;
  }
//close the file.
  resultf.close();
}
/****************************/
/****************************/

/****************************/
/* Random number stuff. */
/* Random numbers from a file. Not so random actually, this is just for ease of testing. */
int rfileget(void)
{
    streampos size;
    //Random number get.
    cout << "Attempting to open file '" << infile << "' \n";

    randofile.open (infile, ios::in | ios::ate);			//open file and position the pointer to end of file so we can get the size.
    if (!randofile.is_open())
    {
        cout << "FAILED TO OPEN FILE '" << infile << "' \n \n";
        return 1;
    }
    cout << "Success! File '" << infile << "' opened. \n";

    size = randofile.tellg();			//get the file size
    inputblock = new char [size];
    randofile.seekg (0, ios::beg);		//seek to beginning of file.
    randofile.read (inputblock, size);		//copy to memory.


    int i;
    i = 0;
    unsigned int testvar;
    unsigned int addvar[3];
    int varplace;
    int tmpplace;
    unsigned int outvar;
    unsigned int vardiv;
    unsigned int randoaddr;
    randoaddr = 0;
    vardiv = 1;
    varplace = 0;

    while (i < size)
    {
        testvar = inputblock[i];
        if (testvar != 13)
        {
            addvar[varplace] = testvar - 48;
            varplace++;
            vardiv = vardiv * 10;
            i++;
        }
        else
        {
            varplace = varplace - 1;
            tmpplace = varplace;
            while (tmpplace >= 0)
            {
                if (tmpplace == 3)
                {
                    vardiv = vardiv / 10;
                    addvar[3] = addvar[3] * vardiv;
                }
                else if (tmpplace == 2)
                {
                    vardiv = vardiv / 10;
                    addvar[2] = addvar[2] * vardiv;
                }
                else if (tmpplace == 1)
                {
                    vardiv = vardiv / 10;
                    addvar[1] = addvar[1] * vardiv;
                }
                else if (tmpplace == 0)
                {
                    vardiv = vardiv / 10;
                    addvar[0] = addvar[0] * vardiv;
                }
                tmpplace--;
            }
            tmpplace = varplace;
            outvar = 0;
            while (tmpplace >= 0)
            {
                outvar = outvar + addvar[tmpplace];
                tmpplace--;
            }
            //cout << outvar << "\n";
            i++;
            varplace = 0;
            tmpplace = 0;
            vardiv = 1;
            if (randoaddr >= rbox)
            {
                cout << "Error! random file has more numbers than what the program has been set to handle. \n";
                return 1;
            }
            else
            {
                randombox[randoaddr] = outvar;
                randoaddr++;
            }
        i++;
        }
    }
    return 0;
}
//End of random number get.
