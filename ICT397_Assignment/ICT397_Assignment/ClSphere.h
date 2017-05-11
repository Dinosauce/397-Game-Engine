///Jayden Grant
#ifndef CLSPHERE_H
#define CLSPHERE_H

#pragma once
#include "Vector3.h"
#include "ClAABB.h"
class ClAABB;

/**
 * Represents a collision sphere centered on a point.
 */
class ClSphere
{
private:
	Vector3 center;
	float radius;

public:
	/**
	 * @brief Constructs the collision sphere at position (0, 0, 0) with a radius of one
	 */
	ClSphere();
	/**
	* @brief Constructs the collision sphere at given position with given radius
	*/
	ClSphere(Vector3 pos, float radius);

	/**
	* @brief Returns the spheres position
	*/
	Vector3 GetPosition() const;
	/**
	* @brief Returns the spheres radius
	*/
	float GetRadius() const;
	/**
	* @brief Sets the spheres position
	*/
	void SetPosition(Vector3 pos);
	/**
	* @brief Sets the spheres radius
	*/
	void SetRadius(float r);

	/**
	 * @brief Translates the sphere by the given vector
	 */
	void Translate(Vector3 v);
	/**
	 * @brief Scales the sphere but the given value
	 */
	void Scale(float s);

	/**
	* @brief Returns the minimum distance beween the point and the sphere (point - surface)
	*/
	float Distance(Vector3 &p);
	/**
	* @brief Returns the minumum distance between the spheres (surface - surface)
	*/
	float Distance(ClSphere &s);
	/**
	* @brief Returns the minimum distance between the sphere and AABB (surface - surface)
	*/
	float Distance(ClAABB &a);

	/**
	* @brief Returns true when the point is inside the sphere
	*/
	bool Contains(Vector3 &p);
	/**
	* @brief Returns true when the spheres intersect
	*/
	bool Intersects(ClSphere &s);
	/**
	* @brief Returns true when the AABB intersects with the sphere
	*/
	bool Intersects(ClAABB &a);
};

#endif