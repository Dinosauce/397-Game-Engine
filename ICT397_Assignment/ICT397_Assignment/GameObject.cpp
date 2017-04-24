#include "GameObject.h"

GameObject::GameObject()
{
	pathName = "";
}

void GameObject::LoadGameObject(const char *path)
{
	pathName = path;
	res = OL.loadOBJ(pathName, vertices, uvs, normals);
}

void GameObject::ShowGameObject()
{
	if (res)
	{
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	}
}
