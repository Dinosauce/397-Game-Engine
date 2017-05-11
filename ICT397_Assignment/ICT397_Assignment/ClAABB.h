///Jayden Grant
#ifndef CLAABB_H
#define CLAABB_H

#pragma once
#include "Vector3.h"
#include "ClSphere.h"
class ClSphere;


/**
* Represenst an axis aligned bounding box, defined by two corners
*/
class ClAABB
{
private:
	Vector3 min;
	Vector3 max;

	/// Ensures the minimum and maximum points are in correct order
	void Validate();

public:
	/**
	* @brief Constructs an AABB from (0, 0, 0) to (1, 1, 1)
	*/
	ClAABB();
	/**
	* @brief Constructs an AABB with opposite corners min and max
	*/
	ClAABB(Vector3 min, Vector3 max);

	/**
	* @brief Returns the minimum corner position
	*/
	Vector3 GetMin() const;
	/**
	* @brief Returns the maximum corner position
	*/
	Vector3 GetMax() const;
	/**
	* @brief Sets the minimum and maximum corner positions and validates AABB
	*/
	void Set(Vector3 min, Vector3 max);
	/**
	* @brief Sets the minimum corner position and validates AABB
	* Use set if changing both min and max.
	*/
	void SetMin(Vector3 minPos);
	/**
	* @brief Sets the maximum corner position  and validates AABB
	* Use set if changing both min and max.
	*/
	void SetMax(Vector3 maxPos);

	/**
	* @brief Translates the AABB by the given vector
	*/
	void Translate(Vector3 v);

	/**
	* @brief Returns the minimum distance between the AABB and the point (point - surface)
	*/
	float Distance(Vector3 &p);
	/**
	* @brief Returns the minimum distance between the AABB and sphere (surface - surface)
	*/
	float Distance(ClSphere &s);
	/**
	* @brief Returns the minimum distance between the AABBs (surface - surface), or 0 if touching/intersecting/containing.
	*/
	float Distance(ClAABB &a);

	/**
	* @brief Returns true when the point is within the AABB
	*/
	bool Contains(Vector3 &p);
	/**
	* @brief Returns true when the AABB intersects with the sphere
	*/
	bool Intersects(ClSphere &s);
	/**
	* @brief Returns true when the AABBs intersect
	*/
	bool Intersects(ClAABB &a);

};

#endif