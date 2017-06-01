#include "GameObject.h"

AABB GameObject::boundingBox;

GameObject::GameObject()
{
	position.x = 1;
	position.y = 1;
	position.z = 1;

	scale.x = 1;
	scale.y = 1;
	scale.z = 1;
}

void GameObject::LoadGameObject(char* Files[], char* type)
{
	gameAssetFactory_handler = gameAssetFactory_factory.Create(type);

	gameAssetFactory_handler->LoadAsset(Files);

	model[0].set(0, 0, 0);  //front face
	model[1].set(15, 0, 0);
	model[2].set(15, 15, 0);
	model[3].set(0, 15, 0);

	model[4].set(0, 0, 15);  //rear face
	model[5].set(15, 0, 15);
	model[6].set(15, 15, 15);
	model[7].set(0, 15, 15);
	boundingBox.createAABB(model, 8);
}

void GameObject::ShowGameObject()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(scale.x, scale.y, scale.z);
	gameAssetFactory_handler->RenderAsset();
	glPopMatrix();
}



bool GameObject::processCollision(GameObject &obj)
{
	if (boundingBox.checkCollision(position, obj.boundingBox, obj.position))
	{
		return true;
	}
	return false;
}
