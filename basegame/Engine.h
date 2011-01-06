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

void ENGINE_Init(void);
void ENGINE_Render(void);
void ENGINE_ProcessInput(void);
void ENGINE_GenerateRandomMap(void);
void ENGINE_DrawMap(void);
void ENGINE_Shutdown(void);
void ENGINE_AddPlayer(int team);
void ENGINE_AddBullet(int x,int y,int dir,int team);
void ENGINE_UpdateBullets(void);

#endif