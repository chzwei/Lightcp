/*
 *==========================================================================
 *       Filename:  StaticTest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月06日 16时46分47秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

static volatile sig_atomic_t tmp = 0;

int main(){
	for(int i = 0; i < 10; ++i){
		switch(fork()){
		case -1:
			return -1;
		case 0:
			if(i%2)
				tmp++;
			else
				cout << tmp << endl;
			return 0;
		default:
			break;
		}
	}
	sleep(10);
}

