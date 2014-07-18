#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

int main(){
	int num;
	scanf("%d", &num);
	printf("%d\n", num);
	char ch[5];
    memcpy(ch, &num, sizeof(num));
    ch[4] = '\0';
	printf("%s\n", ch);
	int othernum = 0;
	memcpy(&othernum, ch, sizeof(othernum));
	printf("%d\n", othernum);
	system("pause");
}
