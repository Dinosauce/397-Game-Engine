#include "ClSphere.h"

ClSphere::ClSphere()
{
	center = center.Zero();
	radius = 1.0;
}
ClSphere::ClSphere(Vector3 pos, float r)
{
	center = Vector3(pos);
	radius = r;
}

Vector3 ClSphere::GetPosition() const
{
	return center;
}
float ClSphere::GetRadius() const
{
	return radius;
}
void ClSphere::SetPosition(Vector3 pos)
{
	center.x = pos.x;
	center.y = pos.y;
	center.z = pos.z;
}
void ClSphere::SetRadius(float r)
{
	radius = r;
}

void ClSphere::Translate(Vector3 v)
{
	center.x += v.x;
	center.y += v.y;
	center.z += v.z;
}
void ClSphere::Scale(float s)
{
	radius *= s;
}

float ClSphere::Distance(Vector3 &p)
{
	return center.Distance(center, p) - radius;
}
float ClSphere::Distance(ClSphere &s)
{
	return s.Distance(center) - radius;
}
float ClSphere::Distance(ClAABB &a)
{
	return a.Distance(*this);
}

bool ClSphere::Contains(Vector3 &p)
{
	return center.Distance(center, p) < radius;
}
bool ClSphere::Intersects(ClSphere &s)
{
	return Distance(s) < 0;
}
bool ClSphere::Intersects(ClAABB &a)
{
	return a.Intersects(*this);
}

bool ClSphere::Intersects(ClRay &r)
{
	return r.Intersects(*this);
}