

#include <stdio.h>



int main(int argc, const char*argvs[]) {

	char * strs[] = {"hello","the","world"};

	char **p = strs;
	printf("p-value=%s \n",*p);
	p++;
	printf("new p-value=%s \n",*p);
	p++;
	printf("new p-value=%s \n", *p);
	getchar();

	return 0;
}