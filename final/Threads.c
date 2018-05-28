#include "Threads.h"

void* sleep_runner(void* time)
{
	int t = (int)time;
	runTimer(t);
	return NULL;
}