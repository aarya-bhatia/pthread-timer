#include "common.h"
#include "timer.h"

int main()
{
	struct timespec timeout = {.tv_sec = 4, .tv_nsec = 0};

	Timer timer;
	memset(&timer, 0, sizeof timer);

	timer.timeout = timeout;

	for (size_t i = 0; i < 3; i++)
	{
		timer_start(&timer);
		timer_wait(&timer);
	}

	return 0;
}
