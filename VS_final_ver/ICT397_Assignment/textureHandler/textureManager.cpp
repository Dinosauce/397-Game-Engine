#include "textureManager.h"
#include "imageFactory.h"
#define GL_CLAMP_TO_EDGE 0x812F
#include <time.h>
#include <sstream>

textureManager::textureManager()
{
}

textureManager::~textureManager()
{
	releaseAllTextures();
}

bool textureManager::setActiveTexture(unsigned int texID)
{
 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D,texID);
 return true;
}



image* textureManager::loadTextureRaw(std::string filename)
{
 imageFactory imageLoader;
 image* texture=imageLoader.create(filename.c_str());
     if(!texture)
	 {
		 cout<<"texture load error"<<endl;
		 return NULL;
	 }
	 if(!texture->load((char*)filename.c_str()))
     {
	   cout<<"error in tm loadtmmc"<<endl;
	   return NULL;
     }
 return texture;
}

int textureManager::loadTexture(std::string filename)
{
 image* texture=loadTextureRaw(filename);
 unsigned int texID=-1;

        if(!texture)
		  return -1;

	  //unsigned int texID;
	  	glEnable(GL_TEXTURE_2D);
   // glGenTextures(1, &texID);
		 glGenTextures(1, &texID);
   if(texID<0)
   {
	   return texID;
   }

glBindTexture(GL_TEXTURE_2D, texID); 
 addTextureToMap(filename,texID);  
 numTextures++;
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->getWidth(),texture->getHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,texture->getData());
	glBindTexture(GL_TEXTURE_2D, texID); 
	delete texture;
	texture=NULL;
	return texID;
}

void textureManager::addTextureToMap(std::string filename, int texID)
{
	if (!textures[filename])
    {
     textures[filename] = texID;
    }
}


int textureManager::createNewTexture(unsigned char* tex,int width,int height)
{
	 unsigned int texID=-1;
	  	glEnable(GL_TEXTURE_2D);
   // glGenTextures(1, &texID);
		 glGenTextures(1, &texID);
   if(texID<0)
   {
	   return texID;
   }

glBindTexture(GL_TEXTURE_2D, texID); 
 srand(time(NULL));
 std::stringstream out;
out << (rand()*1000);
addTextureToMap(out.str(),texID);  
 numTextures++;



 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

 glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );		
 glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
//   int iType=texture.GetBPP();
  //				if( iType==24 )
int					iType= GL_RGB;
	//			else
//	int				iType= GL_RGBA;
			//create a mipmapped texture
	
			//gluBuild2DMipmaps( GL_TEXTURE_2D, iType, texture.GetWidth(), texture.GetHeight(), iType, GL_UNSIGNED_BYTE, texture.GetData() );
				gluBuild2DMipmaps( GL_TEXTURE_2D, iType, width, height, iType, GL_UNSIGNED_BYTE, tex );
			//textureSet=true;
glBindTexture( GL_TEXTURE_2D, texID);

	return texID;
}


int textureManager::loadTextureMipmapClamp(std::string filename)
{

 image* texture=loadTextureRaw(filename);
 unsigned int texID=-1;

        if(!texture)
		  return -1;

	  //unsigned int texID;
	  	glEnable(GL_TEXTURE_2D);
   // glGenTextures(1, &texID);
		 glGenTextures(1, &texID);
   if(texID<0)
   {
	   return texID;
   }

glBindTexture(GL_TEXTURE_2D, texID); 
 addTextureToMap(filename,texID);   
 

numTextures++;




 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

 glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );		
 glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
//   int iType=texture.GetBPP();
  //				if( iType==24 )
int					iType= GL_RGB;
	//			else
//	int				iType= GL_RGBA;
			//create a mipmapped texture
	
			//gluBuild2DMipmaps( GL_TEXTURE_2D, iType, texture.GetWidth(), texture.GetHeight(), iType, GL_UNSIGNED_BYTE, texture.GetData() );
				gluBuild2DMipmaps( GL_TEXTURE_2D, iType, texture->getWidth(), texture->getHeight(), iType, GL_UNSIGNED_BYTE, texture->getData() );
			//textureSet=true;
glBindTexture( GL_TEXTURE_2D, texID);
    delete texture;
	return texID;
}

void textureManager::releaseAllTextures(void)
{
  std::map<std::string, unsigned int>::iterator it = textures.begin();
  while(it != textures.end())
  {
	  cout<<"unloading Texture: "<< (*it).first<<", ID: "<<(*it).second;
    glDeleteTextures(1, &(*it).second);
	cout<<" ... done"<<endl;
    ++it;
  }
  textures.clear();
  }