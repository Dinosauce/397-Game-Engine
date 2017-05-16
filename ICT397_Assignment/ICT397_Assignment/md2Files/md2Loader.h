/******************************************************************************
* fileName: md2Loader.h
* Author  : David Bennett
* Legal   : use it, dont, whatever. Just dont bitch at me.
* Date    : 17/03/2005
* Purpose : class for reading in a quake md2 model
*         : contains opengl code. Replace with functions from your own graphics
*           engine.
******************************************************************************/
#ifndef __md2Loader_H
#define __md2Loader_H

#if _MCS_VER >= 1020
  #pragma once
#endif

#include <iostream>
#include <fstream>
using namespace std;
#include "md2Header.h"
#include "timer.h"
#include <GL/glu.h>
#include "vector/vector.h"
//a single vertex
struct vertex
{
 float x,y,z;
 unsigned char normIndex;  //unused
};

// single MD2 triangle
struct triangle
{
	unsigned short vertIndices[3];
	unsigned short texIndices[3];
};


// Texture coord information for the MD2
struct texCoord
{
	float tex[2];
};

//Name of a single skin in the md2 file
struct skin
{
	char filename[64];	//filename
	GLuint texID;		//Image file ready for texturing
};

struct frame
{
	//header
    float scale[3];    //x,y,z scaling factors for the frame vertices
	float trans[3];    //x,y,z translation factors for the frame vertices
	char name[16];     //ASCI filename for the model
    vertex* vertices;
    
	frame(){vertices=0;}
	~frame()
	{
		if(vertices)
			delete[] vertices;
	}
};

class md2Loader
 {
private:
   md2Header header;
   frame* frames;
   triangle* triangles;
   skin* skins;
   texCoord* texCoords;
   unsigned int lastStart;
   unsigned int	lastEnd;	//last start/end params passed to the function
   unsigned int lastFrame;	//lastframe rendered
   float lastInterpol;		//Last interpolation value
   bool validFile();
   bool readTriangles(char*);
   bool readSkins(char*);
   bool readTextures(char* buf);
   bool readFrames(char*);
   void renderAnimFrame();
   int timesAnimated;
   unsigned short animationSpeed;
   
   unsigned short skinNumber;   //current skin number
   //Interpolated vertices
	vertex* vertices;
	CTimer timer;
	vector3D calculateTriangleNormal(const vector3D v1, const vector3D v2, const vector3D v3);
public:
   /*****************************************************************************
   *Purpose: default constructor
   *****************************************************************************/
   md2Loader();
   int setTex(char* filename);
   /*****************************************************************************
   *Purpose: destructor
   *****************************************************************************/
   ~md2Loader();
   /*****************************************************************************
   *Purpose: Prints out the header values
   *Pre : none
   *Post: header values displayed
   *****************************************************************************/
   void printHeader();
   /*****************************************************************************
   *Purpose: Loads an MD2 model from file
   *Pre : filename is an assigned value
   *Post: model is loaded
   *returns: true if model loaded, otherwise false
   *Vars: filename - the filename containing the MD2 model
   *****************************************************************************/  
   bool loadModel(char* filename,char* skinName);
   void printModelInfo();
   bool addCustomSkin(char* filename);
   void setSkin(unsigned short num);
   void render(unsigned int frameNum);
   void render();
   int animate(unsigned short startFrame, unsigned short endFrame);
   /*****************************************************************************
   *Purpose: cycles through a single animation sequence between startFrame and  *
   *         endFrame.
   *Pre : all vars are assigned values >= 0
   *Post: animates a single cycle.
   *returns: true if animation cycle complete, otherwise false
   *Vars: fps - frames per second
   *      startFrame - starting frame of the animation
   *      endFrame - ending frame of the animation
   *      curFrame - the current frame to be rendered. The function updates its 
   *                 value. Should be set to the same value as startFrame on first
   *                 call to the function.
   *****************************************************************************/ 
   bool animateOnce(unsigned short startFrame, unsigned short endFrame, unsigned short &curFrame);
   unsigned short getSkinNumber(){return skins[0].texID;}
   void setAnimationSpeed(unsigned short speed);
  };

#endif