#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <pthread.h>
#include <vector>
#include "Thread.h"
using namespace std;

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	void init();
	void execute(Thread *thread);
	void destroy();
private:
	vector<Thread*> threadVector;
	void* run(void *);
	bool isStop;
};
#endif