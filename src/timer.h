#include "common.h"

typedef struct Timer
{
	bool alive;
	pthread_t tid;
	pthread_mutex_t m;
	pthread_cond_t cv;
	struct timespec timeout;
} Timer;

void *timer_thread(void *args);
void timer_start(Timer *this);
void timer_stop(Timer *this);
void timer_wait(Timer *this);
