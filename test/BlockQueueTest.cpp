#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include "BlockQueue.h"
using namespace std;

class Test
{
public:
	int a, b, c;
};

BlockQueue<Test> bqueue;

void* test_push(void *arg){
	int *p = (int*) arg;
	int id = *p;
	printf("create pushthread sucess %d \n", id);
	for(int i = 0; i < 100; ++i){
		Test t;
		bqueue.push(t);
		printf("push sucess by %d \n", id);
	}
	return (void*) 0;
}

void* test_pop(void *arg){
	int *p = (int*) arg;
	int id = *p;
	printf("create popthread sucess %d \n", id);
	for(int i = 0; i < 100; ++i){
		Test *t = bqueue.pop();
		if(t == NULL){
			--i;
			continue;
		}
		printf("pop sucess by %d \n", id);
	}
	return (void*) 0;
}

void multi_test(){
	pthread_t push_thread[10], pop_thread[10];
	int push_id[10], pop_id[10];
	for(int i = 0; i < 10; ++i){
		push_id[i] = i;
		int err = pthread_create(&push_thread[i], NULL, test_push, &push_id[i]);
		if(err != 0){
			printf("cannot create push %d thread!\n", i);
		}

		pop_id[i] = i;
		err = pthread_create(&pop_thread[i], NULL, test_pop, &pop_id[i]);
		if(err != 0){
			printf("cannot create pop %d thread!\n", i);
		}
	}
}

int main(){

	multi_test();
	sleep(60);
	return 0;
}
