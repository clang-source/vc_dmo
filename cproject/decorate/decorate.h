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
	//��Ȼ�л��࣬���� ������Ϊ�ṩ������࣬�ͻ����ṩ����������
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