#ifndef __TALKER_h_
#define __TALKER_h_

#define SERVERPORT "4950"	// the port users will be connecting to

class Game;

class Talker
{

public:
    Talker(Game* game);
    virtual ~Talker(void);

    int sendMessageToServer (char newMessageToServer[100] );
//    void setServerIP(char* ip) { mServerIP = ip; }
    void sendMessageToClients(char newMessageToClients[100]);

    char* getMessage () { return mMessage;  }
//    char* getServerIP() { return mServerIP; }

protected:

Game* mGame;
char* mMessage;
//char* mServerIP;

};

#endif
