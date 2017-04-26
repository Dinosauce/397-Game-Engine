#include "GameObject.h"

GameObject::GameObject()
{
	pathName = "";
}

void GameObject::LoadGameObject(const char *path)
{
	pathName = path;
	res = OL.LoadMesh(pathName);
}

void GameObject::ShowGameObject()
{
	if (res)
	{
		OL.Render();
	}
}
