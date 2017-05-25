#ifndef LUAENGINE_H
#define LUAENGINE_H

#include "Lua\lua.hpp"
#include "LuaPlayer.h"
#include "LuaGameObject.h"

class LuaEngine{
public:
	LuaEngine(){
		
	}
	
	LuaPlayer GetPlayer(){ return player; };

private:
	LuaPlayer player;
};

#endif