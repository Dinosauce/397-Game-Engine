#include "Terrain.h"
#include <SDL/SDL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
using namespace std;

void terrain::loadHeightfield(const char *filename, const int size) {
	//open for binary read
	ifstream infile(filename, ios::binary);
	if (!infile) {
		cout << "Cannot open file :" << filename << endl;
		Loaded = false;
	}
	//allocate memory
	if (terrainData)
		delete[] terrainData;
	if (size>0)
		terrainData = new unsigned char[size*size];
	if (terrainData == NULL)
		Loaded = false;
	//read in heightfield.
	// get length of file:
	infile.seekg(0, ios::end);
	int length = infile.tellg();
	// read data as a block:
	infile.seekg(0, ios::beg);
	infile.read(reinterpret_cast<char *>(terrainData), length);
	infile.close();
	this->size = size;
	Loaded = true;
}

void terrain::setScalingFactor(float xScale, float yScale, float zScale) {
	scaleX = xScale;
	scaleY = yScale;
	scaleZ = zScale;
}

float terrain::getHeight(int xpos, int zpos) {
	if (inbounds(xpos, zpos)) {
		return ((float)(terrainData[(zpos*size) + xpos])*scaleY);
	}
}

unsigned char terrain::getHeightColor(int xpos, int zpos) {
	if (inbounds(xpos, zpos)) {
		return terrainData[zpos*size + xpos];
	}
	return 1;
}

bool terrain::inbounds(int xpos, int zpos)
{
	return((xpos >= 0 && xpos <= 128) && (zpos >= 0 && zpos <= 128));
}

void terrain::render() {
	unsigned char hcolor; //color of the height
	setScalingFactor(1, 3, 1);
	//float texLeft, texBottom, texTop;


	/*if (textureMapping) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.GetID());
	}*/

	if (Loaded)
	{

		//loop through the z axis
		for (int z = 0; z<getSize() - 1; z++) {
			//loop through the x axis
			glBegin(GL_TRIANGLE_STRIP);
			for (int x = 0; x<getSize(); x++) {
				//create the the first point in the triangle strip
				hcolor = getHeightColor(x, z);
				glColor3ub(hcolor, hcolor, hcolor);
				glVertex3f((float)x*scaleX, getHeight(x, z)*0.1, (float)z*scaleZ);

				//create the next point in the triangle strip
				hcolor = getHeightColor(x, z + 1);
				glColor3ub(hcolor, hcolor, hcolor);
				glVertex3f((float)x*scaleX, getHeight(x, z + 1)*0.1, (float)(z + 1)*scaleZ);
			}
			glEnd();
		}
	}
	else
	{
		cout << "failed to load" << endl;
	}
}