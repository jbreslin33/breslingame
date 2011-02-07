#include <time.h>

class DreamWinSock
{
public:
	DreamWinSock();
	~DreamWinSock();

int dreamSock_InitializeWinSock(void);
time_t dreamSock_Win_GetCurrentSystemTime(void);
};
