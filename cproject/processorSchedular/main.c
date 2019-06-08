#define SCHED_NORMAL 0
#define SCHED_FIFO	 1
#define SCHED_RR	 2
#define SCHED_BATCH	 4
#define SCHED_IDLE	 5
#define SCHED_DEADLINE 6


static void* myalloc(int size) {
	if (size <= 0) return 0;
	void *o = 0;
	do {
		o = malloc(size);
	} while (o==0);
	return o;
}


#define NEW(type,...)\
	type##Construct((type*)myalloc(sizeof(type)),##__VA_ARGS__)



unsigned int policy;


struct Processor_;
typedef struct Processor_ Processor;
struct SchedIndexer_;
typedef struct SchedIndexer_  SchedIndexer;

struct SchedIndexer_ {
	int pid;
	int evaluteValue;


};
struct Processor_Sched_Operation_;

typedef struct Processor_Sched_Operation_  SchedOperation;


struct Processor_ {
	int id;
	void * (*exe)(Processor*this);

};

struct sched_tree_;
typedef struct sched_tree_  sched_tree;
struct sched_tree_ {
	sched_tree * right, *left;
	SchedIndexer *index;

};
sched_tree rbtree;

sched_tree* sched_treeConstruct(sched_tree* this) {


	return  this;
}

void sched_add(sched_tree* this, Processor* p) {
	p->id = 1;
	this->index = NEW(SchedIndexer);
	this->index->pid = p->id;

}


void shed_ref(sched_tree* this, Processor* p) {
	sched_tree * node = NEW(sched_tree,p);
	sched_add(this, node);

}

Processor* ProcessorConstruct(Processor* this) {
	shed_ref(&rbtree,this);

	return this;
}


struct Processor_Sched_Operation_ {
	int pid;



};


static SchedIndexer *arrs[100] = {0};


int main(int argc, const char *argvs[]) {


	

	return 0;
}