#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
using namespace std;

class ObjectLoader{
public:
	bool loadOBJ(const char *pathName, vector<glm::vec3>  & out_vertices, vector<glm::vec2>  & out_uvs, vector<glm::vec3>  & out_normals);
private:
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< glm::vec3 > temp_vertices;
	vector< glm::vec2 > temp_uvs;
	vector< glm::vec3 > temp_normals;
};