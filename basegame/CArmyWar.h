#ifndef CARMYWAR_H
#define CARMYWAR_H
/*
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <2dlib.h>
*/
#include "ClientLoginData.h"
#include <string.h>
//#include <vector>

#define NORTH		0
#define NORTHEAST	45
#define EAST		90
#define SOUTHEAST	135
#define SOUTH		180
#define SOUTHWEST	225
#define WEST		270
#define NORTHWEST	315

#define BLUE_TEAM	0
#define RED_TEAM	1



class DreamMessage;
class DreamClient;
class Character;
class BaseGame;

typedef struct
{
	float x;
	float y;
} VECTOR2D;

typedef struct Bullet_t
{
	VECTOR2D	vel;
	VECTOR2D	origin;
	VECTOR2D	predictedOrigin;

	bool		shot;
	int			lifetime;
} Bullet_t;

typedef struct
{
	int			key;
	int			heading;

	VECTOR2D	vel;
	VECTOR2D	origin;
	VECTOR2D	predictedOrigin;

	Bullet_t	bullet;

	int			msec;
} command_t;

typedef struct clientData
{
	command_t	frame[COMMAND_HISTORY_SIZE];	// frame history
	command_t	serverFrame;					// the latest frame from server
	command_t	command;						// current frame's commands

	int			index;

	VECTOR2D	startPos;
	bool		team;
	char		nickname[30];
	char		password[30];

    Character* character;

	clientData	*next;
} clientData;

// The main application class interface
class CArmyWar
{
public:
	// Methods

	// Client.cpp
	void	InitialiseEngine(void);
	void	DrawMap(void);
	void	CheckVictory(void);
	void	KillPlayer(int index);
	clientData *GetClientPointer(int index);

	void	CheckPredictionError(int a);
	void	CheckBulletPredictionError(int a);
	void	CalculateVelocity(command_t *command, float frametime);
	void	CalculateHeading(command_t *command);
	void	CalculateBulletVelocity(command_t *command);
	void	PredictMovement(int prevFrame, int curFrame);
	void	MoveObjects(void);

	void	AddClient(int local, int index, char *name);
	void	RemoveClient(int index);
	void	RemoveClients(void);

	// Network.cpp
	void	ReadPackets(void);
	void	SendCommand(void);
	void	SendRequestNonDeltaFrame(void);
	void	ReadMoveCommand(DreamMessage *mes, clientData *client);
	void	ReadDeltaMoveCommand(DreamMessage *mes, clientData *client);
	void	BuildDeltaMoveCommand(DreamMessage *mes, clientData *theClient);

	// Variables

	// Network variables
	DreamClient *networkClient;

	clientData *clientList;			// Client list
	clientData *localClient;		// Pointer to the local client in the client list
	int clients;

	clientData inputClient;			// Handles all keyboard input

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

	//Character* myCharacter;

	float frametime;

	char gamename[32];
	bool inProgress;
	bool init;

	// Tile scroll positions
	int scrollX;
	int scrollY;
	int tileScrollX;
	int tileScrollY;

	bool mapdata[100][100];
	int gameIndex;

	float targetRotation;			// variable to rotate the target images

	int redScore;
	int blueScore;

	float flagX;
	float flagY;
	clientData *playerWithFlag;



public:
	CArmyWar(BaseGame* baseGame);
	~CArmyWar();

	// Client.cpp
	void	Shutdown  (void);
	void	CheckKeys (void);
	void	Frame     (void);
	void	RunNetwork(int msec);
	
	// Network.cpp
	void	StartConnection(int ind);
	void	Connect(void);
	void	Disconnect(void);
	void	SendStartGame(void);

	void	SetName(char *n)		{ strcpy(gamename, n); }
	char	*GetName(void)			{ return gamename; }

	void	SetGameIndex(int index)	{ gameIndex = index; }
	int		GetGameIndex(void)		{ return gameIndex; }

	clientData *GetClientList(void) { return clientList; }

	void	SetInProgress(bool p)	{ inProgress = p; }	
	bool	GetInProgress(void)		{ return inProgress; }

	CArmyWar *next;

    bool keys[256];

#ifdef WIN32
	//do nothing
#else

#define VK_ESCAPE 0	
#define VK_DOWN 1
#define VK_UP 2
#define VK_LEFT 3
#define VK_RIGHT 4
#define VK_SPACE 5
#endif



	//char* serverIP;
	//std::vector<Character>* characterVector;

	BaseGame* mBaseGame;
};

#endif
