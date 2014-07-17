#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <queue>
#include <time.h>
using namespace std;

void StringFun(string& str){}
void CharFun(char *ch){}


int main(){
	string str = "abdashkjahdscadfsfkjhadskjhadskadsjl";
	char ch[]  = "abdashkjahdscadfsfkjhadskjhadskadsjl";
	
	clock_t begin = clock();
	for(int i = 0; i < 10000000; ++i)
		StringFun(str);
	clock_t end = clock();
	cout << "string:" << end-begin << endl;

	begin = clock();
	for(int i = 0; i < 10000000; ++i)
		CharFun(ch);
	end = clock();
	cout << "char:" << end-begin << endl;
	return 0;
}
