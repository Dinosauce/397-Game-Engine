#include "GameObject.h"


GameObject::GameObject()
{
	position.x = 1;
	position.y = 1;
	position.z = 1;
}

void GameObject::LoadGameObject(const char* Files[], char* type)
{
	gameAssetFactory_handler = gameAssetFactory_factory.Create(type);

	gameAssetFactory_handler->LoadAsset(Files);
}

void GameObject::ShowGameObject()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	gameAssetFactory_handler->RenderAsset();
	glPopMatrix();
}
