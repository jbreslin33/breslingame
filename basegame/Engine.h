#ifndef ENGINE_H
#define ENGINE_H

// Define the map
extern bool mapdata[100][100];

// Tile scroll positions
extern int scroll_x, scroll_y;

// Player Data
#define BLUE_TEAM 0
#define RED_TEAM  1

#define NORTH     0
#define NORTHEAST 45
#define EAST      90
#define SOUTHEAST 135
#define SOUTH     180
#define SOUTHWEST 225
#define WEST      270
#define NORTHWEST 315

#define USMSG_STARTGAME		WM_USER + 2
#define USMSG_SHUTDOWNGAME	WM_USER + 3

extern int final_winning_team;

extern struct Player_t players[16];	// limit of 16 players

//#include "main.h"
//#include "network.h"
//#include "lobby.h"

//#include "..\tutGameServer\netcommon.h"

// Graphic Declarations
/*
GFX_IMAGE2D grass;				// variable to hold 'cdrom' graphic
GFX_IMAGE2D redman;				// variable to hold 'cdrom' graphic
GFX_IMAGE2D blueman;			// variable to hold 'cdrom' graphic
GFX_IMAGE2D tree;				// variable to hold 'cdrom' graphic
GFX_IMAGE2D redtarget;			// variable to hold 'cdrom' graphic
GFX_IMAGE2D bluetarget;			// variable to hold 'cdrom' graphic
GFX_IMAGE2D flag;				// variable to hold 'cdrom' graphic
GFX_IMAGE2D rednumbers[10];		// variable to hold 'cdrom' graphic
GFX_IMAGE2D bluenumbers[10];	// variable to hold 'cdrom' graphic
*/
float target_rotation = 0.0;	// variable to rotate the target images

// Define the map
bool mapdata[100][100];

// Tile scroll positions
int scroll_x, scroll_y;
int tile_scroll_x = 0;
int tile_scroll_y = 0;

// Flag Data
int flag_x;
int flag_y;

int local_x;		// Reference coordinate
int local_y;		// Reference coordinate
bool southeast;		// Direction flag
bool southwest;		// Direction flag
bool northeast;		// Direction flag
bool northwest;		// Direction flag
bool south;			// Direction flag
bool north;			// Direction flag
bool east;			// Direction flag
bool west;			// Direction flag
bool stopped;		// Direction flag

struct Player_t players[16];	// limit of 16 players
int ingame_players;				// the number of players in the game
int half_players;				// half the amount of players in the game
int place_pos_x;
int player_with_flag_id;

struct Bullet_t bullets[MAX_BULLETS]; // limit of 500 bullets (at once)

int red_score;
int blue_score;

int final_winning_team;

int engine_inited;


class Engine
{

Engine();
~Engine();

void ENGINE_Init(void);
void ENGINE_Render(void);
void ENGINE_ProcessInput(void);
void ENGINE_GenerateRandomMap(void);
void ENGINE_DrawMap(void);
void ENGINE_Shutdown(void);
void ENGINE_AddPlayer(int team);
void ENGINE_AddBullet(int x,int y,int dir,int team);
void ENGINE_UpdateBullets(void);
};

#endif