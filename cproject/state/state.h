#ifndef __STATE_H__
#define __STATE_H__


struct _Target;
typedef struct _Target Target;


struct _StateBase;

typedef struct _StateBase StateBase;



struct _StateBase {
	Target * target;
	void(*onChanged)(StateBase*, Target* target);
	void(*destruct)(StateBase*);
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



struct _Target {
	void(*changeState)(Target*, StateBase*);

};


#endif

