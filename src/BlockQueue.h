#ifndef BLOCKQUEUE_H
#define BLOCKQUEUE_H

#include <pthread.h>
#include <queue>
using namespace std;

template<typename T>
class BlockQueueNode
{
public:
	T item;
	BlockQueueNode<T> *next;	
};

template<typename T>
class BlockQueue
{
public:
	BlockQueue();
	~BlockQueue();
 	T* pop();
 	void push(T item);
 	int size();
private:
	pthread_mutex_t h_lock;
	pthread_mutex_t t_lock;
	int len;
	BlockQueueNode<T> *head;
	BlockQueueNode<T> *tail;
};

#endif
