#include "CArmyWar.h"
#include "../dreamsock/DreamClient.h"
#include "../dreamsock/DreamSock.h"

#include "../charactercontrollers/Character.h"
#include "BaseGame.h"
#include "Ogre.h"
using namespace Ogre;

CArmyWar::CArmyWar(BaseGame* baseGame)
{
	mBaseGame = baseGame;

	//serverIP = "127.0.0.1";
	networkClient	= new DreamClient();
	clientList		= NULL;
	localClient		= NULL;
	clients			= 0;

	memset(&inputClient, 0, sizeof(clientData));
	memset(&mapdata, 0, sizeof(mapdata));

	frametime		= 0.0f;

	inProgress		= false;
	init			= false;

	scrollX			= 0;
	scrollY			= 0;

	tileScrollX		= 0;
	tileScrollY		= 0;

	gameIndex		= 0;

	targetRotation	= 0.0f;

	redScore		= 0;
	blueScore		= 0;

	playerWithFlag	= NULL;

	next			= NULL;

	//myCharacter = NULL;
	//Character* jaywad = new Character(mBaseGame->getSceneManager(), "jaydd", "Sinbad.mesh", "RunBase",  0,  5, 0);
}


CArmyWar::~CArmyWar()
{
	delete networkClient;
}

void CArmyWar::ReadPackets(void)
{
	char data[1400];
	struct sockaddr address;

	clientData *clList;

	int type;
	int ind;
	int local;
	int ret;

	char name[50];

	DreamMessage mes;
	mes.Init(data, sizeof(data));

	while(ret = networkClient->GetPacket(mes.data, &address))
	{
		mes.SetSize(ret);
		mes.BeginReading();

		type = mes.ReadByte();

		switch(type)
		{
		case DREAMSOCK_MES_ADDCLIENT:
			local	= mes.ReadByte();
			ind		= mes.ReadByte();
			strcpy(name, mes.ReadString());

			AddClient(local, ind, name);
			break;

		case DREAMSOCK_MES_REMOVECLIENT:
			ind = mes.ReadByte();

			LogString("Got removeclient %d message", ind);

			RemoveClient(ind);

			if(clientList == NULL)
			{
				LogString("clientList == NULL, sending remove game %s", gamename);
//				Lobby.SendRemoveGame(gamename);
			}
			break;

		case USER_MES_FRAME:
			// Skip sequences
			mes.ReadShort();
			mes.ReadShort();

			for(clList = clientList; clList != NULL; clList = clList->next)
			{
//				LogString("Reading DELTAFRAME for client %d", clList->index);
				ReadDeltaMoveCommand(&mes, clList);
			}

			break;

		case USER_MES_NONDELTAFRAME:
			// Skip sequences
			mes.ReadShort();
			mes.ReadShort();

			clList = clientList;

			for(clList = clientList; clList != NULL; clList = clList->next)
			{
				LogString("Reading NONDELTAFRAME for client %d", clList->index);
				ReadMoveCommand(&mes, clList);
			}

			break;

		case USER_MES_SERVEREXIT:
			MessageBox(NULL, "Server disconnected", "Info", MB_OK);
			Disconnect();
			break;

		case USER_MES_STARTGAME:
			// Skip sequences
			mes.ReadShort();
			mes.ReadShort();

//			DestroyWindow(hWnd_JoinGameDialog);

			InitialiseEngine();

			break;

		case USER_MES_MAPDATA:
			// Skip sequences
			mes.ReadShort();
			mes.ReadShort();

			for(int m = 0; m < 300; m++)
			{
				int i = mes.ReadByte();
				int j = mes.ReadByte();

				mapdata[i][j] = true;
			}

			break;

		}
	}
}
void CArmyWar::AddClient(int local, int ind, char *name)
{
//Character* jaybird = new Character(mBaseGame->getSceneManager(), "jayman", "Sinbad.mesh", "RunBase",  0,  5, 0);
	// First get a pointer to the beginning of client list
	clientData *list = clientList;
	clientData *prev;

	LogString("App: Client: Adding client with index %d", ind);

	// No clients yet, adding the first one
	if(clientList == NULL)
	{
		LogString("App: Client: Adding first client");

		clientList = (clientData *) calloc(1, sizeof(clientData));

		if(local)
		{
			LogString("App: Client: This one is local");
			localClient = clientList;
		}

		clientList->index = ind;
		clientList->character = new Character(mBaseGame->getSceneManager(), "jay" + ind, "Sinbad.mesh", "RunBase",  0,  5, 0);
		strcpy(clientList->nickname, name);

		if(clients % 2 == 0)
			clientList->team = RED_TEAM;
		else
			clientList->team = BLUE_TEAM;

		clientList->next = NULL;
	}
	else
	{
		LogString("App: Client: Adding another client");

		prev = list;
		list = clientList->next;

		while(list != NULL)
		{
			prev = list;
			list = list->next;
		}

		list = (clientData *) calloc(1, sizeof(clientData));

		if(local)
		{
			LogString("App: Client: This one is local");
			localClient = list;
		}

		list->index = ind;
		clientList->character = new Character(mBaseGame->getSceneManager(), "jay" + ind, "Sinbad.mesh", "RunBase",  0,  5, 0);
		strcpy(list->nickname, name);

		if(clients % 2 == 0)
			list->team = RED_TEAM;
		else
			list->team = BLUE_TEAM;

		list->next = NULL;
		prev->next = list;
	}

	clients++;

	// If we just joined the game, request a non-delta compressed frame
	if(local)
		SendRequestNonDeltaFrame();

//	Lobby.RefreshJoinedPlayersList();
}


void CArmyWar::InitialiseEngine(void)
{
	// Init the Graphics Engine
/*
	GFX_Init("Army War Engine v2.0", 640, 480, 16, 0, ApplicationProc);

	// Load Required Graphics
	GFX_LoadBitmap(&grass,      "gfx\\grass.bmp");	
	GFX_LoadBitmap(&redman,     "gfx\\redman.bmp");	
	GFX_LoadBitmap(&blueman,    "gfx\\blueman.bmp");
	GFX_LoadBitmap(&tree,       "gfx\\tree.bmp");
	GFX_LoadBitmap(&redtarget,  "gfx\\redtarget.bmp");
	GFX_LoadBitmap(&bluetarget, "gfx\\bluetarget.bmp");
	GFX_LoadBitmap(&flag,       "gfx\\flag.bmp");

	GFX_LoadBitmap(&rednumbers[0], "gfx\\red0.bmp");
	GFX_LoadBitmap(&rednumbers[1], "gfx\\red1.bmp");
	GFX_LoadBitmap(&rednumbers[2], "gfx\\red2.bmp");
	GFX_LoadBitmap(&rednumbers[3], "gfx\\red3.bmp");
	GFX_LoadBitmap(&rednumbers[4], "gfx\\red4.bmp");
	GFX_LoadBitmap(&rednumbers[5], "gfx\\red5.bmp");
	GFX_LoadBitmap(&rednumbers[6], "gfx\\red6.bmp");
	GFX_LoadBitmap(&rednumbers[7], "gfx\\red7.bmp");
	GFX_LoadBitmap(&rednumbers[8], "gfx\\red8.bmp");
	GFX_LoadBitmap(&rednumbers[9], "gfx\\red9.bmp");

	GFX_LoadBitmap(&bluenumbers[0], "gfx\\blue0.bmp");
	GFX_LoadBitmap(&bluenumbers[1], "gfx\\blue1.bmp");
	GFX_LoadBitmap(&bluenumbers[2], "gfx\\blue2.bmp");
	GFX_LoadBitmap(&bluenumbers[3], "gfx\\blue3.bmp");
	GFX_LoadBitmap(&bluenumbers[4], "gfx\\blue4.bmp");
	GFX_LoadBitmap(&bluenumbers[5], "gfx\\blue5.bmp");
	GFX_LoadBitmap(&bluenumbers[6], "gfx\\blue6.bmp");
	GFX_LoadBitmap(&bluenumbers[7], "gfx\\blue7.bmp");
	GFX_LoadBitmap(&bluenumbers[8], "gfx\\blue8.bmp");
	GFX_LoadBitmap(&bluenumbers[9], "gfx\\blue9.bmp");
*/
	// Set the scroll positions
	scrollX = 40*32;

	if(localClient->team == RED_TEAM)
		scrollY = 90*32;
	else
		scrollY = 0;

	// Set the flag position
	flagX = 49*32;
	flagY = 49*32;

	playerWithFlag = NULL;

	// Reset score counters
	redScore	= 0;
	blueScore	= 0;
}

void CArmyWar::DrawMap(void)
{
	int heading = 0;

	 // Work out how many tiles have been scrolled
   	tileScrollX = scrollX/32;
   	tileScrollY = scrollY/32;

	for(int i = (tileScrollX)-2; i < (tileScrollX)+21; i++)
   	{
   		for(int j = (tileScrollY)+15; j > (tileScrollY)-2; j--)
   		{
 			//GFX_Blit(&grass, (32*i)-(scrollX),(32*j)-(scrollY), 32, 32, 0);

			// Draw a tree if required
			if(mapdata[i][j] == true)
			{
			//	GFX_Blit(&tree, (32*i+16)-(scrollX),(32*j+16)-(scrollY), 32, 32, 0);
			}
			
			// Draw the static targets
			if(i==49 && j==3)
			{
				// draw the blue target
			//	GFX_Blit(&bluetarget, (32*i)-(scrollX),(32*j)-(scrollY),
			//		32, 32, targetRotation);
			}

			if(i==49 && j==97)
			{
				// draw the blue target
			//	GFX_Blit(&redtarget, (32*i)-(scrollX),(32*j)-(scrollY),
			//		32, 32, targetRotation);
			}
		}
	}

	// Render the flag
	//GFX_Blit(&flag, ((int) flagX)-(scrollX), ((int) flagY)-(scrollY), 32, 32, 0);

	// Render players
	clientData *list = clientList;

	for( ; list != NULL; list = list->next)
	{
		if(list->team == RED_TEAM)
		{
	//		GFX_Blit(&redman, ((int) list->command.origin.x)-(scrollX),
	//			((int) list->command.origin.y)-(scrollY),
	//			32, 32, (float) list->command.heading);
		}

		if(list->team == BLUE_TEAM)
		{
	//		GFX_Blit(&blueman, ((int) list->command.origin.x)-(scrollX),
	//			((int) list->command.origin.y)-(scrollY),
	//			32, 32, (float) list->command.heading);
		}

		// Render bullets
		if(list->command.bullet.shot)
		{
			if(list->team == RED_TEAM)
			{
	//			GFX_RectFill(((int) list->command.bullet.origin.x-2)-(scrollX),
	//				((int) list->command.bullet.origin.y-2)-(scrollY),
	//				((int) list->command.bullet.origin.x+2)-(scrollX),
	//				((int) list->command.bullet.origin.y+2)-(scrollY), 200, 0, 0);
			}

			if(list->team == BLUE_TEAM)
			{
	//			GFX_RectFill(((int) list->command.bullet.origin.x-2)-(scrollX),
	//				((int) list->command.bullet.origin.y-2)-(scrollY),
	//				((int) list->command.bullet.origin.x+2)-(scrollX),
	//				((int) list->command.bullet.origin.y+2)-(scrollY), 0, 0, 200);
			}
		}
	}

	// Finally, Render the Team Scores
	//GFX_Blit(&rednumbers[redScore], 5, 410, 64, 64, 0);
	//GFX_Blit(&bluenumbers[blueScore], 570, 410, 64, 64, 0);
}

void CArmyWar::Frame(void)
{
	if(!localClient)
		return;

	// Scroll the map to follow the local player
	if((localClient->command.origin.x - scrollX) > 340)
	{
		if(scrollX <= 3200-(19*32)-2)
			scrollX += 2;
	}

	if((localClient->command.origin.x - scrollX) < 300)
	{
		if(scrollX >= 2)
			scrollX -= 2;
	}

	if((localClient->command.origin.y - scrollY) > 260)
	{
		if(scrollY <= 3200-(15*32)-2)
			scrollY += 2;
	}

	if((localClient->command.origin.y - scrollY) < 220)
	{
		if(scrollY >= 2)
			scrollY -= 2;
	}

	// Move the flag with the player
	if(playerWithFlag)
	{
		flagX = playerWithFlag->command.origin.x;
		flagY = playerWithFlag->command.origin.y;
	}

	// Rotate the target images
	if(targetRotation < 360)
		targetRotation += 1;
	else
		targetRotation -= targetRotation;

	// Draw map
	/*
	GFX_Begin();
	{
		DrawMap();
	}
	GFX_End();
	*/
}

void CArmyWar::Shutdown(void)
{
	//Disconnect();
/*
	GFX_Begin();
	GFX_Shutdown();
	GFX_End();
*/
}

void CArmyWar::CheckVictory(void)
{
	if(localClient == NULL)
		return;

	// Check team scores
	if(redScore > 1)
	{
		if(localClient->team == RED_TEAM)
		{
			//MessageBox(NULL, "Your team (RED) won!", "Victory", MB_OK);
		}
		else
		{
			//MessageBox(NULL, "The other team (RED) won", "Failure", MB_OK);
		}

		Shutdown();
	}
	if(blueScore > 1)
	{
		if(localClient->team == BLUE_TEAM)
		{
			//MessageBox(NULL, "Your team (BLUE) won!", "Victory", MB_OK);
		}
		else
		{
			//MessageBox(NULL, "The other team (BLUE) won", "Failure", MB_OK);
		}

		Shutdown();
	}
}

void CArmyWar::KillPlayer(int index)
{
	LogString("Player %d died", index);

	clientData *client = GetClientPointer(index);

	if(client == NULL)
		return;

	client->command.origin.x = client->startPos.x;
	client->command.origin.y = client->startPos.y;
}

clientData *CArmyWar::GetClientPointer(int index)
{
	for(clientData *clList = clientList; clList != NULL; clList = clList->next)
	{
		if(clList->index == index)
			return clList;
	}

	return NULL;
}

void CArmyWar::CheckKeys(void)
{
	inputClient.command.key = 0;

	if(keys[VK_ESCAPE])
	{
		Shutdown();

		keys[VK_ESCAPE] = false;
	}

	if(keys[VK_DOWN])
	{
		inputClient.command.key |= KEY_DOWN;
	}

	if(keys[VK_UP])
	{
		inputClient.command.key |= KEY_UP;
	}

	if(keys[VK_LEFT])
	{
		inputClient.command.key |= KEY_LEFT;
	}

	if(keys[VK_RIGHT])
	{
		inputClient.command.key |= KEY_RIGHT;
	}

	if(keys[VK_SPACE])
	{
		inputClient.command.key |= KEY_WEAPON;
	}

	inputClient.command.msec = (int) (frametime * 1000);
}

void CArmyWar::CheckPredictionError(int a)
{
	if(a < 0 && a > COMMAND_HISTORY_SIZE)
		return;

	float errorX =
		localClient->serverFrame.origin.x - localClient->frame[a].predictedOrigin.x;
		
	float errorY =
		localClient->serverFrame.origin.y - localClient->frame[a].predictedOrigin.y;

	// Fix the prediction error
	if( (errorX != 0.0f) || (errorY != 0.0f) )
	{
		localClient->frame[a].predictedOrigin.x = localClient->serverFrame.origin.x;
		localClient->frame[a].predictedOrigin.y = localClient->serverFrame.origin.y;

		localClient->frame[a].vel.x = localClient->serverFrame.vel.x;
		localClient->frame[a].vel.y = localClient->serverFrame.vel.y;

		LogString("Prediction error for frame %d:     %f, %f\n", a,
			errorX, errorY);
	}
}

void CArmyWar::CheckBulletPredictionError(int a)
{
	if(a < 0 && a > COMMAND_HISTORY_SIZE)
		return;

	float errorX = localClient->serverFrame.bullet.origin.x - localClient->frame[a].bullet.predictedOrigin.x;
	float errorY = localClient->serverFrame.bullet.origin.y - localClient->frame[a].bullet.predictedOrigin.y;

	// Fix the prediction error
	if( (errorX != 0.0f) || (errorY != 0.0f) )
	{
		localClient->frame[a].bullet.predictedOrigin.x = localClient->serverFrame.bullet.origin.x;
		localClient->frame[a].bullet.predictedOrigin.y = localClient->serverFrame.bullet.origin.y;

		localClient->frame[a].bullet.vel.x = localClient->serverFrame.bullet.vel.x;
		localClient->frame[a].bullet.vel.y = localClient->serverFrame.bullet.vel.y;

		LogString("Bullet prediction error for frame %d:     %f, %f\n", a,
			errorX, errorY);
	}
}

void CArmyWar::CalculateVelocity(command_t *command, float frametime)
{
	int checkX;
	int checkY;

	float multiplier = 100.0f;

	command->vel.x = 0.0f;
	command->vel.y = 0.0f;

	if(command->key & KEY_UP)
	{
		checkX = (int) (command->origin.x / 32.0f);
		checkY = (int) ((command->origin.y - multiplier * frametime) / 32.0f);

		if(mapdata[checkX][checkY] == false)
			command->vel.y += -multiplier * frametime;
	}

	if(command->key & KEY_DOWN)
	{
		checkX = (int) (command->origin.x / 32.0f);
		checkY = (int) ((command->origin.y + multiplier * frametime) / 32.0f);

		if(mapdata[checkX][checkY] == false)
			command->vel.y += multiplier * frametime;
	}

	if(command->key & KEY_LEFT)
	{
		checkX = (int) ((command->origin.x - multiplier * frametime) / 32.0f);
		checkY = (int) (command->origin.y / 32.0f);

		if(mapdata[checkX][checkY] == false)
			command->vel.x += -multiplier * frametime;
	}

	if(command->key & KEY_RIGHT)
	{
		checkX = (int) ((command->origin.x + multiplier * frametime) / 32.0f);
		checkY = (int) (command->origin.y / 32.0f);

		if(mapdata[checkX][checkY] == false)
			command->vel.x += multiplier * frametime;
	}
}

void CArmyWar::CalculateHeading(command_t *command)
{
	// Left
	if( (command->vel.x > 0.0f) &&
		(command->vel.y == 0.0f) )
	{
		command->heading = EAST;
	}

	// Right
	if( (command->vel.x < 0.0f) &&
		(command->vel.y == 0.0f) )
	{
		command->heading = WEST;
	}

	// Down
	if( (command->vel.y > 0.0f) &&
		(command->vel.x == 0.0f) )
	{
		command->heading = SOUTH;
	}

	// Up
	if( (command->vel.y < 0.0f) &&
		(command->vel.x == 0.0f) )
	{
		command->heading = NORTH;
	}

	// Down-Left
	if( (command->vel.x > 0.0f) &&
		(command->vel.y > 0.0f) )
	{
		command->heading = SOUTHEAST;
	}

	// Up-Left
	if( (command->vel.x > 0.0f) &&
		(command->vel.y < 0.0f) )
	{
		command->heading = NORTHEAST;
	}

	// Down-Right
	if( (command->vel.x < 0.0f) &&
		(command->vel.y > 0.0f) )
	{
		command->heading = SOUTHWEST;
	}

	// Up-Right
	if( (command->vel.x < 0.0f) &&
		(command->vel.y < 0.0f) )
	{
		command->heading = NORTHWEST;
	}
}

void CArmyWar::CalculateBulletVelocity(command_t *command)
{
	command->bullet.shot = true;

	if(command->heading == NORTH)
	{
		command->bullet.vel.x = 0.0f;
		command->bullet.vel.y = -200.0f;
	}
	if(command->heading == SOUTH)
	{
		command->bullet.vel.x = 0.0f;
		command->bullet.vel.y = 200.0f;
	}
	if(command->heading == EAST)
	{
		command->bullet.vel.x = 200.0f;
		command->bullet.vel.y = 0.0f;
	}
	if(command->heading == WEST)
	{
		command->bullet.vel.x = -200.0f;
		command->bullet.vel.y = 0.0f;
	}

	if(command->heading == NORTHEAST)
	{
		command->bullet.vel.x = 200.0f;
		command->bullet.vel.y = -200.0f;
	}
	if(command->heading == NORTHWEST)
	{
		command->bullet.vel.x = -200.0f;
		command->bullet.vel.y = -200.0f;
	}
	if(command->heading == SOUTHEAST)
	{
		command->bullet.vel.x = 200.0f;
		command->bullet.vel.y = 200.0f;
	}
	if(command->heading == SOUTHWEST)
	{
		command->bullet.vel.x = -200.0f;
		command->bullet.vel.y = 200.0f;
	}
}

void CArmyWar::PredictMovement(int prevFrame, int curFrame)
{
	if(!localClient)
		return;

	float frametime = inputClient.frame[curFrame].msec / 1000.0f;

	localClient->frame[curFrame].key = inputClient.frame[curFrame].key;

	//
	// Player ->
	//
	
	// Process commands
	CalculateVelocity(&localClient->frame[curFrame], frametime);
	CalculateHeading(&localClient->frame[curFrame]);

	// Calculate new predicted origin
	localClient->frame[curFrame].predictedOrigin.x =
		localClient->frame[prevFrame].predictedOrigin.x + localClient->frame[curFrame].vel.x;

	localClient->frame[curFrame].predictedOrigin.y =
		localClient->frame[prevFrame].predictedOrigin.y + localClient->frame[curFrame].vel.y;

	// Copy values to "current" values
	localClient->command.predictedOrigin.x	= localClient->frame[curFrame].predictedOrigin.x;
	localClient->command.predictedOrigin.y	= localClient->frame[curFrame].predictedOrigin.y;
	localClient->command.vel.x				= localClient->frame[curFrame].vel.x;
	localClient->command.vel.y				= localClient->frame[curFrame].vel.y;
	localClient->command.heading			= localClient->frame[curFrame].heading;


	//
	// Bullet ->
	//

	// First set the previous values
	localClient->frame[curFrame].bullet.shot = localClient->frame[prevFrame].bullet.shot;
	localClient->frame[curFrame].bullet.vel.x = localClient->frame[prevFrame].bullet.vel.x;
	localClient->frame[curFrame].bullet.vel.y = localClient->frame[prevFrame].bullet.vel.y;
	localClient->frame[curFrame].bullet.lifetime = localClient->frame[prevFrame].bullet.lifetime;

	// The bullet is carried by the player
	if(localClient->frame[curFrame].bullet.shot == false)
	{
		localClient->frame[curFrame].bullet.predictedOrigin.x = localClient->frame[curFrame].predictedOrigin.x;
		localClient->frame[curFrame].bullet.predictedOrigin.y = localClient->frame[curFrame].predictedOrigin.y;
	}
	else
	{
		localClient->frame[curFrame].bullet.lifetime += (int) (frametime * 1000.0f);

		if(localClient->frame[curFrame].bullet.lifetime > 2000)
		{
			localClient->frame[curFrame].bullet.shot = false;
			localClient->frame[curFrame].bullet.lifetime = 0;

			localClient->frame[curFrame].bullet.predictedOrigin.x = localClient->frame[curFrame].predictedOrigin.x;
			localClient->frame[curFrame].bullet.predictedOrigin.y = localClient->frame[curFrame].predictedOrigin.y;
		}
	}

	// Calculate the heading for the bullet only when firing
	if(localClient->frame[curFrame].key & KEY_WEAPON && localClient->frame[curFrame].bullet.shot == false)
	{
		CalculateBulletVelocity(&localClient->frame[curFrame]);
	}

	// If the bullet is in the air (shot), update its origin
	if(localClient->frame[curFrame].bullet.shot)
	{
		localClient->frame[curFrame].bullet.predictedOrigin.x =
			localClient->frame[prevFrame].bullet.predictedOrigin.x +
			localClient->frame[curFrame].bullet.vel.x * frametime;

		localClient->frame[curFrame].bullet.predictedOrigin.y =
			localClient->frame[prevFrame].bullet.predictedOrigin.y +
			localClient->frame[curFrame].bullet.vel.y * frametime;
	}

	// Copy values to "current" values
	localClient->command.bullet.predictedOrigin.x	= localClient->frame[curFrame].bullet.predictedOrigin.x;
	localClient->command.bullet.predictedOrigin.y	= localClient->frame[curFrame].bullet.predictedOrigin.y;
	localClient->command.bullet.vel.x				= localClient->frame[curFrame].bullet.vel.x;
	localClient->command.bullet.vel.y				= localClient->frame[curFrame].bullet.vel.y;
}

void CArmyWar::MoveObjects(void)
{
	if(!localClient)
		return;

	clientData *client = clientList;

	for( ; client != NULL; client = client->next)
	{
		// Remote players
		if(client != localClient)
		{
			CalculateVelocity(&client->command, frametime);
			CalculateHeading(&client->command);

			client->command.origin.x += client->command.vel.x;
			client->command.origin.y += client->command.vel.y;

			client->command.bullet.origin.x += client->serverFrame.bullet.vel.x * frametime;
			client->command.bullet.origin.y += client->serverFrame.bullet.vel.y * frametime;
		}

		// Local player
		else
		{
			Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
			
			client->command.origin.x = client->command.predictedOrigin.x;
			client->command.origin.y = client->command.predictedOrigin.y;

			transVector.x = client->command.origin.x;
            transVector.y = client->command.origin.y;
			
			//myCharacter->getSceneNode()->setPosition(transVector);
			//client->character->getSceneNode()->setPosition(transVector);

			client->command.bullet.origin.x = client->command.bullet.predictedOrigin.x;
			client->command.bullet.origin.y = client->command.bullet.predictedOrigin.y;
		}
	}
}

void CArmyWar::StartConnection(int ind)
{
//	LogString("StartConnection");

	//gameIndex = ind;
char serverIP[32] = "127.0.0.1";
//char serverIP[32] = "192.168.1.104";

	int ret = networkClient->Initialise("", serverIP, 30004);

	if(ret == DREAMSOCK_CLIENT_ERROR)
	{
		char text[64];
		sprintf(text, "Could not open client socket");

		MessageBox(NULL, text, "Error", MB_OK);
	}

	Connect();

}

void CArmyWar::Connect(void)
{
	if(init)
	{
		LogString("ArmyWar already initialised");
		return;
	}

	LogString("CArmyWar::Connect");

	init = true;

	networkClient->SendConnect("myname");
}

void CArmyWar::Disconnect(void)
{
	if(!init)
		return;

	LogString("CArmyWar::Disconnect");

	init = false;
	localClient = NULL;
	memset(&inputClient, 0, sizeof(clientData));

	networkClient->SendDisconnect();
}

void CArmyWar::ReadMoveCommand(DreamMessage *mes, clientData *client)
{
	// Key
	client->serverFrame.key				= mes->ReadByte();

	// Heading
	client->serverFrame.heading			= mes->ReadShort();

	// Origin
	client->serverFrame.origin.x		= mes->ReadFloat();
	client->serverFrame.origin.y		= mes->ReadFloat();
	client->serverFrame.vel.x			= mes->ReadFloat();
	client->serverFrame.vel.y			= mes->ReadFloat();

	client->serverFrame.bullet.origin.x	= mes->ReadFloat();
	client->serverFrame.bullet.origin.y	= mes->ReadFloat();
	client->serverFrame.bullet.vel.x	= mes->ReadFloat();
	client->serverFrame.bullet.vel.y	= mes->ReadFloat();
	client->serverFrame.bullet.lifetime	= mes->ReadShort();
	client->serverFrame.bullet.shot		= mes->ReadByte();

	int playerWithFlagIndex = mes->ReadShort();

	if(playerWithFlagIndex != -1)
	{
		playerWithFlag = GetClientPointer(playerWithFlagIndex);
	}

	flagX = mes->ReadFloat();
	flagY = mes->ReadFloat();

	redScore = mes->ReadByte();
	blueScore = mes->ReadByte();

	// Read time to run command
	client->serverFrame.msec = mes->ReadByte();

	memcpy(&client->command, &client->serverFrame, sizeof(command_t));

	// Fill the history array with the position we got
	for(int f = 0; f < COMMAND_HISTORY_SIZE; f++)
	{
		client->frame[f].predictedOrigin.x = client->command.origin.x;
		client->frame[f].predictedOrigin.y = client->command.origin.y;
		client->frame[f].bullet.predictedOrigin.x = client->command.bullet.origin.x;
		client->frame[f].bullet.predictedOrigin.y = client->command.bullet.origin.y;
	}
}

void CArmyWar::ReadDeltaMoveCommand(DreamMessage *mes, clientData *client)
{
	int processedFrame;
	int flags = 0;

	// Flags
	flags = mes->ReadByte();

	// Key
	if(flags & CMD_KEY)
	{
		client->serverFrame.key = mes->ReadByte();

		client->command.key = client->serverFrame.key;
		LogString("Client %d: Read key %d", client->index, client->command.key);
	}

	if(flags & CMD_ORIGIN || flags & CMD_BULLET)
	{
		processedFrame = mes->ReadByte();
	}

	// Origin
	if(flags & CMD_ORIGIN)
	{
		client->serverFrame.origin.x = mes->ReadFloat();
		client->serverFrame.origin.y = mes->ReadFloat();

		client->serverFrame.vel.x = mes->ReadFloat();
		client->serverFrame.vel.y = mes->ReadFloat();

		if(client == localClient)
		{
			CheckPredictionError(processedFrame);
		}
		else
		{
			client->command.origin.x = client->serverFrame.origin.x;
			client->command.origin.y = client->serverFrame.origin.y;
		}
	}

	if(flags & CMD_BULLET)
	{
		client->serverFrame.bullet.origin.x = mes->ReadFloat();
		client->serverFrame.bullet.origin.y = mes->ReadFloat();
		client->serverFrame.bullet.vel.x = mes->ReadFloat();
		client->serverFrame.bullet.vel.y = mes->ReadFloat();
		client->serverFrame.bullet.shot = mes->ReadByte();

		client->command.bullet.shot = client->serverFrame.bullet.shot;

		if(client == localClient)
		{
			CheckBulletPredictionError(processedFrame);
		}
		else
		{
			client->command.bullet.origin.x = client->serverFrame.bullet.origin.x;
			client->command.bullet.origin.y = client->serverFrame.bullet.origin.y;
		}
	}

	// Flag & points
	if(flags & CMD_FLAG)
	{
		int playerWithFlagIndex = mes->ReadShort();

		if(playerWithFlagIndex != 0)
		{
			LogString("FLAG playerWithFlagIndex %d", playerWithFlagIndex);
			playerWithFlag = GetClientPointer(playerWithFlagIndex);
		}
		else
		{
			playerWithFlag = NULL;
		}

		flagX = mes->ReadFloat();
		flagY = mes->ReadFloat();

		redScore = mes->ReadByte();
		blueScore = mes->ReadByte();

		CheckVictory();
	}

	// Someone died
	if(flags & CMD_KILL)
	{
		int died = mes->ReadByte();

		if(died)
			KillPlayer(client->index);
	}

	// Read time to run command
	client->command.msec = mes->ReadByte();
}

void CArmyWar::BuildDeltaMoveCommand(DreamMessage *mes, clientData *theClient)
{
	int flags = 0;
	int last = (networkClient->GetOutgoingSequence() - 1) & (COMMAND_HISTORY_SIZE-1);

	// Check what needs to be updated
	if(theClient->frame[last].key != theClient->command.key)
		flags |= CMD_KEY;

	// Add to the message
	// Flags
	mes->WriteByte(flags);

	// Key
	if(flags & CMD_KEY)
	{
		mes->WriteByte(theClient->command.key);
	}

	mes->WriteByte(theClient->command.msec);
}

void CArmyWar::RunNetwork(int msec)
{
	static int time = 0;
	time += msec;

	// Framerate is too high
	if(time < (1000 / 60))
		return;

	frametime = time / 1000.0f;
	time = 0;

	// Read packets from server, and send new commands
	ReadPackets();
	SendCommand();

	int ack = networkClient->GetIncomingAcknowledged();
	int current = networkClient->GetOutgoingSequence();

	// Check that we haven't gone too far
	if(current - ack > COMMAND_HISTORY_SIZE)
		return;

	// Predict the frames that we are waiting from the server
	for(int a = ack + 1; a < current; a++)
	{
		int prevframe = (a-1) & (COMMAND_HISTORY_SIZE-1);
		int frame = a & (COMMAND_HISTORY_SIZE-1);

		PredictMovement(prevframe, frame);
	}

	MoveObjects();
}

/*************************/
void CArmyWar::RemoveClient(int ind)
{
	clientData *list = clientList;
	clientData *prev = NULL;
	clientData *next = NULL;

	// Look for correct client and update list
	for( ; list != NULL; list = list->next)
	{
		if(list->index == ind)
		{
			if(prev != NULL)
			{
				prev->next = list->next;
			}

			break;
		}

		prev = list;
	}

	// First entry
	if(list == clientList)
	{
		if(list)
		{
			next = list->next;
			free(list);
		}

		list = NULL;
		clientList = next;
	}

	// Other
	else
	{
		if(list)
		{
			next = list->next;
			free(list);
		}

		list = next;
	}

	clients--;

//	Lobby.RefreshJoinedPlayersList();
}

void CArmyWar::RemoveClients(void)
{
	clientData *list = clientList;
	clientData *next;

	while(list != NULL)
	{
		if(list)
		{
			next = list->next;
			free(list);
		}

		list = next;
	}

	clientList = NULL;
	clients = 0;
}

void CArmyWar::SendCommand(void)
{
	if(networkClient->GetConnectionState() != DREAMSOCK_CONNECTED)
		return;

	DreamMessage message;
	char data[1400];

	int i = networkClient->GetOutgoingSequence() & (COMMAND_HISTORY_SIZE-1);

	message.Init(data, sizeof(data));
	message.WriteByte(USER_MES_FRAME);						// type
	message.AddSequences(networkClient);					// sequences

	// Build delta-compressed move command
	BuildDeltaMoveCommand(&message, &inputClient);

	// Send the packet
	networkClient->SendPacket(&message);

	// Store the command to the input client's history
	memcpy(&inputClient.frame[i], &inputClient.command, sizeof(command_t));

	clientData *clList = clientList;

	// Store the commands to the clients' history
	for( ; clList != NULL; clList = clList->next)
	{
		memcpy(&clList->frame[i], &clList->command, sizeof(command_t));
	}
}

void CArmyWar::SendStartGame(void)
{
	char data[1400];
	DreamMessage message;
	message.Init(data, sizeof(data));

	message.WriteByte(USER_MES_STARTGAME);
	message.AddSequences(networkClient);

	networkClient->SendPacket(&message);
}

void CArmyWar::SendRequestNonDeltaFrame(void)
{
	char data[1400];
	DreamMessage message;
	message.Init(data, sizeof(data));

	message.WriteByte(USER_MES_NONDELTAFRAME);
	message.AddSequences(networkClient);

	networkClient->SendPacket(&message);
}

