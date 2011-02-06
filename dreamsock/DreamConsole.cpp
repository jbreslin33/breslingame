
#ifdef WIN32
#include <windows.h>
#include <commctrl.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "DreamConsole.h"

FILE *LogFile;

#ifdef WIN32
DreamConsole *console = NULL;
#endif

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void StartLog(void)
{
	time_t current = time(NULL);
#ifdef WIN32
	//FILE *stream;
	if((fopen_s(&LogFile,"DreamSock.log", "w")) != NULL)
	{
		fprintf_s(LogFile, "Log file started %s", ctime(&current));
		
		fclose(LogFile);
	}

	if((fopen_s(&LogFile,"DreamSock.log", "a")) != NULL)
	{
	}
#endif
#ifdef UNIX
	if((LogFile = fopen("DreamSock.log", "w")) != NULL)
	{
		fprintf(LogFile, "Log file started %s", ctime(&current));
		
		fclose(LogFile);
	}

	if((LogFile = fopen("DreamSock.log", "a")) != NULL)
	{
	}
#endif
}

#ifdef WIN32
void StartLogConsole(void)
{
	console = new DreamConsole("DreamSock application");
}
#endif

void StopLog(void)
{
	fclose(LogFile);

#ifdef WIN32
	if(console != NULL)
		delete console;
#endif
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void LogString(const char *string, ...)
{
	
	char buf[1024];
	va_list ap;
	va_start(ap, string);
	vsprintf(buf, string, ap);
	va_end(ap);

	// Get current time and date
	time_t current = time(NULL);

	char timedate[64];
	sprintf(timedate, "time: %s", ctime(&current));

	// Remove linefeed from time / date string
	int i = 0;

	while(timedate[i] != '\n')
	{
		i++;
	}

	timedate[i] = '\0';

	// Output log string
#ifdef WIN32
	char c = '\n';
	//fprintf_s(LogFile, "%s:", timedate,c);

	if(console)
		console->println(timedate, 0);
//
	//fprintf_s(LogFile, "%s:", buf,c);

	if(console)
		console->println(buf, 0);

#else
	// Linux outputs to screen and to the open file when running as daemon
	printf("%s: %s\n", timedate, buf);
#endif
	
}

/***************

 Console

****************/

#ifdef WIN32

DreamConsole::DreamConsole(char *title)
{
	AllocConsole();
	SetConsoleTitle(title);
}

DreamConsole::~DreamConsole()
{
	FreeConsole();
}

void DreamConsole::println(char *string, int type, ...)
{
	char buf[1024];
	char buf2[1024];
	va_list ap;
	va_start(ap, string);
	vsprintf(buf, string, ap);
	va_end(ap);

	sprintf(buf2, "-> %s\n", buf);

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	switch(type)
	{
	case 0:
		SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;

	case 1:
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	}

	WriteConsole(console, buf2, strlen(buf2), NULL, NULL);
}

#endif
