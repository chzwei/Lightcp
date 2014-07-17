#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "ObjectPool.h"
#include <queue>
#include <time.h>
using namespace std;

class Test
{
public:
	int a, b, c;
	void f(){
		cout << "ok" << endl;
	}
};

void test_pool(int *test_array, int test_size, int pool_size){	
	queue<Test*> test_queue;
	ObjectChunk<Test> object_pool(pool_size+1);
	for(int i = 0; i < test_size; ++i){
		if(test_array[i] > 0){
			for (int j = 0; j < test_array[i]; ++j){
				Test *p = object_pool.new_object();
				test_queue.push(p);
			}
		}else{
			for(int j = 0; j > test_array[i]; --j){
				Test *p = test_queue.front();
				test_queue.pop();
				object_pool.delete_object(&(*p));
			}
		}
	}
}

void test_normal(int *test_array, int test_size){	
	queue<Test*> test_queue;
	for(int i = 0; i < test_size; ++i){
		if(test_array[i] > 0){
			for (int j = 0; j < test_array[i]; ++j){
				Test *p = new Test;
				test_queue.push(p);
			}
		}else{
			for(int j = 0; j > test_array[i]; --j){
				Test *p = test_queue.front();
				test_queue.pop();
				delete p;
			}
		}
	}
}

const int TEST_NUM = 1000;

void test_fun(){
	int *num = new int[TEST_NUM];
	for(int i = 0; i < TEST_NUM-1; ++i){
		num[i] = rand()%2000 - 1000;
	}
	int sum = 0, maxsum = 0;
	for (int i = 0; i < TEST_NUM-1; ++i){
		sum += num[i];
		if(sum < 0){
			num[i] -= sum;
			sum = 0;
		}
		if(sum > maxsum){
			maxsum = sum;
		}
	}
	cout << maxsum << endl;
	num[TEST_NUM-1] = 0 - sum;

	clock_t begintime, endtime;
	
	begintime = clock();
	test_pool(num, TEST_NUM, maxsum);
	endtime = clock();
	printf("pool test cost %ld\n", endtime - begintime);

	begintime = clock();
	test_normal(num, TEST_NUM);
	endtime = clock();
	printf("normal test cost %ld\n", endtime - begintime);	

	delete [] num;	
}

int main(){
//	ObjectChunk<Test> object_pool(5);
//	Test *p = object_pool.new_object();
//	object_pool.delete_object(&(*p));
	test_fun();
	return 0;
}