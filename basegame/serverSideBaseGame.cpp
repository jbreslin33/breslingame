#include "serverSideBaseGame.h"

#include "Ogre.h"

using namespace Ogre;

//#include "../network/clientSideNetwork.h"
#include "../game/serverSideGame.h"
#include "../dreamsock/DreamSock.h"
#include "../dreamsock/DreamServer.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
ServerSideBaseGame::ServerSideBaseGame(HWND hwnd)
#else
ServerSideBaseGame::ServerSideBaseGame()
#endif
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	StartLogConsole();

	mServerSideGame = new ServerSideGame();

	if(mServerSideGame->InitNetwork() != 0)
	{
		LogString("Could not create game server");
	}

	MSG WinMsg;
	bool done = false;
	int time, oldTime, newTime;

	// first peek the message without removing it
	PeekMessage(&WinMsg, hwnd, 0, 0, PM_NOREMOVE);

	oldTime = mServerSideGame->networkServer->dreamSock->dreamSock_GetCurrentSystemTime();

	try
	{
		while(!done)
		{
			while (PeekMessage(&WinMsg, NULL, 0, 0, PM_NOREMOVE))
			{
				if(!GetMessage(&WinMsg, NULL, 0, 0))
				{
					mServerSideGame->networkServer->dreamSock->dreamSock_Shutdown();

					done = true;
				}

				TranslateMessage(&WinMsg);
   				DispatchMessage(&WinMsg);
			}

			do
			{
				newTime = mServerSideGame->networkServer->dreamSock->dreamSock_GetCurrentSystemTime();
				time = newTime - oldTime;
			} while (time < 1);
			
			mServerSideGame->Frame(time);
			

			oldTime = newTime;
		}
	}
	catch(...)
	{
		LogString("Unknown Exception caught in main loop");

		mServerSideGame->networkServer->dreamSock->dreamSock_Shutdown();

		MessageBox(NULL, "Unknown Exception caught in main loop", "Error", MB_OK | MB_TASKMODAL);
	}
//unix
#else
	LogString("Init successful");

	mServerSideGame = new ServerSideGame();
	mServerSideGame->InitNetwork();
	
	int time, oldTime, newTime;

	oldTime = mServerSideGame->networkServer->dreamSock->dreamSock_GetCurrentSystemTime();

	// App main loop
	try
	{
		// Keep server alive (wait for keypress to kill it)
		while(1)
		{
			do
			{
				newTime = mServerSideGame->networkServer->dreamSock->dreamSock_GetCurrentSystemTime();
				time = newTime - oldTime;
			} while (time < 1);

			mServerSideGame->Frame(time);
			oldTime = newTime;
		}
	}
	catch(...)
	{
		mServerSideGame->networkServer->dreamSock->dreamSock_Shutdown();

		LogString("Unknown Exception caught in main loop");
	}

	LogString("Shutting down everything");

	mServerSideGame->networkServer->dreamSock->dreamSock_Shutdown();
#endif
}

ServerSideBaseGame::~ServerSideBaseGame()
{
}

void ServerSideBaseGame::createPlayer(int index)
{
}

void ServerSideBaseGame::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

    	Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    	pointLight->setType(Ogre::Light::LT_POINT);
    	pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    	pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);
	
	// create a floor mesh resource
	MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	Plane(Vector3::UNIT_Y, 0), 100, 100, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
    	Entity* floor = mSceneMgr->createEntity("Floor", "floor");
    	floor->setMaterialName("Examples/Rockwall");
	floor->setCastShadows(false);
    	mSceneMgr->getRootSceneNode()->attachObject(floor);
}

bool ServerSideBaseGame::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	return true;
}

bool ServerSideBaseGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}

void ServerSideBaseGame::go(void)
{

#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
    	mPluginsCfg = "plugins_d.cfg";
#else
    	mResourcesCfg = "resources.cfg";
    	mPluginsCfg = "plugins.cfg";
#endif
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

ServerSideBaseGame* mServerSideBaseGame;
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

	mServerSideBaseGame = new ServerSideBaseGame(hwnd);
	
	return 0;

#else
	LogString("Welcome to Army War Server v2.0");
	LogString("-------------------------------\n");

	// Ignore the SIGPIPE signal, so the program does not terminate if the
	// pipe gets broken
	signal(SIGPIPE, SIG_IGN);

	mServerSideBaseGame = new ServerSideBaseGame();
	
	return 0;

#endif

        try {
            //mBaseGame->go();
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
