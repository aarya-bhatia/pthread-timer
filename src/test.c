#include "common.h"
#include "timer.h"

void *test_timer(void *args)
{
	time_t sec = * (time_t *) args;

	struct timespec timeout = {.tv_sec = sec, .tv_nsec = 0};

	Timer timer;
	timer_init(&timer);
	timer.timeout = timeout;

	timer_start(&timer);
	timer_wait(&timer);

	timer_destroy(&timer);

	return NULL;
}

int main()
{
	unsigned long sec = 4;

	for (size_t i = 0; i < 3; i++)
	{
		get_duration_sec(test_timer, (void *)&sec);
	}

	return 0;
}
