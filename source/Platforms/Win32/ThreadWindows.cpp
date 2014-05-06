#include <windows.h>

#include "ThreadWindows.h"

ThreadWindows::ThreadWindows()
{
}

ThreadWindows::~ThreadWindows()
{
	CloseHandle(thread);
}

void ThreadWindows::start()
{
	running = true;
	thread = CreateThread(NULL, 0, threadEntry, this, 0, NULL);
}

void ThreadWindows::interrupt()
{
	running = false;
}

void ThreadWindows::join()
{
	WaitForSingleObject(thread, INFINITE);
	running = false;
	thread = NULL;
}

bool ThreadWindows::joinFor(int milliseconds)
{
	if (WaitForSingleObject(thread, milliseconds) == WAIT_OBJECT_0)
	{
		running = false;
		thread = NULL;
		return true;
	}

	return false;
}

DWORD CALLBACK ThreadWindows::threadEntry(void *param)
{
	ThreadWindows *threadWindows = reinterpret_cast<ThreadWindows *>(param);
	threadWindows->run();
	return 0;
}
