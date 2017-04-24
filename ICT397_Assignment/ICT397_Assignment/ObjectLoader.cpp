#include "ObjectLoader.h"

bool ObjectLoader::loadOBJ(const char * pathName, vector<glm::vec3>  & out_vertices, vector<glm::vec2>  & out_uvs, vector<glm::vec3>  & out_normals)
{
	FILE *pFile = fopen(pathName, "r");
	if (pFile == NULL){
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(pFile, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;
			fscanf(pFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			glm::vec2 uv;
			fscanf(pFile, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			glm::vec3 normal;
			fscanf(pFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(pFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	fclose(pFile);

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
}