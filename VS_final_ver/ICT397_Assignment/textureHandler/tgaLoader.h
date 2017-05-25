#ifndef __TGALOADER_H
#define __TGALOADER_H

#include "image.h"


class tgaLoader:public image
{
 private:
    unsigned char* imageData;
    int width;
    int height;
	int BPP;
         

public:
	tgaLoader();
	~tgaLoader();
	bool load(char *filename);
	unsigned char* getData(){return imageData;}
	int getWidth();
	int getHeight();
	void unload(){}
	int getBPP();
	RGB<unsigned char> getColor(int x,int y);
};

#endif