#include "base.h"

void ObjectDestruct(Object* this);

Object * ObjectConstruct(Object* this) 
{

	this->destruct = ObjectDestruct;

	return this;
}


void ObjectDestruct(Object* this)
{

}