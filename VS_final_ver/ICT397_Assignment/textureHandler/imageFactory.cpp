#include "imageFactory.h"
#include <string>
#include <iostream>
using namespace std;

// Make an uppercase copy of s:
string upperCase(string& s) {
  char* buf = new char[s.length()];
  s.copy(buf, s.length());
  for(int i = 0; i < s.length(); i++)
    buf[i] = toupper(buf[i]);
  string r(buf, s.length());
  delete buf;
  return r;
}


string getFileExt(string filename)
{
 int pos=filename.find_last_of(".");

	if(pos !=-1 && (filename.length()> pos+1))
	{
		string ext=filename.substr(pos+1,filename.length()); 
		return ext;
	}
 return "";
}

image* imageFactory::create(string filename)
{
	string extension=getFileExt(filename);
	if(extension.length()==0)
		  return NULL;
	string ext=upperCase(extension);
	if(ext=="BMP")
	  {
		return new bmpLoader;
	  }
	  else if(ext=="TGA")
	  {
		return new tgaLoader;
	  }
	  else if (ext == "PCX")
	  {
		  return new pcx;
	  }
	  else 
	  {
		return NULL;
	  }
}