#ifndef __BMPLOADER_H
#define __BMPLOADER_H

#include "image.h"

class bmpLoader:public image
{
private:
   unsigned char* imageData;
   int width;
   int height;
   int BPP;

public:
bmpLoader();
~bmpLoader();
bool load(char *filename);
//unsigned char* getData(){return TextureImage->data;}
unsigned char* getData(){return imageData;}
void unload(){}
//int getWidth(){return TextureImage->sizeX;}
int getWidth(){return width;}
//int getHeight(){return TextureImage->sizeY;}
int getHeight(){return height;}
int getBPP();
RGB<unsigned char> getColor(int x,int y){RGB<unsigned char> ret={0,0,0};return ret;}
};

#endif