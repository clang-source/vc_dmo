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

//��Ҳ�ǽ��ʹ��븴�Ӷȵ�һ�ַ�ʽ
//## ������νӾ��ǶϿ�
#define DefCmd(typeCmd)\
	struct  typeCmd##_ ;\
	typedef struct  typeCmd##_  typeCmd ;\
	struct typeCmd##_{\
		CmdBase base; 


#define EndDef  };

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

#endif