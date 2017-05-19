#include "GameObject.h"


GameObject::GameObject()
{
	
}

void GameObject::LoadGameObject(const char *path, char* type)
{
	gameAssetFactory_handler = gameAssetFactory_factory.Create(type);

	gameAssetFactory_handler->LoadAsset(path);
}

void GameObject::ShowGameObject()
{

	gameAssetFactory_handler->RenderAsset();
}
