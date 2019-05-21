#include <stdio.h>




int main(int argc, const char*argvs[]) {
	int arr[4] = {1,2,3,4}; // arr type int[4]
	int(*ptr)[4] = &arr;   //ptr type int(*)[4]
	int *a = (int *)(ptr + 1);  //&arr[0]+ sizeof(arr)*1
	printf("value %d \n",*(a-1));
	getchar();



	return 0;
}