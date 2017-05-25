#ifndef __TEXTUREMANAGER_H
#define __TEXTUREMANAGER_H

#if _MCS_VER >= 1020
  #pragma once
#endif


#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;
#include <gl\glut.h>
#include "image.h"
#include "bmpLoader.h"
#include "tgaLoader.h"


class textureManager
{
private:
	map<std::string, unsigned int> textures;
	int numTextures;
public:
	textureManager();
	~textureManager();
	bool setActiveTexture(unsigned int texID);
	 int loadTexture(std::string filename);
	image* loadTextureRaw(std::string filename);
	 int loadTextureMipmapClamp(std::string filename);
	 int getBPP();
	 void releaseAllTextures(void);
	 void addTextureToMap(std::string filename, int texID);

	int createNewTexture(unsigned char* tex,int width,int height);
};

#endif