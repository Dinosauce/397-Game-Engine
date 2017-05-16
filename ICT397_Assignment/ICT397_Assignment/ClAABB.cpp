#include "ClAABB.h"

ClAABB::ClAABB()
{
	Set(min.Zero(), Vector3(1, 1, 1));
}
ClAABB::ClAABB(Vector3 mn, Vector3 mx)
{
	Set(mn, mx);
}

void ClAABB::Validate()
{
	float temp;

	if (min.x > max.x)
	{
		temp = min.x;
		min.x = max.x;
		max.x = temp;
	}
	if (min.y > max.y)
	{
		temp = min.y;
		min.y = max.y;
		max.y = temp;
	}
	if (min.z > max.z)
	{
		temp = min.z;
		min.z = max.z;
		max.z = temp;
	}
}

Vector3 ClAABB::GetMin() const
{
	return min;
}
Vector3 ClAABB::GetMax() const
{
	return max;
}
void ClAABB::Set(Vector3 mn, Vector3 mx)
{
	min.x = mn.x;
	min.y = mn.y;
	min.z = mn.z;

	max.x = mx.x;
	max.y = mx.y;
	max.z = mx.z;

	Validate();
}
void ClAABB::SetMin(Vector3 v)
{
	min.x = v.x;
	min.y = v.y;
	min.z = v.z;

	Validate();
}
void ClAABB::SetMax(Vector3 v)
{
	max.x = v.x;
	max.y = v.y;
	max.z = v.z;

	Validate();
}

void ClAABB::Translate(Vector3 v)
{
	min.x += v.x;
	min.y += v.y;
	min.z += v.z;

	max.x += v.x;
	max.y += v.y;
	max.z += v.z;
}

float ClAABB::Distance(Vector3 &p)
{
	Vector3 c = p.Clamp(min, max);
	return c.Distance(c, p);
}
float ClAABB::Distance(ClSphere &s)
{
	Vector3 p = s.GetPosition();
	Vector3 c = p.Clamp(min, max);
	return (c.Distance(c, p) - s.GetRadius() );
}
float ClAABB::Distance(ClAABB &a)
{
	float x = 0;
	float y = 0;
	float z = 0;

	if (a.max.x < min.x)
		x = a.max.x - min.x;
	else if (a.min.x > max.x)
		x = a.min.x - max.x;

	if (a.max.y < min.y)
		y = a.max.y - min.y;
	else if (a.min.y > max.y)
		y = a.min.y - max.y;

	if (a.max.z < min.z)
		z = a.max.z - min.z;
	else if (a.min.z > max.z)
		z = a.min.z - max.z;

	return sqrt((x*x) + (y*y) + (z*z));
}

bool ClAABB::Contains(Vector3 &p)
{
	return (p.x > min.x && p.x < max.x &&
		p.y > min.y && p.y < max.y &&
		p.z > min.z && p.z < max.z);
}
bool ClAABB::Intersects(ClSphere &s)
{
	return (Distance(s) < 0);
}
bool ClAABB::Intersects(ClAABB &a)
{
	return min.x < a.max.x &&
		min.y < a.max.y &&
		min.z < a.max.z &&
		a.min.x < max.x &&
		a.min.y < max.y &&
		a.min.z < max.z;
}

bool ClAABB::Intersects(ClRay &r)
{
	return r.Intersects(*this);
}