#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H
#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes
 // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class ObjectLoader
{
public:

	ObjectLoader();

	void loadModel(string path);

	void Draw();


private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;	

	void Load(string path);

	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	GLint TextureFromFile(const char* path, string directory);
};


#endif