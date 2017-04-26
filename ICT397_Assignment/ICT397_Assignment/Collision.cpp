#include "Collision.h"
#include "Math/float3.h"

ClSphere::ClSphere()
{
	sphere = Sphere(float3(0, 0, 0), 1);
}
ClSphere::ClSphere(Vector3 pos, float radius)
{
	sphere = Sphere(float3(pos.x, pos.y, pos.z), radius);
}

Vector3 ClSphere::GetPosition()
{
	return Vector3(sphere.pos.x, sphere.pos.y, sphere.pos.z);
}
float ClSphere::GetRadius()
{
	return sphere.r;
}
void ClSphere::SetPosition(Vector3 pos)
{
	sphere.pos.x = pos.x;
	sphere.pos.y = pos.y;
	sphere.pos.z = pos.z;
}
void ClSphere::SetRadius(float r)
{
	sphere.r = r;
}

void ClSphere::Translate(Vector3 v)
{
	sphere.Translate(float3(v.x, v.y, v.z));
}
void ClSphere::Scale(float s)
{
	sphere.r *= s;
}

float ClSphere::Distance(Vector3 &p)
{
	return sphere.Distance(float3(p.x, p.y, p.z));
}
float ClSphere::Distance(ClSphere &s)
{
	return sphere.Distance(s.sphere);
}
float ClSphere::Distance(ClAABB &a)
{
	return sphere.Distance(a.aabb);
}

bool ClSphere::Contains(Vector3 &p)
{
	return sphere.Contains(float3(p.x, p.y, p.z));
}
bool ClSphere::Intersects(ClSphere &s)
{
	return sphere.Intersects(s.sphere);
}
bool ClSphere::Intersects(ClAABB &a)
{
	return sphere.Intersects(a.aabb);
}

ClAABB::ClAABB()
{
	aabb = AABB(float3(0, 0, 0), float3(1, 1, 1));
}
ClAABB::ClAABB(Vector3 min, Vector3 max)
{
	aabb = AABB(float3(min.x, min.y, min.z), float3(max.x, max.y, max.z));
}

Vector3 ClAABB::GetMin()
{
	return Vector3(aabb.minPoint.x, aabb.minPoint.y, aabb.minPoint.z);
}
Vector3 ClAABB::GetMax()
{
	return Vector3(aabb.maxPoint.x, aabb.maxPoint.y, aabb.maxPoint.z);
}
void ClAABB::SetMin(Vector3 min)
{
	aabb.minPoint.x = min.x;
	aabb.minPoint.y = min.y;
	aabb.minPoint.z = min.z;
}
void ClAABB::SetMax(Vector3 max)
{
	aabb.maxPoint.x = max.x;
	aabb.maxPoint.y = max.y;
	aabb.maxPoint.z = max.z;
}

void ClAABB::Translate(Vector3 v)
{
	aabb.Translate(float3(v.x, v.y, v.z));
}

float ClAABB::Distance(Vector3 &p)
{
	return aabb.Distance(float3(p.x, p.y, p.z));
}
float ClAABB::Distance(ClSphere &s)
{
	return aabb.Distance(s.sphere);
}

bool ClAABB::Contains(Vector3 &p)
{
	return aabb.Contains(float3(p.x, p.y, p.z));
}
bool ClAABB::Intersects(ClSphere &s)
{
	return aabb.Intersects(s.sphere);
}
bool ClAABB::Intersects(ClAABB &a)
{
	return aabb.Intersects(a.aabb);
}
