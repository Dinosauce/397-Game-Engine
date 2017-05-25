#ifndef PLAYER_H
#define PLAYER_H

#include "lua_script\C\LuaPlayer.h"

class Player{
public:
	Player(){};
	Player(LuaPlayer lua_player){
		player_pos_x = lua_player.GetPlayerPosX();
		player_pos_y = lua_player.GetPlayerPosY();
		player_pos_z = lua_player.GetPlayerPosZ();
		player_spd = lua_player.GetPlayerSpd();
	}

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