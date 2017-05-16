///Jayden Grant
#ifndef CLRAY_H
#define CLRAY_H

#include "Vector3.h"

#pragma once
class ClRay
{
private:
	Vector3 pos, dir;
public:
	ClRay(Vector3 start, Vector3 direction);


};

#endif //CLRAY_H