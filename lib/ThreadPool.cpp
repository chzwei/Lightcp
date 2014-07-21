#include "ThreadPool.h"
#include "thread.h"
#include <iostream>
#include <pthread.h>
#include <vector>
#include <Task.h>
using namespace std;

ThreadPool::ThreadPool(){
	isStop = false;
};
ThreadPool::~ThreadPool();

void ThreadPool::init(){}

void ThreadPool::execute(Thread *thread){
	threadVector.push_back(thread);
	int err = pthread_create(&thread->ntid, NULL, this->run, NULL);
	if(err != 0){
		cerr << "cannot create thread!\n";
	}
}

void ThreadPool::destroy(){
	this->isStop = true;
}

void* ThreadPool::run(void *arg){
	while(1){
		Task t = 
		if(isStop) break;
	}
}