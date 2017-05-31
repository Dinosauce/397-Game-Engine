/******************************************************************************
* fileName: md2Loder.h
* Author  : David Bennett
* Legal   : use it, dont, whatever. Just dont bitch at me.
* Date    : 17/03/2005
* Purpose : class for reading in a quake md2 model
******************************************************************************/
#ifndef __md2Header_H
#define __md2Header_H
#if _MCS_VER >= 1020
  #pragma once
#endif
#include <iostream>
using namespace std;


class md2Header
 {
private:
   int ident;				//indentifies as MD2 file- always "IDP2"
   int version;				//should be equal to 8
   int skinWidth;			//width of skin texture
   int skinHeight;			//width of skin height
   int frameSize;			//number of bytes per frame
   int numSkins;			//number of textures
   int numVertices;			//number of vertices
   int numTexCoords;		//number of texture coords
   int numTriangles;		//number of triangles
   int numGLCommands;		//number of OpenlGL command types
   int numFrames;			//offset of frame data
   int offsetSkins;			//offset (location) of skin names (64 bytes each)
   int offsetTexCoords;		//offset (location) of texture values
   int offsetTriangles;		//offset (location) of triangle mesh
   int offsetFrames;		//offset (location) of frame data
   int offsetGLCommands;	//type of opengl commands to use
   int fileSize;            //size of file
public:
   md2Header();
   bool setHeader(const md2Header&);
   void printHeader();
   bool readHeader(char* buf);
   friend ostream& operator<<(ostream&, const md2Header&);
   bool operator=(const md2Header&); 
   friend class md2Loader;
};

#endif