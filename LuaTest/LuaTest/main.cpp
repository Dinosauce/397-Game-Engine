#include <iostream>
#include <string>
#include "lua_script\C\LuaEngine.h"
#include "Player.h"

int main(int argc, char* argv[]){
	LuaEngine lua_engine;
	Player player(lua_engine.GetPlayer());
	std::cout << player.GetPlayerPosY() << std::endl;

	getchar();
	return 0;
}