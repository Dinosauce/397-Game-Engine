#include "md2Loader.h"
#include <cstdio>
//#include "imageLoader/imageFactory.h"
#include "../textureHandler/imageFactory.h"
#include <gl\glut.h>
//#include <GL/glfw.h>



md2Loader::md2Loader()
{   //set all variables to zero
	frames=0;
	triangles=0;
	skins=0;
	texCoords=0;
	skinNumber=0;
	lastStart=0, 
    lastEnd=0;	//last start/end parems passed to the function
    lastFrame=0;	//lastframe rendered
    lastInterpol=0;		//Last interpolation value
	vertices=NULL;
	timesAnimated=0;
	animationSpeed=24;
	timer.Init();
}

md2Loader::~md2Loader()
{   
	  if(frames)
		  delete[] frames;
	  if(triangles)
		  delete[] triangles;
	  if(skins)
		  delete[] skins;
	  if(texCoords)
		  delete[] texCoords;
	  if(vertices)
		  delete[] vertices;
}


bool md2Loader::readTriangles(char* buf)
{
  unsigned char *ptr=(unsigned char *)buf+header.offsetTriangles;
	  //read in triangles
	  triangles=new triangle[header.numTriangles];
	  memcpy(triangles,ptr,12*header.numTriangles);
 return true;
}

bool md2Loader::readSkins(char* buf)
{	  
/* unsigned char *ptr=(unsigned char *)buf+header.offsetSkins;
 char *end=0;
	  //read in skin filenames
	  skins=new skin[header.numSkins];
	  cout<<"Number of skins: "<<header.numSkins<<endl;
	  memcpy(skins,ptr,header.numSkins*sizeof(skin));
	    for(int i=0;i<header.numSkins;i++)
	    {  //filename contains quake specific directories - remove them
			end=strrchr(skins[i].filename,'/');
			  if(!end)
                end=strrchr(skins[i].filename,'\\');

			  if(end)
				  strcpy(skins[i].filename,end+1);
	    }
*/
 return true;
}

bool md2Loader::readTextures(char* buf)
{	  
  //read in uv texture coords- read into array of shorts and convert
  //to floats using skinwidth and skinheight
  unsigned char *ptr=(unsigned char *)buf+header.offsetTexCoords;
      texCoords=new texCoord[header.numTexCoords];
	  short *sTexCoords = new short[header.numTexCoords*2];
	  memcpy(sTexCoords, ptr, 4 * header.numTexCoords);
   	    for(int i = 0; i < header.numTexCoords; i++)
	    {
		 texCoords[i].tex[0] = (float)sTexCoords[2*i] /header.skinWidth;
		 texCoords[i].tex[1] = (float)sTexCoords[2*i+1] /header.skinHeight;
	    }
	 delete [] sTexCoords;
 return true;
}



bool md2Loader::readFrames(char* buf)
{
 unsigned char* ptr=0;
	//allocate memory for frame data
	frames=new frame[header.numFrames];
	  if(!frames)
	  {
		  cerr<<"could not allocate mem for frames"<<endl;
		  return false;
	  }
	//point to the beggining of the frame data
    //need to convert to unsigned as x value is unsigned
	ptr=(unsigned char*)buf+header.offsetFrames;
	  for(int i=0;i<header.numFrames;i++)
	  { //loop through and read in all frames
		//read in frame header
		//read in scale
		memcpy(frames[i].scale,ptr,12);
		//read in trans
		ptr+=12;
		memcpy(frames[i].trans,ptr,12);
		//read in name
		ptr+=12;
		memcpy(frames[i].name,ptr,16);
		ptr+=16;
		//allocate vertice mem
		frames[i].vertices=new vertex[header.numVertices];
		  for(int j = 0; j < header.numVertices; j++)
	      {
	       //swap y and z coords to convert to the proper orientation on screen
	        frames[i].vertices[j].x = ptr[0] * frames[i].scale[0] + frames[i].trans[0];
			frames[i].vertices[j].y = ptr[2] * frames[i].scale[2] + frames[i].trans[2];
			frames[i].vertices[j].z = ptr[1] * frames[i].scale[1] + frames[i].trans[1];
			frames[i].vertices[j].normIndex=ptr[3];  //read normal index
			ptr += 4;  //point to next vertex array index
	      }
	  } //for
 return true;
}

/*****************************************************************************
*Purpose: checks for a valid md2 file
*Pre : header is an assigned value
*Post: returns true if valid, otherwise false
*****************************************************************************/
bool md2Loader::validFile()
{
	if(header.ident!=844121161 || header.version!=8)
	{
		cerr<<"Not a valid MD2 file"<<endl;
		return false;
	}
 return true;
}

void md2Loader::printHeader()
{
 cout<<header;
}

bool md2Loader::loadModel(char* filename, char* skinName)
{
 char * buffer=NULL;

	//open for binary read 
	ifstream infile(filename,ios::binary|ios::in);
	  if(!infile)
	  {
		  cerr<<"Cannot open md2File :"<<filename<<endl;





		  return false;
	  }
	  else
	  {
       // get length of file
       infile.seekg (0, ios::end);
       //determine length of file
	   header.fileSize = infile.tellg();
       infile.seekg (0, ios::beg);
       // allocate memory:
       buffer = new  char [header.fileSize];
	       if(!buffer)
		      return false;
       // read data as a block:
	   infile.read(buffer,header.fileSize);
       infile.close();
	  } //if
	//read in header
	header.readHeader(buffer);
    //read in frames
    readFrames(buffer);
    //read in triangles
	readTriangles(buffer);
	//read in skin filenames
	//readSkins(buffer);
	addCustomSkin(skinName);
	//read in textures
	readTextures(buffer);    
	  if(buffer)
        delete[] buffer;
 return true;
}

void md2Loader::printModelInfo()
{
	if(!frames && !triangles && !skins && !texCoords)
	{
	 cout<<"no model loaded"<<endl;
	}
	else
	{
	 cout<<header;
		for(int i=0;i<header.numFrames;i++)
		{
		 cout<<"frame #: "<<i<<endl;
		 printf("scale x y z:%.2f,%.2f,%.2f\n",frames[i].scale[0],frames[i].scale[1],frames[i].scale[0]); 
		 printf("trans x y z:%.2f,%.2f,%.2f\n",frames[i].trans[0],frames[i].trans[1],frames[i].trans[0]); 
		 cout<< "name: "<<frames[i].name<<endl;
		 for(int j=0;j<header.numVertices;j++)
		 {
			 printf("vertices x y z:%.2f,%.2f,%.2f\n",frames[i].vertices[j].x,frames[i].vertices[j].y,frames[i].vertices[j].z);
		 }
		}
		for(int i=0;i<header.numTriangles;i++)
		{
		 printf("triangle : %d : x y z:%d,%d,%d\n",i,triangles[i].vertIndices[0],triangles[i].vertIndices[1],triangles[i].vertIndices[2]); 
		}
		for(int i=0;i<header.numTexCoords;i++)
		{
		 printf("tex Coords : %d : u v:%.2f,%.2f\n",i,texCoords[i].tex[0],texCoords[i].tex[1]); 
		}
		for(int i=0;i<header.numSkins;i++)
		{
	     printf("filename : %s\n",skins[i].filename); 
		}
	}
}


void md2Loader::render(unsigned int frameNum)
{
	vector3D v1,v2,v3;
	  if(skins)
	  {
	   glEnable(GL_TEXTURE_2D);
	   glBindTexture(GL_TEXTURE_2D,skins[skinNumber].texID);
	  }
	glBegin(GL_TRIANGLES);

	  for(int i = 0; i < header.numTriangles; i++)
	  {
		  v1.set(frames[frameNum].vertices[triangles[i].vertIndices[0]].x,
		        frames[frameNum].vertices[triangles[i].vertIndices[0]].y,
				frames[frameNum].vertices[triangles[i].vertIndices[0]].z);
		  v2.set(frames[frameNum].vertices[triangles[i].vertIndices[1]].x,
		        frames[frameNum].vertices[triangles[i].vertIndices[1]].y,
				frames[frameNum].vertices[triangles[i].vertIndices[1]].z);
		  v3.set(frames[frameNum].vertices[triangles[i].vertIndices[2]].x,
		        frames[frameNum].vertices[triangles[i].vertIndices[2]].y,
				frames[frameNum].vertices[triangles[i].vertIndices[2]].z);
		  vector3D n1=calculateTriangleNormal(v1,v2,v3);
		glNormal3f(n1.x,n1.y,n1.z);
		   if(skins)
			   glTexCoord2fv(texCoords[triangles[i].texIndices[0]].tex);
		       
	   glVertex3f(v1.x,v1.y,v1.z);
	      if(skins)
			  glTexCoord2fv(texCoords[triangles[i].texIndices[1]].tex);
		  
	   glVertex3f(v2.x,v2.y,v2.z);
	      if(skins)
			  glTexCoord2fv(texCoords[triangles[i].texIndices[2]].tex);
		  
       glVertex3f(v3.x,v3.y,v3.z);
	   
	  }  
	glEnd();	
	glDisable(GL_TEXTURE_2D);
}

//render frame 0
void md2Loader::render()
{
	render(0);
}

void md2Loader::renderAnimFrame()
{
  vector3D v1,v2,v3;

    //Render the new vertices
      if(skins)
	  {
	   glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D,skins[skinNumber].texID);
	  }
	glBegin(GL_TRIANGLES);

	for(int i = 0; i < header.numTriangles; i++)
	{
		v1.set(vertices[triangles[i].vertIndices[0]].x,
				   vertices[triangles[i].vertIndices[0]].y,
				   vertices[triangles[i].vertIndices[0]].z);
		v2.set(vertices[triangles[i].vertIndices[1]].x,
		           vertices[triangles[i].vertIndices[1]].y,
				   vertices[triangles[i].vertIndices[1]].z);
		v3.set(vertices[triangles[i].vertIndices[2]].x,
		           vertices[triangles[i].vertIndices[2]].y,
   			       vertices[triangles[i].vertIndices[2]].z);
        vector3D n1=calculateTriangleNormal(v1,v2,v3);
		glNormal3f(n1.x,n1.y,n1.z);
		  if(skins)
			glTexCoord2fv(texCoords[triangles[i].texIndices[0]].tex);
		glVertex3f(v1.x,v1.y,v1.z);
		  if(skins)
			glTexCoord2fv(texCoords[triangles[i].texIndices[1]].tex);
		glVertex3f(v2.x,v2.y,v2.z);	   
	      if(skins)
			glTexCoord2fv(texCoords[triangles[i].texIndices[2]].tex);
		glVertex3f(v3.x,v3.y,v3.z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

int md2Loader::animate(unsigned short startFrame, unsigned short endFrame)
{	
	unsigned int msPerFrame = 0;			//number of milliseconds per frame
	//alloc a place to put the interpolated vertices
	if(!vertices)
		vertices = new vertex[header.numVertices];

	//Prevent invalid frame counts
	if(endFrame >= (unsigned short)header.numFrames||endFrame<0)
		endFrame = header.numFrames-1;
	if(startFrame > (unsigned short)header.numFrames||startFrame<0)
		startFrame = 0;

	//avoid calculating everything every frame
	if(lastStart != startFrame || lastEnd != endFrame)
	{
		lastStart = startFrame;
		lastEnd = endFrame;
		timesAnimated=0;
	}
		msPerFrame = (unsigned int)(1000/ animationSpeed);
	//Calculate the next frame and the interpolation value
	unsigned int time = timer.GetMS();
	
	float interpolVal = ((float) time / msPerFrame) + lastInterpol;
	lastInterpol = interpolVal;
	//If the interpolation value is greater than 1, we must increment the frame counter
	while(interpolVal > 1.0f)
	{
		lastFrame ++;
		if(lastFrame<startFrame)
			lastFrame=startFrame;
		if(lastFrame >= endFrame)
		{
			timesAnimated++;
			lastFrame = startFrame;
		}
		interpolVal -= 1.0f;
		lastInterpol = 0.0f;
	}
	if(lastFrame>=header.frameSize)
		lastFrame=startFrame;
	frame* curFrame = &frames[lastFrame];
	frame* nextFrame = &frames[lastFrame+1];
  	  if(lastFrame >= endFrame-1)
		nextFrame = &frames[startFrame];
	//interpolate the vertices
	for(int i = 0; i < header.numVertices; i++)
	{
		vertices[i].x = curFrame->vertices[i].x + (nextFrame->vertices[i].x - curFrame->vertices[i].x) * interpolVal;		
		vertices[i].y = curFrame->vertices[i].y + (nextFrame->vertices[i].y - curFrame->vertices[i].y) * interpolVal;
		vertices[i].z = curFrame->vertices[i].z + (nextFrame->vertices[i].z - curFrame->vertices[i].z) * interpolVal;
	}
    renderAnimFrame();
interpolVal++;
 return timesAnimated;
}

void md2Loader::setSkin(unsigned short num)
{
	if(num>=0 && num<header.numSkins)
		skinNumber=num;
}

/***********************************************************
* temp function for loading a texture into opengl. replace
* with a function from your texture manager.
***********************************************************/
int md2Loader::setTex(char* filename)
{
	unsigned int numTextures=-1;
	 imageFactory imageLoader;
 image *texture=imageLoader.create(filename);
     if(!texture)
	 {
		 cout<<"texture load error"<<endl;
		 return -1;
	 }
   if(!texture->load(filename))
   {
	   cout<<"error in tm load"<<endl;
	   return -1;
   }
   glEnable(GL_TEXTURE_2D);
   glGenTextures(1, &numTextures);
   glBindTexture(GL_TEXTURE_2D, numTextures); 
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 
   glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->getWidth(),texture->getHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,texture->getData());
   glBindTexture(GL_TEXTURE_2D, numTextures); 
   delete texture;
   return numTextures;
}

bool md2Loader::addCustomSkin(char* filename)
{
	int texNum=setTex(filename);
	if(texNum==-1)
	{		
	 return false;
	}
	skins=new skin[1];
	strcpy(skins[0].filename,filename);
	skins[0].texID=texNum;
	skinNumber=0;
 return true;
}

vector3D md2Loader::calculateTriangleNormal(const vector3D v1, const vector3D v2, const vector3D v3)
{
  vector3D nv1=v2-v1;
  vector3D nv2=v3-v1;
  vector3D norm=nv1.crossProduct(nv2);
  norm.normalise();

	return norm;
}

/*****************************************************************************
*Purpose: cycles through a single animation sequence between startFrame and  
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
bool md2Loader::animateOnce(unsigned short startFrame, unsigned short endFrame, unsigned short &curFrame)
{
	  if(curFrame>endFrame)
		  return true;
	  if(curFrame<startFrame)
		  curFrame=startFrame;
	animate(startFrame,endFrame);
	curFrame++;
 return false;
}

void md2Loader::setAnimationSpeed(unsigned short speed)
{
	if(speed>0 && speed <=50)
		animationSpeed=speed;
}