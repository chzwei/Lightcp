/*
 *==========================================================================
 *       Filename:  DynamicTest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月23日 20时16分28秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void (*p_fun)();
int (*p_test_cpp)();

int main(){
	void *lib = dlopen("./libDynamicLib.so", RTLD_LAZY);
	printf("lib load error:%s\n",dlerror());
	p_fun = (void (*)())dlsym(lib, "print");
	printf("lib load error:%s\n",dlerror());
	p_fun();
	dlclose(lib);

	void *lib2 = dlopen("./DynamicLib2.so", RTLD_LAZY);
	printf("lib load error:%s\n",dlerror());
	p_test_cpp = (int (*)())dlsym(lib2, "testcpp");
	printf("lib load error:%s\n",dlerror());
	p_test_cpp();
	dlclose(lib2);

}

