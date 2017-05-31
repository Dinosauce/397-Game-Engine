#ifndef __IMAGEFACTORY_H 
#define __IMAGEFACTORY_H 
#if _MCS_VER >= 1020
  #pragma once
#endif
#include <string>
using namespace std;
#include "image.h"
#include "bmpLoader.h"
#include "tgaLoader.h"
#include "pcx.h"


class imageFactory{
public:
	image* create(string type);
};

#endif