//|||||||||||||||||||||||||||||||||||||||||||||||

#include "DemoApp.hpp"

#include <iostream>
//|||||||||||||||||||||||||||||||||||||||||||||||

#ifdef WIN32
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
	DemoApp demo;
	try
    	{
		std::cout << "calling startDemo()\n";
		demo.startDemo();
    	}
	catch(...)
    	{
#ifdef WIN32
        	MessageBoxA(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        	std::cout << "An exception has occurred\n";
#endif
    	}
    	return 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
