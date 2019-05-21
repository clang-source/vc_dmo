#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include<string.h>


void* mymalloc(int size) {
	void * o = 0;

	do {
		o = malloc(size);
	} while (o == 0);

	memset(o, 0, size);
	return o;
}

#define MYMALLOC(buf)\
	mymalloc(buf)


#ifdef _WIN32 
#define NEW(type,...)\
	type##Construct((type*)MYMALLOC(sizeof(type)),##__VA_ARGS__)

#elif _WIN64

#elif __linux__
#define NEW(type,...)\
({\
	typeof(type) *o =  MYMALLOC(sizeof(type));\
    type##Construct(o,##__VA_ARGS__);\
	o;\
})


#elif __unix__
#define NEW(type,...)\
({\
	typeof(type) *o =  MYMALLOC(sizeof(type));\
    type##Construct(o,##__VA_ARGS__);\
	o;\
})

#endif



#define SAFE_DELETE(ptr)\
	do{\
		if (ptr != 0) {\
			free(ptr);\
			ptr = 0;\
		}\
	}while(0);


#define OOPSAFE_DELETE(ptr)\
	do{\
		if (ptr != 0) {\
			ptr->destruct(ptr);\
			free(ptr);\
			ptr = 0;\
		}\
	}while(0);


enum STATE_;
typedef enum STATE_ STATE;

enum STATE_{
	STATE_INIT,
	STATE_START,
	STATE_STOP,
	STATE_PAUSE,
};

typedef int(*StateHandler)(int type, void* input);

struct _Target;
typedef struct _Target Target;
struct _Target {
	int age;
	int id;
	int namelength;
	char *name;
	//other construct domain memory
};


int StateInit(int type, void* input) {

	return 0;
}

int StateStart(int type, void* input) {
	Target * t = 0;
	if (type==1) {
		t = (Target*)input;
		printf("name= %s ,age =%d \n",t->name,t->age);
	}
	return 0;
}
int StateStop(int type, void* input) {

	return 0;
}

int StatePause(int type, void* input) {

	return 0;
}

static StateHandler stateHandlers[] = { 
	StateInit ,
	StateStart,
	StateStop,
	StatePause
};


void changeState(STATE s,int type,void* input) {
	StateHandler h = stateHandlers[s];
	if (h != 0) {
		h(type, input);
	}
}




typedef enum PlayerProperty_enum PlayerProperty;
enum PlayerProperty_enum {
	Pt_PASSWORD,
	Pt_ID,
	Pt_refCount,
	Pt_NAME_LENGTH,
	Pt_NAME,
};

struct Player_struct_;
typedef struct Player_struct Player;


struct Player_struct {
	int password;
	int id;
	int refCount;
	int nameLength;
	int sname;
	void(*destruct)(Player*this);









};

Player* PlayerConstruct(Player *this, int password, int id, int refCount, int namelength, int name) {
	this->password = password;
	//strcpy(this->id,id);
	this->refCount = refCount;
	this->nameLength = namelength;
	//strcpy(this->name,name);
	this->id = id;
	this->sname = name;

	return this;
}

int  PlayerGetIntProperty(Player *this, PlayerProperty pt) {
	int *ptOffset = (int*)this;
	return ptOffset[pt];
}


void PlayerDestruct(Player *this) {
	printf("player Îö¹¹º¯Êý....\n");

}



int main(int argc, const char *argvs[]) {
	int namelen = 30;
	Target * o = (Target*)MYMALLOC(sizeof(Target)+ namelen);
	o->age = 100;
	o->id = 10;
	o->namelength = namelen;
	o->name = (char*)&(o->name) + sizeof(char *);
	strcpy(o->name, "helloworld");
	STATE s = STATE_START;
	changeState(s, 1, o);



	Player * p = NEW(Player, 123, 456, 111111, 30, 99990);

	int  name = PlayerGetIntProperty(p, Pt_NAME);
	printf("name =%d \n", name);

	int password = PlayerGetIntProperty(p,Pt_PASSWORD);
	printf("password =%d \n", password);

	int id = PlayerGetIntProperty(p, Pt_ID);
	printf("id =%d \n", id);

	int refCount = PlayerGetIntProperty(p, Pt_refCount);
	printf("refCount =%d \n", refCount);

	int namelength = PlayerGetIntProperty(p, Pt_NAME_LENGTH);
	printf("namelength =%d \n", namelength);
	


	//SAFE_DELETE(p);
	OOPSAFE_DELETE(p);

	getchar();

	return 0;

}



