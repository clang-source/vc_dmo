
#include "base.h"
#include "decorate.h"





int main(int argc, const char *argvs[])
{
	Target * t = NEW(Target);


	DecorateBase * chr =(DecorateBase*) NEW(DecorateCharIO, t);
	DecorateBase * cb = (DecorateBase*) NEW(DecorateBufferIO, t);

	chr->decorate(chr);
	cb->decorate(cb);

	VIR_DELETE(chr);

	system("pause");
	return 0;
}