#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "ObjectLoader.h"

class GameObject
{
	public:

		GameObject();
		void LoadGameObject(const char * path);
		void ShowGameObject();

	private:
		ObjectLoader OL;
		bool res;
		const char * pathName;
};

#endif