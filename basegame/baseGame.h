#ifndef BASEGAME_H
#define BASEGAME_H

#include "../baseapplication/BaseApplication.h"
#include "../math/Vector3D.h"
#include "../command/ClientSideCommand.h"
#include "../client/ClientSideClient.h"

//#include "Tutorial4.h"
class DreamMessage;
class DreamClient;


extern bool keys[256];


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

/*
typedef struct ClientSideClient
{
	ClientSideCommand	frame[64];	// frame history
	ClientSideCommand	serverFrame;					// the latest frame from server
	ClientSideCommand	command;						// current frame's commands

.int			index;
.
.	Vector3D	startPos;
.	bool		team;
.	char		nickname[30];
	char		password[30];

	Ogre::SceneNode *myNode;

	ClientSideClient	*next;
} ClientSideClient;
*/
// The main application class interface
class BaseGame : public BaseApplication
{
private:
	// Methods

	// Client.cpp
	void	DrawMap(void);
	
	void	CheckPredictionError(int a);
	void	CalculateVelocity(ClientSideCommand *command, float frametime);
	void	PredictMovement(int prevFrame, int curFrame);
	void	MoveObjects(void);

	void	AddClient(int local, int index, char *name);
	void	RemoveClient(int index);
	void	RemoveClients(void);

	// Network.cpp
/*	
void	ReadPackets(void);
	void	SendCommand(void);
	void	SendRequestNonDeltaFrame(void);
	void	ReadMoveCommand(DreamMessage *mes, ClientSideClient *client);
	void	ReadDeltaMoveCommand(DreamMessage *mes, ClientSideClient *client);
	void	BuildDeltaMoveCommand(DreamMessage *mes, ClientSideClient *theClient);
*/
	bool processUnbufferedInput(const Ogre::FrameEvent& evt);


	// Variables

	// Network variables
	DreamClient *networkClient;

	ClientSideClient *clientList;			// Client list
	ClientSideClient *localClient;		// Pointer to the local client in the client list
	int clients;

	ClientSideClient inputClient;			// Handles all keyboard input

	float frametime;

	char gamename[32];
	bool init;

	//bool mapdata[100][100];
	int gameIndex;


public:
	BaseGame();
	~BaseGame();

    void createPlayer(int index);
    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool keyPressed( const OIS::KeyEvent &arg );

	// Client.cpp
	void	Shutdown(void);
	void	CheckKeys(void);
	void	Frame(void);
	void	RunNetwork(int msec);
	
	// Network.cpp
	void	StartConnection();
	void	Connect(void);
	void	Disconnect(void);
	void	SendStartGame(void);

	void	SetName(char *n)		{ strcpy(gamename, n); }
	char	*GetName(void)			{ return gamename; }

	void	SetGameIndex(int index)	{ gameIndex = index; }
	int		GetGameIndex(void)		{ return gameIndex; }

	ClientSideClient *GetClientList(void) { return clientList; }

	ClientSideClient *GetClientPointer(int index);


	BaseGame *next;
};

#endif
