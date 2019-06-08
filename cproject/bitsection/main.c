#include <stdlib.h>
#include <stdio.h>



//微端有格调；不能夸存储单元
struct CharBit {
	char a : 7;
	char b : 7;
	char c : 2;

	char f1 : 1;
	char f2:  1;
	char f3 : 1; 
	char f4 : 1;
	char f5 : 1;
	//char f6 : 1;
//	char f7 : 1;
char f8 : 1;

};




int main(int argc, const char *argvs[]) {
	 
	printf("sizeof(struct CharBit)=%d \n", sizeof(struct CharBit));

 

	system("pause");

	return 0;
}