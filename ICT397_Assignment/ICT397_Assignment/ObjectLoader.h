#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/mesh.h>  
#include <assimp/postprocess.h>
#include <assimp/texture.h>// Post processing fla
//#include "Texture.h"
using namespace std;

struct Vertex
{
	glm::vec3 m_pos;
	glm::vec2 m_tex;
	glm::vec3 m_normal;

	Vertex(){}

	Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
	}
};

class ObjectLoader
{
public:
	ObjectLoader();
	//~ObjectLoader();

	bool LoadMesh(const string& filename);

	void Render();

private:
	bool InitFromScene(const aiScene* pScene, const string& filename);

	void InitMesh(unsigned int Index, const aiMesh* paiMesh);

	//bool InitMaterials(const aiScene* pScene, const string& filename);

	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF
#define INVALID_OGL_VALUE 0xFFFFFFFF

private:
	struct MeshEntry{
		MeshEntry();
		~MeshEntry();
		void Init(const vector<Vertex>& Vertices, const vector<unsigned int>& Indices);

		GLuint VB;
		GLuint IB;

		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};

	vector<MeshEntry> m_Entries;
	//vector<Texture*> m_Textures;
};

#endif