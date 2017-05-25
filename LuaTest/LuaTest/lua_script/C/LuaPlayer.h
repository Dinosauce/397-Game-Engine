#ifndef LUAPLAYER_H
#define LUAPLAYER_H

#include "Lua/lua.hpp"

class LuaPlayer{
public:
	LuaPlayer(){
		ReadFile();
	};

	void ReadFile(){
		lua_State *lua_file = lua_open();

		luaL_openlibs(lua_file);
		luaL_loadfile(lua_file, "lua_script/Player/Player.lua");
		lua_pcall(lua_file, 0, 0, 0);

		lua_getglobal(lua_file, "player_pos_x");
		lua_getglobal(lua_file, "player_pos_y");
		lua_getglobal(lua_file, "player_pos_z");
		lua_getglobal(lua_file, "player_spd");

		player_pos_x = lua_tonumber(lua_file, 1);
		player_pos_y = lua_tonumber(lua_file, 2);
		player_pos_z = lua_tonumber(lua_file, 3);
		player_spd = lua_tonumber(lua_file, 4);

		lua_close(lua_file);
	};

	double GetPlayerPosX(){ return player_pos_x; };
	double GetPlayerPosY(){ return player_pos_y; };
	double GetPlayerPosZ(){ return player_pos_z; };
	double GetPlayerSpd(){ return player_spd; };


private:
	double player_pos_x;// Vector3
	double player_pos_y;
	double player_pos_z;
	double player_spd;
};

#endif