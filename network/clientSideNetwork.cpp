#include "clientSideNetwork.h"

#include "../basegame/baseGame.h"

#include "../dreamsock/DreamMessage.h"
#include "../dreamsock/DreamClient.h"

ClientSideNetwork::ClientSideNetwork(BaseGame* baseGame)
{
	mBaseGame     = baseGame;
	networkClient = mBaseGame->networkClient;
}

ClientSideNetwork::~ClientSideNetwork()
{
}



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

			mBaseGame->AddClient(local, ind, name);
			break;

		case DREAMSOCK_MES_REMOVECLIENT:
			ind = mes.ReadByte();

			LogString("Got removeclient %d message", ind);

			mBaseGame->RemoveClient(ind);

			break;

		case USER_MES_FRAME:
			// Skip sequences
			mes.ReadShort();
			mes.ReadShort();

			for(clList = mBaseGame->clientList; clList != NULL; clList = clList->next)
			{
//				LogString("Reading DELTAFRAME for client %d", clList->index);
				mBaseGame->ReadDeltaMoveCommand(&mes, clList);
			}

			break;

		case USER_MES_NONDELTAFRAME:
			// Skip sequences
			mes.ReadShort();
			mes.ReadShort();

			clList = mBaseGame->clientList;

			for(clList = mBaseGame->clientList; clList != NULL; clList = clList->next)
			{
				LogString("Reading NONDELTAFRAME for client %d", clList->index);
				mBaseGame->ReadMoveCommand(&mes, clList);
			}

			break;

		case USER_MES_SERVEREXIT:
			//MessageBox(NULL, "Server disconnected", "Info", MB_OK);
			mBaseGame->Disconnect();
			break;

		}
	}
}

void ClientSideNetwork::SendCommand(void)
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
	mBaseGame->BuildDeltaMoveCommand(&message, &mBaseGame->inputClient);

	// Send the packet
	networkClient->SendPacket(&message);

	// Store the command to the input client's history
	memcpy(&mBaseGame->inputClient.frame[i], &mBaseGame->inputClient.command, sizeof(ClientSideCommand));

	ClientSideClient *clList = mBaseGame->clientList;

	// Store the commands to the clients' history
	for( ; clList != NULL; clList = clList->next)
	{
		memcpy(&clList->frame[i], &clList->command, sizeof(ClientSideCommand));
	}
}

void ClientSideNetwork::SendRequestNonDeltaFrame(void)
{
	char data[1400];
	DreamMessage message;
	message.Init(data, sizeof(data));

	message.WriteByte(USER_MES_NONDELTAFRAME);
	message.AddSequences(networkClient);

	networkClient->SendPacket(&message);
}


