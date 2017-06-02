#ifndef __TEMPLIBSINGLETON_H
#define __TEMPLIBSINGLETON_H

#if _MCS_VER >= 1020
#pragma once
#endif
#include "singleton.h"
#include "textureHandler/textureManager.h"
typedef singleton<textureManager> textureMan;

#define texMan textureMan::Instance()

#endif