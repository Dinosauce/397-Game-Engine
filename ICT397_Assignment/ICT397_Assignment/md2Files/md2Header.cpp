#include "md2Header.h"

md2Header::md2Header()
{   //set all variables to zero
	memset(this,0,sizeof(md2Header));
}

ostream& operator <<(ostream& out,const md2Header& header)
{
	out << "ident: "<<header.ident<<endl;
	out << "version: "<<header.version<<endl;
	out << "skinWidth: "<<header.skinWidth<<endl;
	out << "skinHeight: "<<header.skinHeight<<endl;
	out << "frameSize: "<<header.frameSize<<endl;
	out << "numSkins: "<<header.numSkins<<endl;
	out << "numVertices: "<<header.numVertices<<endl;
	out << "numTexCoords: "<<header.numTexCoords<<endl;
	out << "numTriangles: "<<header.numTriangles<<endl;
	out << "numGLCommands: "<<header.numGLCommands<<endl;
	out << "numFrames: "<<header.numFrames<<endl;
	out << "offsetSkins: "<<header.offsetSkins<<endl;
	out << "offsetTexCoords: "<<header.offsetTexCoords<<endl;
  	out << "offsetTriangles: "<<header.offsetTriangles<<endl;
	out << "offsetFrames: "<<header.offsetFrames<<endl;
	out << "offsetGLCommands: "<<header.offsetGLCommands<<endl;
	out << "fileSize: "<<header.fileSize<<endl;
	return out;
}



bool md2Header::setHeader(const md2Header& header)
{
   ident=header.ident;
   version=header.version;
   skinWidth=header.skinWidth;
   skinHeight=header.skinHeight;
   frameSize=header.frameSize;
   numSkins=header.numSkins;
   numVertices=header.numVertices;
   numTexCoords=header.numTexCoords;
   numTriangles=header.numTriangles;
   numGLCommands=header.numGLCommands;
   numFrames=header.numFrames;
   offsetSkins=header.offsetSkins;
   offsetTexCoords=header.offsetTexCoords;
   offsetTriangles=header.offsetTriangles;
   offsetFrames=header.offsetFrames;
   offsetGLCommands=header.offsetGLCommands;
   fileSize=header.fileSize;
   return true;
}

bool md2Header::readHeader(char* buf)
{
	  if(!buf)
		return false;
    //read the header from the buffer
	memcpy(this,buf,sizeof(md2Header));
 return true;
}

bool md2Header::operator=(const md2Header& header)
{
   ident=header.ident;
   version=header.version;
   skinWidth=header.skinWidth;
   skinHeight=header.skinHeight;
   frameSize=header.frameSize;
   numSkins=header.numSkins;
   numVertices=header.numVertices;
   numTexCoords=header.numTexCoords;
   numTriangles=header.numTriangles;
   numGLCommands=header.numGLCommands;
   numFrames=header.numFrames;
   offsetSkins=header.offsetSkins;
   offsetTexCoords=header.offsetTexCoords;
   offsetTriangles=header.offsetTriangles;
   offsetFrames=header.offsetFrames;
   offsetGLCommands=header.offsetGLCommands;
   fileSize=header.fileSize;
   return true;
}
void md2Header::printHeader()
{
	 cout<<this;
}