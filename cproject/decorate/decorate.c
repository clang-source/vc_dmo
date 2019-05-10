#include "decorate.h"
#include<stdio.h>

//Target
void TargetDecorate(Target *this);
void TargetDestruct(Target *this);

Target * TargetConstruct(Target *this)
{
	this->base.decorate = TargetDecorate;
	this->base.base.destruct = TargetDestruct;
	return this;
}

void TargetDestruct(Target *this) {

	printf(" TargetDestruct ...\n");
}

void TargetDecorate(Target *this) {

	printf(" TargetDecorate ...\n");
}

//DecorateBase

DecorateBase* DecorateBaseDestruct(DecorateBase *this);
void DecorateBaseDecorate(DecorateBase * this);


DecorateBase* DecorateBaseConstruct(DecorateBase *this, DecorateBase *target)
{
	this->base.destruct = DecorateBaseDestruct;
	this->decorate = DecorateBaseDecorate;
	this->target = target;

	
	return this;
}


void DecorateBaseDecorate(DecorateBase* this) {

	printf(" DecorateBaseDecorate ...\n");
}

DecorateBase* DecorateBaseDestruct(DecorateBase*this, DecorateBase *target)
{
	
	printf(" DecorateBaseDestruct ...\n");
	return this;
}

//DecorateCharIO
void DecorateCharIODestruct(DecorateCharIO* this);
void DecorateCharIODecorate(DecorateCharIO* this);
DecorateCharIO * DecorateCharIOConstruct(DecorateCharIO* this, DecorateBase *target)
{
	DecorateBaseConstruct((DecorateBase*)this,target);
	this->base.decorate = DecorateCharIODecorate;
	this->base.destruct = DecorateCharIODestruct;
	printf(" DecorateCharIOConstruct ...\n");
	return this;
}
void DecorateCharIODecorate(DecorateCharIO* this) {
	this->base.target->decorate(this->base.target);

	printf(" DecorateCharIODecorate ...\n");
}

void DecorateCharIODestruct(DecorateCharIO* this){
	printf(" DecorateCharIODestruct ...\n");
}

//DecorateBufferIO

void DecorateBufferIODestruct(DecorateBufferIO*this);
void DecorateBufferIODecorate(DecorateBufferIO*this);

DecorateBufferIO * DecorateBufferIOConstruct(DecorateBufferIO *this, DecorateBase *target) {
	DecorateBaseConstruct((DecorateBase*)this, target);
	this->base.decorate = DecorateBufferIODecorate;
	this->base.destruct = DecorateBufferIODestruct;

	printf(" DecorateBufferIOConstruct ...\n");
	return this;
}

void DecorateBufferIODecorate(DecorateBufferIO*this) {
	printf(" DecorateBufferIODecorate ...\n");
	this->base.target->decorate(this->base.target);
}

void DecorateBufferIODestruct(DecorateBufferIO*this) {

	printf(" DecorateBufferIODestruct ...\n");

}


