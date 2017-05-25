#include "bmpLoader.h"
#include <fstream>
using namespace std;
#include "../stb_image.h"

bmpLoader::bmpLoader()
{
 imageData=NULL;
}

//checks if file exists.
bool validFile(char *filename)
{

 fstream testExists(filename);
   if(testExists.is_open())
   {
	   testExists.close();
	   return true;
   }
	return false;
}

bmpLoader::~bmpLoader()
{
 delete[] imageData;
}

bool bmpLoader::load(char *filename) 
{
	
	imageData = stbi_load(filename, &width, &height, &BPP, 3);
  return true;
}

int bmpLoader::getBPP()
{
  return 24;
}

