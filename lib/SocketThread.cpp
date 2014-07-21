#include "SocketThread.h"
#include <pthread.h>

SocketThread::SocketThread(){}

SocketThread::~SocketThread(){}

SocketThread::lock = PTHREAD_MUTEX_INITIALIZER;
SocketThread::cond = PTHREAD_COND_INITIALIZER;


void SocketThread::run(){
	pthread_mutex_lock(&SocketThread::lock);
	while(true){
		pthread_cond_wait(&SocketThread::cond, &SocketThread::lock);
	}
	SocketTask = socketTaskQueue.pop();

	//...

	pthread_mutex_unlock(&SocketThread::lock);
}