#ifndef  __ADAPTER_H
#define  __ADAPTER_H

#include "base.h"

struct _APIBase;
typedef struct _APIBase APIBase;

struct _OldAPI;
typedef struct _OldAPI OldAPI;

extern void OldAPI_Exe(OldAPI *this);



struct _NewAPI;
typedef struct _NewAPI NewAPI;


struct _OldAPI {
	char des[30];
};


struct _APIBase {
	//another wdu
	Object base;
	//hope this will output interface
	void(*call)(APIBase *this);
	void(*destruct)(APIBase *this);
};


struct _NewAPI {
	APIBase base;
	OldAPI * old;

};

struct _NowAPI;
typedef struct _NowAPI NowAPI;

struct _NowAPI {
	APIBase base;

};


#endif // ! __ADAPTER_H
