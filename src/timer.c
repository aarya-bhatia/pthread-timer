#include "common.h"
#include "timer.h"
#include <log.h>

void *timer_thread(void *args)
{
	pthread_detach(pthread_self());

	Timer *this = (Timer *)args;

	struct timespec ts;

	if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
	{
		perror("clock_gettime");
		return NULL;
	}

	ts.tv_sec += this->timeout.tv_sec;
	ts.tv_nsec += this->timeout.tv_nsec;

	pthread_mutex_lock(&this->m);

	this->alive = 1;

	log_info("Timer started for %zu seconds", this->timeout.tv_sec);

	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	pthread_cond_timedwait(&this->cv, &this->m, &ts);

	log_info("Timer expired");

	clock_gettime(CLOCK_MONOTONIC, &start);
	double duration = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) * 1E-9;
	log_debug("Duration: %f", duration);

	if (this->alive)
		this->alive = 0;

	pthread_cond_signal(&this->cv);

	pthread_mutex_unlock(&this->m);

	return NULL;
}

void timer_start(Timer *this)
{
	pthread_create(&this->tid, NULL, timer_thread, this);
}

void timer_stop(Timer *this)
{
	pthread_mutex_lock(&this->m);

	if (this->alive)
	{
		this->alive = 0;
		pthread_cond_signal(&this->cv);
	}

	pthread_mutex_unlock(&this->m);
}

void timer_wait(Timer *this)
{
	pthread_mutex_lock(&this->m);

	while (this->alive)
	{
		pthread_cond_wait(&this->cv, &this->m);
	}

	pthread_cond_signal(&this->cv);

	pthread_mutex_unlock(&this->m);
}
