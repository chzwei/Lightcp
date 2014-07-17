#include <pthread.h>
#include "src/BlockQueue.h"
#include <iostream>
#include <stdio.h>
using namespace std;

const int THREAD_NUM = 10;

BlockQueue<int> blockQueue;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_fun(void* arg){
	int* id = (int*)arg;
	printf("thread %d running...\n", *id);
	int *item;
	while(true){
		pthread_mutex_lock(&mutex);
		while( (item = blockQueue.pop()) == NULL) {
			pthread_cond_wait(&cond, &mutex);
		}
		pthread_mutex_unlock(&mutex);
		for(int i = 1; i <= 1000; ++ i){
			for(int j = 1; j <= 1000; ++j){
				*item *= j;
				*item /= j;
			}
		}
		printf("thread: %d, %d\n", *id, *item);
	}
}

int main(){
	pthread_t threads[THREAD_NUM];

	int err;
	for(int i = 0; i < THREAD_NUM; ++i){
		int *id = new int;
		*id = i;
		if((err = pthread_create(&threads[i], NULL, thread_fun, (void*)id)) != 0)
			printf("create pthread %d error!\n", *id);
	}

	for(int i = 0; i < 100; ++i){
		blockQueue.push(i);
		pthread_cond_signal(&cond);
	}

	//cout << blockQueue.size() << endl;
	sleep(10);
}