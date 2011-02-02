/******************************************/
/* MMOG programmer's guide                */
/* Tutorial game client                   */
/* Programming:						      */
/* Teijo Hakala						      */
/******************************************/

#include "clientSideNetwork.h"

//char serverIP[32] = "127.0.0.1";
char serverIP[32] = "192.168.2.112";

#include "../game/ClientSideGame.h"
#include "../dreamsock/DreamClient.h"
#include "../dreamsock/DreamSock.h"
#include "clientSideNetwork.h"
#include "../basegame/baseGame.h"

ClientSideNetwork::ClientSideNetwork(ClientSideGame* clientSideGame)
{
	mClientSideGame = clientSideGame;
}

ClientSideNetwork::~ClientSideNetwork()
{
}


//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::StartConnection()
{
//	LogString("StartConnection");

	//gameIndex = ind;
//networkClient	= new DreamClient();
	int ret = mClientSideGame->networkClient->Initialise("", serverIP, 30004);

	if(ret == DREAMSOCK_CLIENT_ERROR)
	{
		char text[64];
		sprintf(text, "Could not open client socket");

		//MessageBox(NULL, text, "Error", MB_OK);
	}

	Connect();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::ReadPackets(void)
{
	char data[1400];
	struct sockaddr address;

	ClientSideClient *clList;

	int type;
	int ind;
	int local;
	int ret;

	char name[50];

	DreamMessage mes;
	mes.Init(data, sizeof(data));

	while(ret = mClientSideGame->networkClient->GetPacket(mes.data, &address))
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

			mClientSideGame->AddClient(local, ind, name);
			break;

		case DREAMSOCK_MES_REMOVECLIENT:
			ind = mes.ReadByte();

			LogString("Got removeclient %d message", ind);

			mClientSideGame->RemoveClient(ind);

			break;

		case USER_MES_FRAME:
			// Skip sequences
			mes.ReadShort();
			mes.ReadShort();

			for(clList = mClientSideGame->clientList; clList != NULL; clList = clList->next)
			{
//				LogString("Reading DELTAFRAME for client %d", clList->index);
				ReadDeltaMoveCommand(&mes, clList);
			}

			break;

		case USER_MES_NONDELTAFRAME:
			// Skip sequences
			mes.ReadShort();
			mes.ReadShort();

			clList = mClientSideGame->clientList;

			for(clList = mClientSideGame->clientList; clList != NULL; clList = clList->next)
			{
				LogString("Reading NONDELTAFRAME for client %d", clList->index);
				ReadMoveCommand(&mes, clList);
			}

			break;

		case USER_MES_SERVEREXIT:
			//MessageBox(NULL, "Server disconnected", "Info", MB_OK);
			Disconnect();
			break;

		}
	}
}


//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::SendCommand(void)
{
	if(mClientSideGame->networkClient->GetConnectionState() != DREAMSOCK_CONNECTED)
		return;

	DreamMessage message;
	char data[1400];

	int i = mClientSideGame->networkClient->GetOutgoingSequence() & (COMMAND_HISTORY_SIZE-1);

	message.Init(data, sizeof(data));
	message.WriteByte(USER_MES_FRAME);						// type
	message.AddSequences(mClientSideGame->networkClient);					// sequences

	// Build delta-compressed move command
	BuildDeltaMoveCommand(&message, &mClientSideGame->inputClient);

	// Send the packet
	mClientSideGame->networkClient->SendPacket(&message);

	// Store the command to the input client's history
	memcpy(&mClientSideGame->inputClient.frame[i], &mClientSideGame->inputClient.command, sizeof(ClientSideCommand));

	ClientSideClient *clList = mClientSideGame->clientList;

	// Store the commands to the clients' history
	for( ; clList != NULL; clList = clList->next)
	{
		memcpy(&clList->frame[i], &clList->command, sizeof(ClientSideCommand));
	}
}


//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::SendRequestNonDeltaFrame(void)
{
	char data[1400];
	DreamMessage message;
	message.Init(data, sizeof(data));

	message.WriteByte(USER_MES_NONDELTAFRAME);
	message.AddSequences(mClientSideGame->networkClient);

	mClientSideGame->networkClient->SendPacket(&message);
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::Connect(void)
{
	if(mClientSideGame->init)
	{
		LogString("ArmyWar already initialised");
		return;
	}

	LogString("ClientSideNetwork::Connect");

	mClientSideGame->init = true;

	mClientSideGame->networkClient->SendConnect("myname");
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::Disconnect(void)
{
	if(!mClientSideGame->init)
		return;

	LogString("ClientSideNetwork::Disconnect");

	mClientSideGame->init = false;
	mClientSideGame->localClient = NULL;
	memset(&mClientSideGame->inputClient, 0, sizeof(ClientSideClient));

	mClientSideGame->networkClient->SendDisconnect();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::ReadMoveCommand(DreamMessage *mes, ClientSideClient *client)
{
	// Key
	client->serverFrame.key				= mes->ReadByte();

	// Heading
	//client->serverFrame.heading			= mes->ReadShort();

	// Origin
	client->serverFrame.origin.x		= mes->ReadFloat();
	client->serverFrame.origin.y		= mes->ReadFloat();
	client->serverFrame.vel.x			= mes->ReadFloat();
	client->serverFrame.vel.y			= mes->ReadFloat();

	// Read time to run command
	client->serverFrame.msec = mes->ReadByte();

	memcpy(&client->command, &client->serverFrame, sizeof(ClientSideCommand));

	// Fill the history array with the position we got
	for(int f = 0; f < COMMAND_HISTORY_SIZE; f++)
	{
		client->frame[f].predictedOrigin.x = client->command.origin.x;
		client->frame[f].predictedOrigin.y = client->command.origin.y;
	}
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::ReadDeltaMoveCommand(DreamMessage *mes, ClientSideClient *client)
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

	if(flags & CMD_ORIGIN)
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

		if(client == mClientSideGame->localClient)
		{
			mClientSideGame->CheckPredictionError(processedFrame);
		}

		else
		{
			client->command.origin.x = client->serverFrame.origin.x;
			client->command.origin.y = client->serverFrame.origin.y;

			client->command.vel.x = client->serverFrame.vel.x;
			client->command.vel.y = client->serverFrame.vel.y;
		}
	}

	// Read time to run command
	client->command.msec = mes->ReadByte();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::BuildDeltaMoveCommand(DreamMessage *mes, ClientSideClient *theClient)
{
	int flags = 0;
	int last = (mClientSideGame->networkClient->GetOutgoingSequence() - 1) & (COMMAND_HISTORY_SIZE-1);

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

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideNetwork::RunNetwork(int msec)
{
	static int time = 0;
	time += msec;

	// Framerate is too high
	if(time < (1000 / 60))
		return;

	mClientSideGame->frametime = time / 1000.0f;
	time = 0;

	// Read packets from server, and send new commands
	ReadPackets();
	SendCommand();

	int ack = mClientSideGame->networkClient->GetIncomingAcknowledged();
	int current = mClientSideGame->networkClient->GetOutgoingSequence();

	// Check that we haven't gone too far
	if(current - ack > COMMAND_HISTORY_SIZE)
		return;

	// Predict the frames that we are waiting from the server
	for(int a = ack + 1; a < current; a++)
	{
		int prevframe = (a-1) & (COMMAND_HISTORY_SIZE-1);
		int frame = a & (COMMAND_HISTORY_SIZE-1);

		mClientSideGame->PredictMovement(prevframe, frame);
	}

	mClientSideGame->MoveObjects();
}
