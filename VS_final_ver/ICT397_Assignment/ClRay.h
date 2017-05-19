///Jayden Grant
#ifndef CLRAY_H
#define CLRAY_H

#pragma once
#include "Vector3.h"
#include "ClAABB.h"
class ClAABB;
#include "ClSphere.h"
class ClSphere;

/**
 * Represents a collision ray starting from a point extending in a single direction.
 */
class ClRay
{
private:
	Vector3 pos;
	Vector3 dir;

	void Normalize();
public:
	/**
	 * @brief Constructs the ray with given origin and direction. 
	 * If an invalid direction is given (a zero vector) it is set to move directly down (-y)
	 */
	ClRay(Vector3 origin, Vector3 direction);
	
	/** @brief Returns the Rays position / origin
	 */
	Vector3 GetPosition();
	/** @brief Returns the direction of the Ray
	 */
	Vector3 GetDirection();

	/** @brief Sets the position / origin of the Ray.
	 */
	void SetPosition(Vector3 pos);

	/** @brief Sets the direction of the Ray.
	 * If an invalid direction is given (a zero vector) it is set to move directly down (-y)
	 */
	void SetDirection(Vector3 dir);

	/**
	 * @brief Translates the Ray by the given vector
	 */
	void Translate(Vector3 v);

	/** @brief Returns true then the Ray intersects the AABB
	 */
	bool Intersects(ClAABB &aabb);

	/** @brief Returns true then the Ray intersects the Sphere
	 */
	bool Intersects(ClSphere &sphere);

};

#endif //CLRAY_H