#include "base.h"
#include "adapter.h"

#include <stdio.h>

struct _App;
typedef struct _App App;

struct _App {
	APIBase *api;

};
void AppSetImpl(App* this, APIBase *impl);
void AppDestruct(App* this);

App * AppConstruct(App* this, APIBase *impl) {
	AppSetImpl(this,impl);
	return this;
}
void AppDestruct(App* this) {


}

static void AppSetImpl(App* this, APIBase *impl) {
	this->api = impl;
}


void AppCall(App* this) {
	this->api->call(this->api);
}

int main() {
	OldAPI  *old = NEW(OldAPI);
	NowAPI  *now = NEW(NowAPI);

	NewAPI * new = NEW(NewAPI);

	App *app = NEW(App, (APIBase*)now);

	AppCall(app);

	AppSetImpl(app, (APIBase*)new);

	AppCall(app);

	NOVIR_DELETE(OldAPI,old);
	NOVIR_DELETE(NowAPI, now);
	NOVIR_DELETE(NewAPI, new);
	NOVIR_DELETE(App, app);


	getchar();
	return  0;
}