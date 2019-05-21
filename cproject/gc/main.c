#include "base.h"
struct _Tree;
typedef struct _Tree Tree;

struct _Tree {
	Tree *left;
	Tree *right;

	void *value;
};

struct _Asset;
typedef struct _Asset Asset;

struct _Asset {
	Object obj;
	int id;
	char name[30];
};

Asset *AssetConstruct(Asset *this) {



	return this;
}

int main(int argc, const char *argvs[]) {

	return 0;
}



















