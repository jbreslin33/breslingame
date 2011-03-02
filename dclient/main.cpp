#include "networkedGame.h"

#include <iostream>
#include <string>
using namespace std;

NetworkedGame* game;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		char *ip;
		char strIP[15];
		ip = strIP;
		if (strCmdLine[0] == '1')
		{
			game = new NetworkedGame;
			int i = 0;
			while(strCmdLine[i] != 'E')
			{
				ip[i] = strCmdLine[i + 2];
				i++;
			}
		}
		
#else

#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		 game->StartConnection(ip);
#else
		 game->StartConnection(ip);
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		StartLogConsole();
#endif


        try {
            game->go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif