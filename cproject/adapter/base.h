#ifndef  __DOM_BASE__H
#define  __DOM_BASE__H

#include <memory.h>
#include<stdlib.h>

static void* myalloc(int size) {
	void *o = 0;
	do {
		o = malloc(size);
	} while (o == 0);
	memset(o, 0, size);
	return o;
}

//宏也是降低代码复杂度的一种方式
//## 如果不衔接就是断开
#define DefCmd(typeCmd)\
	struct  typeCmd##_ ;\
	typedef struct  typeCmd##_  typeCmd ;\
	struct typeCmd##_{\
		CmdBase base; 


#define EndDef  };


#define NOVIR_DELETE(type,ptr)\
		if (ptr!=0){\
				type##Destruct(ptr);\
				free(ptr);\
				ptr=0;\
		}

#define VIR_DELETE(ptr)\
		if (ptr!=0){\
				ptr->destruct(ptr);\
				free(ptr);\
				ptr=0;\
		}

#ifdef _WIN32

#define NEW(type,...)\
type##Construct((type*)myalloc(sizeof(type)),##__VA_ARGS__);


#elif _WIN64
#define NEW(type,...)\
type##Construct((type*)myalloc(sizeof(type)), ##__VA_ARGS__);


#elif __linux__
#define NEW(type,...)\
({\
	type * o = myalloc(sizeof(type));\
	type##Construct(o, ##__VA_ARGS__);\
	o;\
})

#elif __unix__
#define NEW(type,...)\
({\
	type * o = myalloc(sizeof(type));\
    type##Construct(o, ##__VA_ARGS__);\
	o;\
})

#endif





struct _ObjectBase;
typedef struct _ObjectBase ObjectBase;

struct _ObjectBase {
	int id;
};

struct _Object;
typedef struct _Object Object;

struct _Object {
	ObjectBase base;
	void(*destruct)(Object *);
//	void(*destruct)(Object *this);
};


#endif