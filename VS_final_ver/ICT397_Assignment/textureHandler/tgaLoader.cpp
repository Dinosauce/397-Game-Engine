#include "tgaLoader.h"
#include <memory.h>
#include <iostream>
using namespace std;
#include "../stb_image.h"

tgaLoader::tgaLoader()
{ 
 imageData=NULL;
}

tgaLoader::~tgaLoader()
{ 

}

bool tgaLoader::load(char *filename)
{
	imageData = stbi_load(filename, &width, &height, &BPP, 3);
 return true;
}

int tgaLoader::getHeight()
{
	return height;
}

int tgaLoader::getWidth()
{
	return width;
}

int tgaLoader::getBPP()
{
	return BPP;
}

RGB<unsigned char> tgaLoader::getColor(int x,int y)
{
	RGB<unsigned char> color={0,0,0};

		if( ( x<getWidth() ) && ( y<getHeight() ) )
		{
			color.r  = imageData[( ( y*height )+x )*BPP];
			color.g= imageData[( ( y*height )+x )*BPP+1];
			color.b = imageData[( ( y*height )+x )*BPP+2];
		}
 return color;
}