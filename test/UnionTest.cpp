#include <stdio.h>
#include <stdlib.h>

int main(){
	union U{
		int num;
		char ch[4];
	};
	U u;
	u.num = 0;
	u.ch[2] = 1;
	printf("%d\n", sizeof(u));
	printf("%d\n", u.num);
	printf("%s\n", &u.ch);
	system("pause");
}
