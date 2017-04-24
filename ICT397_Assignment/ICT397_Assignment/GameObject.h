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
		std::vector< glm::vec3 > vertices;
		std::vector< glm::vec2 > uvs;
		std::vector< glm::vec3 > normals;
};