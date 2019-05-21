#include "state.h"


void TargetDestruct(Target *this);
void _TargetChangeState(Target *this, StateBase * s);

Target * TargetConstruct(Target* this) {
	this->changeState = _TargetChangeState;
	
	return this;
}

void _TargetChangeState(Target *this,StateBase * s) {

}

void TargetDestruct(Target *this) {


}


StateBase * StateBaseConstruct(StateBase *this) {



	return this;
}
 
void StateBaseOnChanged(StateBase *this, Target* target) {


}

void StateBaseDestruct(StateBase *this) {

}



UpState * UpStateConstruct(UpState* this) {

	return this;
}


void UpStateDestruct(UpState *this) {


}

DownState * DownStateConstruct(DownState* this) {


	return this;
}

void DownStateDestruct(DownState* this) {

}

MoveState* MoveStateConstruct(MoveState *this) {


	return this;
}

void MoveStateConstruct(MoveState *this);
void MoveStateDestruct(MoveState *this);

void MoveStateConstruct(MoveState *this) {
	this->base.onChanged = _MoveStateChangeState;

}

void _MoveStateChangeState(MoveState *this) {


}

void MoveStateDestruct(MoveState *this) {

}