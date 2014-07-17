#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <pthread.h>
#include "BlockQueue.h"
#include "Thread.h"
#include "SocketTask.h"

class SocketThread : public Thread
{
public:
	SocketThread();
	~SocketThread();
	void run();
private:
	static pthread_mutex_t lock;
	static pthread_cond_t cond;
	static BlockQueue<SocketTask> socketTaskQueue;
	pthread_t       thread;
    pthread_attr_t  attr;
};

#endif