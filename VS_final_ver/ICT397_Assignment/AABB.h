#ifndef __AABB_H
#define __AABB_H
#include "math/GameMathHelp.h"
class AABB
{
private:
	Vector3 min; // min and max coordinates of the object
	Vector3 max; // in the local coordinate system
	AABB createWorldAABB(AABB aabb, Vector3 worldXYZ); // convert aabb to the world
	bool checkCollisionWithPoint(Vector3 &point, AABB &aabb); // the point and aabb must be in
	// the same coordinate system
public:
	AABB();
	AABB(Vector3 minVals, Vector3 maxVals);
	void createAABB(Vector3 vertices[], int numVertices);
	bool checkCollisionWithPoint(Vector3 &point, Vector3 worldXYZ);
	bool checkCollision(Vector3 worldXYZ, AABB &aabb2, Vector3 worldXYZ2);
	const AABB &operator=(const AABB &aabb2);
};
#endif