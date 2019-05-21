#include <stdlib.h>
#include <stdio.h>


int main(int argc, const char *argvs[]) {
	struct NetBits {
		unsigned a :2;
		unsigned b :1;
		unsigned :5; //≤ª π”√
		unsigned c : 4;
		unsigned : 4;
	}bits,*pt;


	printf("%d",sizeof(bits));

	system("pause");

	return 0;
}