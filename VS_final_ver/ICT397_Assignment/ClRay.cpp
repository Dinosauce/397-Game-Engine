#include "ClRay.h"
#include <limits>
#include <algorithm>

ClRay::ClRay(Vector3 s, Vector3 d)
{
	SetPosition(s);
	SetDirection(d);
}

Vector3 ClRay::GetPosition(){
	return pos;
}

Vector3 ClRay::GetDirection(){
	return dir;
}

void ClRay::SetPosition(Vector3 p){
	pos.x = p.x;
	pos.y = p.y;
	pos.z = p.z;
}

void ClRay::SetDirection(Vector3 d){
	if (d.x + d.y + d.z == 0)
	{//Ray cannot have no direction
		dir.x = 0;
		dir.y = -1;
		dir.z = 0;
	}
	else
	{
		dir.x = d.x;
		dir.y = d.y;
		dir.z = d.z;
		Normalize();
	}
}

void ClRay::Translate(Vector3 v){
	pos.x += v.x;
	pos.y += v.y;
	pos.z += v.z;
}

bool ClRay::Intersects(ClAABB &a)
{
	//Using the Slab Method

	float imin = -(std::numeric_limits<float>::infinity());
	float imax = std::numeric_limits<float>::infinity();

	if (dir.x != 0.0)
	{
		float ix1 = (a.GetMin().x - pos.x) / dir.x;
		float ix2 = (a.GetMax().x - pos.x) / dir.x;

		imin = std::max(imin, std::min(ix1, ix2));
		imax = std::min(imax, std::max(ix1, ix2));
	}
	if (dir.y != 0.0)
	{
		float iy1 = (a.GetMin().y - pos.y) / dir.y;
		float iy2 = (a.GetMax().y - pos.y) / dir.y;

		imin = std::max(imin, std::min(iy1, iy2));
		imax = std::min(imax, std::max(iy1, iy2));
	}
	if (dir.z != 0.0)
	{
		float iz1 = (a.GetMin().z - pos.z) / dir.z;
		float iz2 = (a.GetMax().z - pos.z) / dir.z;

		imin = std::max(imin, std::min(iz1, iz2));
		imax = std::min(imax, std::max(iz1, iz2));
	}

	return imin < imax;
}

bool ClRay::Intersects(ClSphere &s)
{// Based on code by Miguel Casillas
	if (s.Contains(pos))
		return true;

	Vector3 srV = s.GetPosition() - pos;

	// Magnitude towards sphere
	float d1 = srV.Dot(dir);

	if (d1 < 0) // Ray is pointing awway from sphere
		return false;

	// Closest point to sphere
	Vector3 cP = Vector3(pos + (dir * d1));

	// Check if that closest point is contained within the sphere
	return s.Contains(cP);
}

void ClRay::Normalize()
{
	//Normalize direction vector
	float mag = dir.x * dir.x + dir.y * dir.y + dir.z + dir.z;
	if (mag != 1)
	{
		mag = sqrt(mag);
		dir.x /= mag;
		dir.y /= mag;
		dir.z /= mag;
	}
}