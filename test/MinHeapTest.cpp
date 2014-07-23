#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class MinHeap
{
public:
	MinHeap():size(0), capacity(10){
		data = new int[capacity];
	}

	MinHeap(int num):size(0), capacity(num){
		data = new int[capacity];
	}

	~MinHeap(){
		delete [] data;
	}

	void insert(int num){
		int index = size++;
		while(index > 0){
			if(num < data[(index-1)/2]){
				data[index] = data[(index-1)/2];
				index = (index-1)/2;
			}else{
				data[index] = num;
				return ;
			}
		}
		data[0] = num;
	}

	int pop(){
		int res = data[0];
		data[0] = data[--size];
		int index = 1, tmp = data[0];
		while(index < size){
			if(index+1 < size && data[index+1] < data[index])
				++index;

			if( data[index] < tmp){
				data[(index-1)/2] = data[index];
				data[index] = tmp;
				index = index*2+1;
			}else{
				return res;
			}
		}
		return res;
	}

private:
	int size;
	int *data;
	int capacity;
};

int main(){
	MinHeap heap(20);
	int num;
	for(int i = 0; i < 20; ++i){
		heap.insert(rand());
	}
	for (int i = 0; i < 20; ++i){
		printf("%d\n", heap.pop());
	}
	system("pause");
	return 0;
}
