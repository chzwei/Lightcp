/*
 *==========================================================================
 *       Filename:  ObjectPoolTest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月24日 20时51分09秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ObjectPool.h"
#include <queue>
using namespace std;

int main(){
	queue<int*> q;
	ObjectPool<int> op;
	int *tmp;
	for(int i = 0; i < 10; ++i){
		int r = rand()%10000;
		for(int j = 0; j < r; ++j){
			tmp = op.NewObject();
			q.push(tmp);
		}
		op.ShowCount();	
		while(q.size() > 0){
			tmp = q.front();
			q.pop();
			op.DeleteObject(tmp);
		}
		op.ShowCount();
		printf("\n");
	}
	
	cout << "ok" << endl;
}

