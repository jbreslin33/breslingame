/******************************************/
/* MMOG programmer's guide                */
/* Tutorial game server                   */
/* Programming:						      */
/* Teijo Hakala						      */
/******************************************/
#include "server.h"
#include "../dreamsock/DreamServer.h"
#include "../dreamsock/DreamSock.h"
#include "../dreamsock/DreamMessage.h"

#include <math.h>

#ifdef WIN32
#include <windows.h>
#include <mmsystem.h>
#include <assert.h>
#endif

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void CArmyWarServer::ReadPackets(void)
{
	char data[1400];

	int type;
	int ret;

	struct sockaddr address;

	clientData *clList;

	DreamMessage mes;
	mes.Init(data, sizeof(data));

	// Get the packet from the socket
	try
	{
		while(ret = networkServer->GetPacket(mes.data, &address))
		{
			mes.SetSize(ret);
			mes.BeginReading();

			type = mes.ReadByte();

			// Check the type of the message
			switch(type)
			{
			case DREAMSOCK_MES_CONNECT:
				AddClient();
				break;

			case DREAMSOCK_MES_DISCONNECT:
				RemoveClient(&address);
				break;

			case USER_MES_FRAME:
//			LogString("Got frame (size: %d bytes)", ret);

				// Skip sequences
				mes.ReadShort();
				mes.ReadShort();

				// Find the correct client by comparing addresses
				clList = clientList;

				for( ; clList != NULL; clList = clList->next)
				{
					if(memcmp(&clList->address, &address, sizeof(address)) == 0)
					{
						ReadDeltaMoveCommand(&mes, clList);
						MovePlayer(clList);

						break;
					}
				}

				break;

			case USER_MES_NONDELTAFRAME:
				clList = clientList;
				clientData *dataClient;

				for( ; clList != NULL; clList = clList->next)
				{
					clList->netClient->message.Init(clList->netClient->message.outgoingData,
						sizeof(clList->netClient->message.outgoingData));

					clList->netClient->message.WriteByte(USER_MES_NONDELTAFRAME);
					clList->netClient->message.WriteShort(clList->netClient->GetOutgoingSequence());
					clList->netClient->message.WriteShort(clList->netClient->GetIncomingSequence());

					for(dataClient = clientList; dataClient != NULL; dataClient = dataClient->next)
					{
						BuildMoveCommand(&clList->netClient->message, dataClient);
					}

					clList->netClient->SendPacket();
				}

				break;

			case USER_MES_STARTGAME:
				// Skip sequences
				mes.ReadShort();
				mes.ReadShort();

				// Send to everybody
				for(clList = clientList; clList != NULL; clList = clList->next)
				{
					clList->netClient->message.Init(clList->netClient->message.outgoingData,
						sizeof(clList->netClient->message.outgoingData));

					clList->netClient->message.WriteByte(USER_MES_MAPDATA);			// type
					clList->netClient->message.AddSequences(clList->netClient);		// sequences

					for(int i = 0; i < 100; i++)
					{
						for(int j = 0; j < 100; j++)
						{
							if(mapdata[i][j] == true)
							{
								clList->netClient->message.WriteByte(i);
								clList->netClient->message.WriteByte(j);
							}
						}
					}
				}

				networkServer->SendPackets();

				// Send to everybody
				for(clList = clientList; clList != NULL; clList = clList->next)
				{
					clList->netClient->message.Init(clList->netClient->message.outgoingData,
						sizeof(clList->netClient->message.outgoingData));

					clList->netClient->message.WriteByte(USER_MES_STARTGAME);		// type
					clList->netClient->message.AddSequences(clList->netClient);		// sequences
				}

				networkServer->SendPackets();

				break;
			}
		}
	}
	catch(...)
	{
		LogString("Unknown Exception caught in Lobby ReadPackets loop");

#ifdef WIN32
		MessageBox(NULL, "Unknown Exception caught in Lobby ReadPackets loop", "Error", MB_OK | MB_TASKMODAL);
#endif
	}
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void CArmyWarServer::SendCommand(void)
{
	clientData *toClient;
	clientData *dataClient;

	// Fill messages
	for(toClient = clientList; toClient != NULL; toClient = toClient->next)
	{
		toClient->netClient->message.Init(toClient->netClient->message.outgoingData,
			sizeof(toClient->netClient->message.outgoingData));

		toClient->netClient->message.WriteByte(USER_MES_FRAME);			// type
		toClient->netClient->message.AddSequences(toClient->netClient);	// sequences

		for(dataClient = clientList; dataClient != NULL; dataClient = dataClient->next)
		{
			BuildDeltaMoveCommand(&toClient->netClient->message, dataClient);
		}
	}

	// Send messages to all clients
	networkServer->SendPackets();

	// Store the sent command in history
	for(toClient = clientList; toClient != NULL; toClient = toClient->next)
	{
		int i = (toClient->netClient->GetOutgoingSequence() - 1) & (COMMAND_HISTORY_SIZE-1);

		memcpy(&toClient->frame[i], &toClient->command, sizeof(command_t));
	}
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void CArmyWarServer::SendExitNotification(void)
{
	clientData *toClient = clientList;

	for( ; toClient != NULL; toClient = toClient->next)
	{
		toClient->netClient->message.Init(toClient->netClient->message.outgoingData,
			sizeof(toClient->netClient->message.outgoingData));

		toClient->netClient->message.WriteByte(USER_MES_SERVEREXIT);	// type
		toClient->netClient->message.AddSequences(toClient->netClient);	// sequences
	}

	networkServer->SendPackets();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void CArmyWarServer::ReadDeltaMoveCommand(DreamMessage *mes, clientData *client)
{
	int flags = 0;

	// Flags
	flags = mes->ReadByte();

	// Key
	if(flags & CMD_KEY)
	{
		client->command.key = mes->ReadByte();

		LogString("Client %d: read CMD_KEY (%d)", client->netClient->GetIndex(), client->command.key);
	}

	// Read time to run command
	client->command.msec = mes->ReadByte();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void CArmyWarServer::BuildMoveCommand(DreamMessage *mes, clientData *client)
{
	// Add to the message
	// Key
	mes->WriteByte(client->command.key);

	// Heading
	mes->WriteShort(client->command.heading);

	// Origin
	mes->WriteFloat(client->command.origin.x);
	mes->WriteFloat(client->command.origin.y);
	mes->WriteFloat(client->command.vel.x);
	mes->WriteFloat(client->command.vel.y);

	mes->WriteFloat(client->command.bullet.origin.x);
	mes->WriteFloat(client->command.bullet.origin.y);
	mes->WriteFloat(client->command.bullet.vel.x);
	mes->WriteFloat(client->command.bullet.vel.y);
	mes->WriteShort(client->command.bullet.lifetime);
	mes->WriteByte(client->command.bullet.shot);

	// Flag & points
	if(playerWithFlag)
		mes->WriteShort(playerWithFlag->netClient->GetIndex());
	else
		mes->WriteShort(-1);

	mes->WriteFloat(flagX);
	mes->WriteFloat(flagY);

	mes->WriteByte(redScore);
	mes->WriteByte(blueScore);

	mes->WriteByte(client->command.msec);
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void CArmyWarServer::BuildDeltaMoveCommand(DreamMessage *mes, clientData *client)
{
	int flags = 0;

	int last = (client->netClient->GetOutgoingSequence() - 1) & (COMMAND_HISTORY_SIZE-1);

	// Check what needs to be updated
	if(client->frame[last].key != client->command.key)
	{
		flags |= CMD_KEY;
	}

	if(client->frame[last].origin.x != client->command.origin.x ||
		client->frame[last].origin.y != client->command.origin.y)
	{
		flags |= CMD_ORIGIN;
	}

	if(client->command.bullet.shot)
	{
		if(client->frame[last].bullet.origin.x != client->command.bullet.origin.x ||
		client->frame[last].bullet.origin.y != client->command.bullet.origin.y)
		{
			flags |= CMD_BULLET;
		}
	}

	if(client->frame[last].bullet.shot != client->command.bullet.shot)
	{
		flags |= CMD_BULLET;
	}

	if(updateFlag == true)
	{
		flags |= CMD_FLAG;
	}

	if(updateKill == true)
	{
		flags |= CMD_KILL;
	}


	// Add to the message
	// Flags
	mes->WriteByte(flags);

	// Key
	if(flags & CMD_KEY)
	{
		mes->WriteByte(client->command.key);
	}

	if(flags & CMD_ORIGIN || flags & CMD_BULLET)
	{
		mes->WriteByte(client->processedFrame & (COMMAND_HISTORY_SIZE-1));
	}

	// Origin
	if(flags & CMD_ORIGIN)
	{
		mes->WriteFloat(client->command.origin.x);
		mes->WriteFloat(client->command.origin.y);

		mes->WriteFloat(client->command.vel.x);
		mes->WriteFloat(client->command.vel.y);
	}

	// Origin
	if(flags & CMD_BULLET)
	{
		mes->WriteFloat(client->command.bullet.origin.x);
		mes->WriteFloat(client->command.bullet.origin.y);

		mes->WriteFloat(client->command.bullet.vel.x);
		mes->WriteFloat(client->command.bullet.vel.y);

		mes->WriteByte(client->command.bullet.shot);
	}

	// Flag & points
	if(flags & CMD_FLAG)
	{
		if(playerWithFlag)
			mes->WriteShort(playerWithFlag->netClient->GetIndex());
		else
			mes->WriteShort(0);

		mes->WriteFloat(flagX);
		mes->WriteFloat(flagY);

		mes->WriteByte(redScore);
		mes->WriteByte(blueScore);
	}

	// Someone died
	if(flags & CMD_KILL)
	{
		mes->WriteByte(client->diedThisFrame);
	}

	mes->WriteByte(client->command.msec);
}
