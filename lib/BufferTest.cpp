/*
 *==========================================================================
 *       Filename:  BufferTest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月12日 10时10分44秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Buffer.h"
#include <time.h>
using namespace std;

int main(){
	BufferPool pool;
	vector<Buffer*> v_buf =pool.NewBuf(1024);
	pool.FreeBuf(v_buf);

}

