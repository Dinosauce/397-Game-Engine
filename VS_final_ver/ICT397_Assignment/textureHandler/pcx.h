#ifndef __PCX_H 
#define __PCX_H 
#if _MCS_VER >= 1020
  #pragma once
#endif
#include <GL/glut.h>
#include "image.h"

typedef struct _pcxHeader 
{ 
  short id[2]; 
  short offset[2]; 
  short size[2]; 
} pcxHeader; 




class pcx:public image 
{ 
public: 
  pcx(); 
  ~pcx(); 
  bool load(char *filename);    // PCX loader 
  bool TexMapScalePow2();
  unsigned int texID; 
  void unload();
  unsigned char* getData(){return imageData;}
  int getWidth(){return width;}
  int getHeight(){return height;}
  int getBPP(){return bpp;}
  RGB<unsigned char> getColor(int x,int y){RGB<unsigned char> ret={0,0,0};return ret;}
private:
  unsigned int bpp; 
  int width; 
  int height;
  unsigned char *imageData; 
}; 

#endif 
