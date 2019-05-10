

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dombase.h"

struct _CmdBase;

typedef struct _CmdBase CmdBase;

CmdBase * CmdBaseConstruct(CmdBase* this);
void CmdBaseDestruct(CmdBase* this);


void CmdBaseExec(CmdBase* this);

struct _CmdBase {
	void(*exec)(CmdBase* this);
	void(*destruct)(CmdBase* this);
};


CmdBase * CmdBaseConstruct(CmdBase* this)
{
	this->exec = CmdBaseExec;
	this->destruct = CmdBaseDestruct;
	printf("CmdBaseConstruct \n");
	return this;
}

void  CmdBaseDestruct(CmdBase* this)
{
	printf("CmdBaseConstruct »ùÀàÏú»Ù.... \n");

}


void CmdBaseExec(CmdBase* this) {
	printf("CmdBaseExec  \n");
}

void CmdBaseDelete(CmdBase *this)
{
	

}



DefCmd(OpenCmd)
void(*onOpen)(OpenCmd* this, int fd);


EndDef

DefCmd(CloseCmd)
void(*onClose)(CloseCmd* this, int fd);


EndDef


void OpenCmdOnOpen(OpenCmd* this, int fd);
void CloseCmdOnClose(CloseCmd* this, int fd);

CloseCmd * CloseCmdConstruct(CloseCmd* this);

OpenCmd *OpenCmdConstruct(OpenCmd* this);

void OpenCmdDestruct(OpenCmd* this);
void CloseCmdDestrcut(CloseCmd* this);

OpenCmd *OpenCmdConstruct(OpenCmd* this)
{
	CmdBaseConstruct((CmdBase*)this);
	printf("OpenCmdConstruct \n");
	
	this->onOpen = OpenCmdOnOpen;
	this->base.destruct = OpenCmdDestruct;
	return this;
}

void OpenCmdOnOpen(OpenCmd* this, int fd)
{
	printf("OpenCmdOnOpen \n");

}

void OpenCmdDestruct(OpenCmd* this) {
	CmdBaseDestruct((CmdBase*)this);
	printf("OpenCmdDestruct \n");
}



CloseCmd * CloseCmdConstruct(CloseCmd* this)
{
	CmdBaseConstruct((CmdBase*)this);
	printf("CloseCmdConstruct \n");
	this->onClose = CloseCmdOnClose;
	this->base.destruct = CloseCmdDestrcut;
	return this;
}

void CloseCmdOnClose(CloseCmd* this, int fd) {
	printf("CloseCmdOnClose \n");

}

void CloseCmdDestrcut(CloseCmd* this) {
	CmdBaseDestruct((CmdBase*)this);
	printf("CloseCmdDestrcut \n");
}



int main(int argc, const char *argvs[])
{
	CloseCmd * closeCmd = NEW(CloseCmd);
	OpenCmd * openCmd = NEW(OpenCmd);

	closeCmd->onClose(closeCmd, 1);
	openCmd->onOpen(openCmd, 1);

	CmdBase *b = (CmdBase*)closeCmd;
	VIR_DELETE(b);

	b = (CmdBase*)openCmd;
	VIR_DELETE(b);

	system("pause");
	return 0;
}
