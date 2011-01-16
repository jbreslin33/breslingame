#ifndef __TALKER_h_
#define __TALKER_h_

#define SERVERPORT "38387"// the port users will be connecting to
#define MAXBUFFER = 512;
#include <string>

class Game;

class Talker
{

public:
    Talker(Game* game);
    virtual ~Talker(void);

                        //who          , mess
	void sendMessage(Client* client, char[MAXBUFFER]);
	void sendMessage(Server* server, char[MAXBUFFER]);

	void sendMessageToServer(char p1[100], char p2[100]);
	void sendMessageToServer(char p1[100], char p2[100], char p3[100]);
	void sendMessageToServer(char p1[100], char p2[100], char p3[100], char p4[100]);

	int sendMessageToServer (char mess[100] );
	void sendMessageToClients(char newMessageToClients[100]);

	char* getMessage () { return mMessage;  }

protected:

Game* mGame;
char* mMessage;
//char* mServerIP;

};

#endif
