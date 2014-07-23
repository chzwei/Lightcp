#include <stdio.h>
#include <stdlib.h>

void QuitSort(int *array, int l, int r){
	if (array == NULL || l >= r)  return;
	int tmp = array[l], i = l, j = r;
	while(i < j){
		while(i < j && array[j] > tmp) --j;
		if(i < j) array[i++] = array[j];
		while(i < j && array[i] < tmp) ++i;
		if(i < j) array[j--] = array[i];
	}
	array[i] = tmp;
	QuitSort(array, l, i-1);
	QuitSort(array, i+1, r);
}

int main(){
	int size = 20;
	int *num = new int[size];
	for(int i = 0; i < size; ++i){
		num[i] = rand();
	}
	for (int i = 0; i < size; ++i){
		printf("%d\n", num[i]);
	}
	system("pause");
	QuitSort(num, 0, size-1);
	for (int i = 0; i < size; ++i){
		printf("%d\n", num[i]);
	}
	system("pause");
	return 0;
}
