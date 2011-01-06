#ifndef BULLET_T_H
#define BULLET_T_H

#define MAX_BULLETS 500

// Bullet Data
struct bullet_t
{
	int x,y;
	int dir;
	int life_remaining;
	int team;
};

#endif

