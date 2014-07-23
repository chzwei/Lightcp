/*
 *==========================================================================
 *       Filename:  ExternTest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月23日 21时27分31秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <iostream>
using namespace std;

extern int num;
int main(){
	printf("%d\n", num);
}

