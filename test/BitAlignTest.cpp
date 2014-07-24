/*
 *测试结果
 *1: 188
 *2: 281
 */

#include <iostream>
#include <time.h>
#include <cstring>
#include <vector>
using namespace std;


struct B{ 
       char a;
       int b;
       short c;
       char d;
}; 

int main() 
{ 
    char array[] = {1, 1, 0, 0, 0, 1, 0, 1};
    char *aa = array;
    int *bb = (int*)(&array[1]);
    short *cc = (short*)(&array[5]);
    char *dd = &array[7];

    B tmp;
    tmp.a = 1;
    tmp.b = 1;
    tmp.c = 1;
    tmp.d = 1;
    
    int num;
    clock_t begin1 = clock();
    for(int i = 0; i < 10000; ++i)
    for(int j = 0; j < 10000; ++j){
            num = tmp.b;
    }
    clock_t end1 = clock();

    clock_t begin2 = clock();
    for(int i = 0; i < 10000; ++i)
    for(int j = 0; j < 10000; ++j){
            num = *bb;
    }
    clock_t end2 = clock();
    
    printf("1: %ld\n", end1-begin1);
    printf("2: %ld\n", end2-begin2);
    system("pause");
    return 0; 
} 
