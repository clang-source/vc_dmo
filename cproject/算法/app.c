
#include<stdlib.h>
#include <stdio.h>
#include <memory.h>

#define ROW 2
#define COL 3

#define SIZE sizeof(ROW*COL*sizeof(int))

//以某种方式组织而已，no multi-weid


void testArr() {

	int *arr = (int*)malloc(SIZE);
	memset(arr, 0, SIZE);

	for (int k = 0; k < SIZE; ++k) {
		arr[k] = k;
	}

	int(*ptr)[3] = (int(*)[3])arr;

	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			printf("row=%d,col=%d ,value=%d  \n", i, j, ptr[i][j]);
		}

	}

	free(arr);
}


struct Command_;
typedef struct Command_ Command;

struct Command_ {
	int id;
	void* data;

	void* (*execute)(Command*this);
};

#define CMD_SIZE 12

#define TOTAL_SIZE 12*sizeof(Command)

Command (*cmdPtr)[4];
Command(*cmdPtr2)[3];


void* CommandExe(Command*this) {
	printf("cmd_id=%d \n",this->id);
	return (void*)0;
}

void testCmdArr() {
	Command * cmds = (Command*)malloc(TOTAL_SIZE);

	int i;
	for (i = 0; i < CMD_SIZE; ++i) {
		cmds[i].id = i;
		cmds[i].execute = CommandExe;
	}
	printf("==========================array exe================================\n");
	for (i = 0; i < CMD_SIZE; ++i){
		cmds[i].execute(&cmds[i]);
	}


	printf("==========================cmdPtr1 exe================================\n");
	int r, c;

	cmdPtr = (Command(*)[4])cmds;
	for (r = 0; r < CMD_SIZE/4; ++r) {
		printf("cmdPtr1  row=%d \n",r);
		for (c = 0; c < 4; ++c) {
			cmdPtr[r][c].execute(&cmdPtr[r][c]);
		}
	}
	

	printf("==========================cmdPtr2 exe================================\n");

	cmdPtr2 = (Command(*)[3])cmds;
	for (r = 0; r < CMD_SIZE/3; ++r) {
		printf("cmdPtr2  row=%d \n", r);
		for (c = 0; c < 3; ++c) {
			cmdPtr2[r][c].execute(&cmdPtr2[r][c]);
		}
	}


	free(cmds);

}



int main(int argc, const char *argvs[]) {

	testCmdArr();

	system("pause");


	return 0;
}