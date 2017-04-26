///Jayden Grant
#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3.h"
#include "Geometry/Sphere.h"
#include "Geometry/AABB.h"

/**
 * Represents a collision sphere centered on a point.
 */
class ClSphere
{
public:
	Sphere sphere;

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
	Vector3 GetPosition();
	/**
	* @brief Returns the spheres radius
	*/
	float GetRadius();
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

/**
 * Represenst an axis aligned bounding box, defined by two corners
 */
class ClAABB
{
public:
	AABB aabb;

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
	Vector3 GetMin();
	/**
	* @brief Returns the maximum corner position
	*/
	Vector3 GetMax();
	/**
	* @brief Sets the minimum corner position
	*/
	void SetMin(Vector3 minPos);
	/**
	* @brief Sets the maximum corner position
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
	* @brief Returns the minimum distance between the AABBs (surface - surface)
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