#include <cstdio>
#include <stdlib.h>
#include "pcx.h"
#include <math.h>
#include <iostream>
#include <algorithm>  
using namespace std;


pcx::pcx()
{
	imageData=NULL;
}

pcx::~pcx()
{
	delete[] imageData;
}


bool pcx::TexMapScalePow2()
{
   GLint glMaxTexDim ;
   double xPow2, yPow2;
   int ixPow2, iyPow2;
   int xSize2, ySize2;
//   bool pow2=true;


   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);
   glMaxTexDim = min(128, glMaxTexDim);

   if (width <= glMaxTexDim)
      xPow2 = log((double)width) / log(2.0);
   else
      xPow2 = log((double)glMaxTexDim) / log(2.0);

   if (height <= glMaxTexDim)
      yPow2 = log((double)height) / log(2.0);
   else
      yPow2 = log((double)glMaxTexDim) / log(2.0);

   ixPow2 = (int)xPow2;
   iyPow2 = (int)yPow2;

   if (xPow2 != (double)ixPow2)
      ixPow2++;
    if (yPow2 != (double)iyPow2)
   	  iyPow2++;
 
   
    xSize2 =1 << ixPow2;
    ySize2 = 1 << iyPow2;
    GLubyte *pData = (GLubyte*)malloc(xSize2 * ySize2 * 3 * sizeof(GLubyte));
      if (!pData) return false;
 
	gluScaleImage(GL_RGB, width, height,GL_UNSIGNED_BYTE, imageData,xSize2, ySize2, GL_UNSIGNED_BYTE,pData);

   free(imageData);
   imageData = (GLubyte*)pData; 
   width = xSize2 ;
   height = ySize2 ;

   return true ;
}


bool pcx::load(char *filename) 
{ 
  FILE *hTexFile = fopen( filename, "rb" ); 
  /* check the file open command */ 
  if( hTexFile != NULL ) 
  { 
    int imgWidth, imgHeight, texFileLen, imgBufferPtr, i; 
    pcxHeader *pcxPtr; 
    unsigned char *imgBuffer, *texBuffer, *pcxBufferPtr, *paletteBuffer; 

    /* find length of file */ 
    fseek( hTexFile, 0, SEEK_END ); 
    texFileLen = ftell( hTexFile ); 
    fseek( hTexFile, 0, SEEK_SET ); 

    /* read in file */ 
    texBuffer = (unsigned char *)malloc( texFileLen+1 ); 
    fread( texBuffer, sizeof( char ), texFileLen, hTexFile ); 

    /* get the image dimensions */ 
    pcxPtr = (pcxHeader *)texBuffer; 
    imgWidth = pcxPtr->size[0] - pcxPtr->offset[0] + 1; 
    imgHeight = pcxPtr->size[1] - pcxPtr->offset[1] + 1; 
   /* image starts at 128 from the beginning of the buffer */ 
    imgBuffer = (unsigned char *)malloc( imgWidth * imgHeight ); 
    imgBufferPtr = 0; 
    pcxBufferPtr = &texBuffer[128]; 

    /* decode the pcx image */ 
    while( imgBufferPtr < (imgWidth * imgHeight) ) 
    { 
      if( *pcxBufferPtr > 0xbf ) 
      { 
        int repeat = *pcxBufferPtr++ & 0x3f; 
        for( i=0; i<repeat; i++ ) 
        { 
          imgBuffer[imgBufferPtr++] = *pcxBufferPtr; 
        } 
      } else { 
        imgBuffer[imgBufferPtr++] = *pcxBufferPtr; 
      } 
      pcxBufferPtr++; 
    } 

    /* read in the image palette */ 
    paletteBuffer = (unsigned char *)malloc( 768 ); 
    for( i=0; i<768; i++ ) 
      paletteBuffer[i] = texBuffer[ texFileLen-768+i ]; 

    width=imgWidth; 
    height=imgHeight; 

    /* now create the OpenGL texture */ 
    { 
      int i, j; 
      imageData = (unsigned char *)malloc( width * height * 3 ); 
      for (j = 0; j < imgHeight; j++) 
      { 
        for (i = 0; i < imgWidth; i++) 
        { 
          imageData[3*(j * width + i)+0] 
            = paletteBuffer[ 3*imgBuffer[j*imgWidth+i]+0 ]; 
          imageData[3*(j * width + i)+1] 
            = paletteBuffer[ 3*imgBuffer[j*imgWidth+i]+1 ]; 
          imageData[3*(j * width + i)+2] 
            = paletteBuffer[ 3*imgBuffer[j*imgWidth+i]+2 ]; 
        } 
      } 
    } 
    /* cleanup */ if(!TexMapScalePow2())
	  cout<<"load error - mam"<<endl;
    free( paletteBuffer ); 
    free( imgBuffer ); 
	bpp=24; 
    
  } else { 
    /* skip the texture setup functions */ 
    return false;
  } 
  
  return true; 
} 

void pcx::unload()
{
  delete[] imageData;
  imageData=NULL;
}

