#include "common.h"
#include "timer.h"

int main()
{
	struct timespec timeout = { .tv_sec = 2, .tv_nsec = 0 };

	Timer timer;
	memset(&timer, 0, sizeof timer);

	timer.timeout = timeout;

	printf("starting timer\n");

	for(size_t i = 0; i < 10; i++)
	{
		timer_start(&timer);
		timer_wait(&timer);
		printf("Timer expired\n");
	}

	printf("stopping timer\n");
	timer_stop(&timer);

	return 0;
}
