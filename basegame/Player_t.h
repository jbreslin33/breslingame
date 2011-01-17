#ifndef PLAYER_T_H
#define PLAYER_T_H

// Player Data
struct Player_t
{
	int playerIndex;
	int x,y;
	int dx,dy;
	int start_x,start_y; // for re-spawning
	int dir;
	int team;
	int fire_delay;
};

#endif
