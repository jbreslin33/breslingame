#ifndef __TALKER_h_
#define __TALKER_h_

#define SERVERPORT "4950"	// the port users will be connecting to

#include <string>

class Game;

class Talker
{

public:
    Talker(Game* game);
    virtual ~Talker(void);

	void translateMessage(std::string p1);
	void translateMessage(std::string p1, std::string p2);
	void translateMessage(std::string p1, std::string p2, std::string p3);
	void translateMessage(std::string p1, std::string p2, std::string p3, std::string p4);

	int sendMessageToServer (char* newMessageToServer );
	void sendMessageToClients(char newMessageToClients[100]);

	char* getMessage () { return mMessage;  }

protected:

Game* mGame;
char* mMessage;
//char* mServerIP;

};

#endif
