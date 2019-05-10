#ifndef __DECORATOR_H__
#define  __DECORATOR_H__

#include "base.h"


struct _DecorateBase;
typedef struct _DecorateBase DecorateBase;

struct _DecorateBase
{
	Object base;
	DecorateBase *target;
	void(*decorate)(DecorateBase*this);
	//虽然有基类，但是 又想作为提供抽象基类，就还得提供虚析构函数
	void(*destruct)(DecorateBase* this);

};


struct _DecorateCharIO;
typedef struct _DecorateCharIO DecorateCharIO;

struct _DecorateBufferIO;
typedef struct _DecorateBufferIO DecorateBufferIO;


struct _DecorateCharIO {
	DecorateBase base;
	
};
struct _DecorateBufferIO {
	DecorateBase base;


};

struct _Target;
typedef struct _Target Target;


struct _Target {
	DecorateBase base;
	 

};




#endif