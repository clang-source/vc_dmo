#include "adapter.h"

#include <stdio.h>

APIBase * APIBaseDestruct(APIBase* this);
void APIBaseCall(APIBase* this);
APIBase * APIBaseConstruct(APIBase* this)
{
	this->call = APIBaseCall;
	this->destruct = APIBaseDestruct;
	return this;
}

void APIBaseCall(APIBase* this) {

	printf("基类方法：APIBaseCall");

}

APIBase * APIBaseDestruct(APIBase* this)
{
	printf("基类方法：APIBaseDestruct");

	return this;
}


void NewAPIDestruct(NewAPI* this);
void NewAPICall(NewAPI* this);
void OldAPI_Exe(OldAPI *this);

NewAPI * NewAPIConstruct(NewAPI * this) {
	this->base.call = NewAPICall;
	this->base.destruct = NewAPIDestruct;
	return this;
}

void NewAPIDestruct(NewAPI * this){
	 

}

void NewAPICall(NewAPI * this){
	OldAPI_Exe(this->old);
	printf("NewAPICall..\n");
}

void NowAPIDestruct(NowAPI *this);
void NowAPICallImpl(NowAPI *this);


NowAPI *NowAPIConstruct(NowAPI *this) {
	this->base.call = NowAPICallImpl;
	this->base.destruct = NowAPIDestruct;
	printf("NowAPIConstruct..\n");
	return this;
}

void NowAPIDestruct(NowAPI *this) {
	printf("NowAPIDestruct..\n");
}

void NowAPICallImpl(NowAPI *this) {
	printf("NowAPICallImpl ...\n");

}

OldAPI * OldAPIConstruct(OldAPI *this) {
	
	printf("OldAPIConstruct ...\n");
	return this;
}

void OldAPIDestruct(OldAPI *this) {
	printf("OldAPIDestruct ...\n");
}



void OldAPI_Exe(OldAPI *this) {
	printf("OldAPI_Exe ....\n");
}