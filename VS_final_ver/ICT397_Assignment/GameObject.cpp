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

	rotation_angle = 0.0;
}

void GameObject::LoadGameObject(char* Files[], char* type)
{
	gameAssetFactory_handler = gameAssetFactory_factory.Create(type);

	gameAssetFactory_handler->LoadAsset(Files);
}


void GameObject::SetBoundingBox(double size)
{
	model[0].set(0, 0, 0);  //front face
	model[1].set(size, 0, 0);
	model[2].set(size, size, 0);
	model[3].set(0, size, 0);

	model[4].set(0, 0, size);  //rear face
	model[5].set(size, 0, size);
	model[6].set(size, size, size);
	model[7].set(0, size, size);
	boundingBox.createAABB(model, 8);
}

void GameObject::ShowGameObject()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(scale.x, scale.y, scale.z);
	glRotatef(rotation_angle, 0.0, 1.0, 0.0);
	gameAssetFactory_handler->RenderAsset();
	glPopMatrix();
}

void GameObject::ShowAnimation(int framStart, int framEnd, double speed)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(scale.x, scale.y, scale.z);
	glRotatef(rotation_angle, 0.0, 1.0, 0.0);
	gameAssetFactory_handler->RenderAnimation(framStart, framEnd, speed);
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

