/*
 *==========================================================================
 *       Filename:  alarmtest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年06月22日 15时01分14秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

void sig_fun(int abc){
	for(int i = 0; i < 100; ++i)
		printf("abc\n");
	sleep(5);
	alarm(2);
}

int main(){
	if(signal(SIGALRM, sig_fun) == SIG_ERR){
		printf("signal error\n");
	}
	alarm(2);
	int i = 0;
	while(true){
		printf("%d\n", ++i);
	}
}

