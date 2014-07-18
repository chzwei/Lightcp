#include "BlockQueue.h"
#include "pthread.h"
#include <queue>
using namespace std;

template<typename T>
BlockQueue<T>::BlockQueue(){
	pthread_mutex_init(&this->t_lock, NULL);
	pthread_mutex_init(&this->h_lock, NULL);
	this->len = 0;
	BlockQueueNode<T> *node = new BlockQueueNode<T>();
	node->next = NULL;
	this->head = node;
	this->tail = node;
}

template<typename T>
BlockQueue<T>::~BlockQueue(){
	pthread_mutex_lock(&this->t_lock);
	pthread_mutex_lock(&this->h_lock);
	BlockQueueNode<T> *node = this->head;
	BlockQueueNode<T> *new_head = node->next;
	while(new_head != NULL){
		this->head = new_head;
		this->len --;
		delete node;
		node = this->head;
		new_head = node->next;
	}
	delete node;
	pthread_mutex_unlock(&this->h_lock);
	pthread_mutex_unlock(&this->t_lock);

	pthread_mutex_destroy(&this->t_lock);
	pthread_mutex_destroy(&this->h_lock);
	
}

template<typename T>
T* BlockQueue<T>::pop(){
	T* res = new T();
	pthread_mutex_lock(&this->h_lock);
	BlockQueueNode<T> *node = this->head;
	BlockQueueNode<T> *new_head = node->next;
	if(new_head == NULL){
		pthread_mutex_unlock(&this->h_lock);
		return NULL;
	}
	*res = new_head->item;
	this->head = new_head;
	this->len --;
	delete node;
	pthread_mutex_unlock(&this->h_lock);
	return res;
}

template<typename T>
void BlockQueue<T>::push(T item){
	BlockQueueNode<T> *node = new BlockQueueNode<T>();
	node->item = item;
	node->next = NULL;
	pthread_mutex_lock(&this->t_lock);
	this->tail->next = node;
	this->tail = node;
	this->len ++;
	pthread_mutex_unlock(&this->t_lock);
}

template<typename T>
int BlockQueue<T>::size(){
	pthread_mutex_lock(&this->t_lock);
	pthread_mutex_lock(&this->h_lock);
	int res = this->len;
	pthread_mutex_unlock(&this->h_lock);
	pthread_mutex_unlock(&this->t_lock);
	return res;
}
