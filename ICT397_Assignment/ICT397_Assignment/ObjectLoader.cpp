#include "ObjectLoader.h"

ObjectLoader::ObjectLoader()
{

}

/*
ObjectLoader::~ObjectLoader()
{
	Clear();
}
*/

bool ObjectLoader::LoadMesh(const string& filename)
{
	bool Ret = false;
	Assimp::Importer Importer;
	const aiScene* pScene = Importer.ReadFile(
		filename.c_str(),
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs
		);

	if(pScene)
	{
		Ret = InitFromScene(pScene, filename);
	}
	else
	{
		printf("Error parsing '%s':'%s'\n", filename.c_str(), Importer.GetErrorString());
	}

	return Ret;
}

bool ObjectLoader::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	m_Textures.resize(pScene->mNumMaterials);

	for (unsigned int i = 0; i < m_Entries.size(); i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh);
	}

	return InitMaterials(pScene, Filename);
}

void ObjectLoader::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

	vector<Vertex> Vertices;
	vector<unsigned int> indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
	{
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z), glm::vec2(pTexCoord->x, pTexCoord->y), glm::vec3(pNormal->x, pNormal->y, pNormal->z));
		Vertices.push_back(v);
	}
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);

		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	m_Entries[Index].Init(Vertices, indices);
}


bool ObjectLoader::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	std::string::size_type SlashIndex = Filename.find_last_of("/");

	std::string Dir;

	if (SlashIndex == std::string::npos)
	{
		Dir = ".";
	}
	else if (SlashIndex == 0)
	{
		Dir = "/";
	}
	else
	{
		Dir = Filename.substr(0, SlashIndex);
	}

	bool Ret = true;

	for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];
		m_Textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString Path;
			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string FullPath = Dir + "/" + Path.data;

				m_Textures[i] = new Texture();

				if (!m_Textures[i]->Load(FullPath.c_str(), i, GL_RGBA, GL_RGBA, 0, 0))
				{
					printf("Error loading texture '%s' \n", FullPath.c_str());
					delete m_Textures[i];
					m_Textures[i] = NULL;
					Ret = false;
				}
				else
				{
					printf("Loaded texture '%s' \n", FullPath.c_str());
				}
			}
		}

	}
	return Ret;
}


ObjectLoader::MeshEntry::MeshEntry()
{
	VB = INVALID_OGL_VALUE;
	IB = INVALID_OGL_VALUE;

	NumIndices = 0;
	MaterialIndex = INVALID_MATERIAL;
}

ObjectLoader::MeshEntry::~MeshEntry()
{
	if (VB != INVALID_OGL_VALUE)
		glDeleteBuffers(1, &VB);
	if (IB != INVALID_OGL_VALUE)
		glDeleteBuffers(1, &IB);
}

void ObjectLoader::MeshEntry::Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices)
{
	NumIndices = Indices.size();
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*NumIndices, &Indices[0], GL_STATIC_DRAW);
}

void ObjectLoader::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < m_Entries.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);
		const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;
		if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex])
		{
			m_Textures[MaterialIndex]->Bind(MaterialIndex);
		}
		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}