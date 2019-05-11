#ifndef __STATE_H__
#define __STATE_H__


struct _Target;
typedef struct _Target Target;

struct _Target {
	void(*changeState)(Target* this);

};

struct _StateBase;

typedef struct _StateBase StateBase;






struct _StateBase {
	void(*onChanged)(StateBase* this, Target* target);

};

struct _UpState;
typedef struct _UpState UpState;


struct _UpState {
	StateBase base;

};

struct _DownState;
typedef struct _DownState DownState;

struct _DownState {
	StateBase base;

};

struct _MoveState;
typedef struct _MoveState MoveState;

struct _MoveState {
	StateBase base;

};





#endif

