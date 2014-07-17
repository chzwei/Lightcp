#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>

class Thread
{
public:
	Thread();
	~Thread();
	virtual void run();

	pthread_t ntid;
	pthread_attr_t attr;
};

#endif