#include "common.h"
#include "timer.h"

void *timer_thread(void *args)
{
	pthread_detach(pthread_self());

	Timer *this = (Timer *) args;

	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 0;

	if(clock_gettime(CLOCK_REALTIME, &ts) == -1)
	{
		perror("clock_gettime");
		return NULL;
	}

	ts.tv_sec += this->timeout.tv_sec;
	ts.tv_nsec += this->timeout.tv_nsec;

	pthread_mutex_lock(&this->m);

	this->alive = 1;

	pthread_cond_timedwait(&this->cv, &this->m, &ts);

	if(this->alive) this->alive = 0;

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

	if(this->alive) {
		this->alive = 0;
		pthread_cond_signal(&this->cv);
	}

	pthread_mutex_unlock(&this->m);
}

void timer_wait(Timer *this)
{
	pthread_mutex_lock(&this->m);

	while(this->alive) {
		pthread_cond_wait(&this->cv, &this->m);
	}

	pthread_cond_signal(&this->cv);

	pthread_mutex_unlock(&this->m);
}
