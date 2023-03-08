#include "common.h"

typedef struct Timer
{
	bool alive;
	pthread_t tid;
	pthread_mutex_t m;
	pthread_cond_t cv;
	struct timespec timeout; /* store the timer duration here */
} Timer;

/* Initialise a timer struct.
Caller must set the timeout value of the struct themselves.
*/
void timer_init(Timer *this);

/* Free the memory used by timer struct */
void timer_destroy(Timer *this);

/* Internal function */
void *timer_thread(void *args);

/* Start given timer for timeout seconds as specified in the struct */
void timer_start(Timer *this);

/* Stop the given timer immediately. This call will not block. */
void timer_stop(Timer *this);

/* Wait for the timer to expire. This call blocks. */
void timer_wait(Timer *this);

/* Utility function to "time" a function call. Returns the seconds of time elapsed for the function to return. 
We can specify args to pass to the function while executing it.
*/
double get_duration_sec(void *(*fptr)(void *), void *args);
