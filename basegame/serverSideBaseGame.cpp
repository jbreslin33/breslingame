#include "serverSideBaseGame.h"

#include "../client/ClientSideClient.h"
#include "../game/ClientSideGame.h"
#include "../network/clientSideNetwork.h"
#include "../shape/clientSideShape.h"
#include "../game/serverSideGame.h"

#include "../dreamsock/DreamSock.h"
#include "../dreamsock/DreamServer.h"

bool keys[256];

ServerSideBaseGame::ServerSideBaseGame()
{
	//mClientSideNetwork = NULL;
	//mClientSideGame    = NULL;
}

ServerSideBaseGame::~ServerSideBaseGame()
{

}

void ServerSideBaseGame::createPlayer(int index)
{
}

void ServerSideBaseGame::createScene(void)
{
}

bool ServerSideBaseGame::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
    return true;
}

bool ServerSideBaseGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
return true;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

LRESULT CALLBACK WindowProc(HWND WindowhWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	// Process Messages
	switch(Message)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(WindowhWnd, Message, wParam, lParam);
}



    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	#define UNIX
    int main(int argc, char *argv[])
#endif
    {
ServerSideGame* game;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	WNDCLASS WinClass;

	WinClass.style			= 0;
	WinClass.lpfnWndProc	= WindowProc;
	WinClass.cbClsExtra		= 0;
	WinClass.cbWndExtra		= 0;
	WinClass.hInstance		= hInst;
	WinClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	WinClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WinClass.hbrBackground	= (HBRUSH) (COLOR_MENU);
	WinClass.lpszMenuName	= 0;
	WinClass.lpszClassName	= "WINCLASS1";

	if(!RegisterClass(&WinClass))
		return 0;

	HWND hwnd = CreateWindow(WinClass.lpszClassName,
						"dreamSock server",
						WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						320,
						240,
						320, 240,
						NULL,
						NULL,
						hInst,
						NULL);

	ShowWindow(hwnd, SW_HIDE);

	StartLogConsole();


	game = new ServerSideGame();

	if(game->InitNetwork() != 0)
	{
		LogString("Could not create game server");
	}

	MSG WinMsg;
	bool done = false;
	int time, oldTime, newTime;

	// first peek the message without removing it
	PeekMessage(&WinMsg, hwnd, 0, 0, PM_NOREMOVE);

	oldTime = game->networkServer->dreamSock->dreamSock_GetCurrentSystemTime();

	try
	{
		while(!done)
		{
			while (PeekMessage(&WinMsg, NULL, 0, 0, PM_NOREMOVE))
			{
				if(!GetMessage(&WinMsg, NULL, 0, 0))
				{
					game->networkServer->dreamSock->dreamSock_Shutdown();

					done = true;
				}

				TranslateMessage(&WinMsg);
   				DispatchMessage(&WinMsg);
			}

			do
			{
				newTime = game->networkServer->dreamSock->dreamSock_GetCurrentSystemTime();
				time = newTime - oldTime;
			} while (time < 1);
			
			game->Frame(time);
			

			oldTime = newTime;
		}
	}
	catch(...)
	{
		LogString("Unknown Exception caught in main loop");

		game->networkServer->dreamSock->dreamSock_Shutdown();

		MessageBox(NULL, "Unknown Exception caught in main loop", "Error", MB_OK | MB_TASKMODAL);

		return -1;
	}

	return WinMsg.wParam;

#else
	//mBaseGame->mClientSideNetwork->StartConnection(argv[1]);
	LogString("Welcome to Army War Server v2.0");
	LogString("-------------------------------\n");

	// Ignore the SIGPIPE signal, so the program does not terminate if the
	// pipe gets broken
	signal(SIGPIPE, SIG_IGN);
	
	LogString("Init successful");

	game = new ServerSideGame();
	game->InitNetwork();
	
	int time, oldTime, newTime;

	oldTime = game->networkServer->dreamSock->dreamSock_GetCurrentSystemTime();

	// App main loop
	try
	{
		// Keep server alive (wait for keypress to kill it)
		while(1)
		{
			do
			{
				newTime = game->networkServer->dreamSock->dreamSock_GetCurrentSystemTime();
				time = newTime - oldTime;
			} while (time < 1);

			game->Frame(time);
			oldTime = newTime;
		}
	}
	catch(...)
	{
		game->networkServer->dreamSock->dreamSock_Shutdown();

		LogString("Unknown Exception caught in main loop");

		return -1;
	}

	LogString("Shutting down everything");

	game->networkServer->dreamSock->dreamSock_Shutdown();

	return 0;

#endif

        try {
          //  mBaseGame->go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            //MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            //std::cerr << "An exception has occured: " <<
              //  e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
