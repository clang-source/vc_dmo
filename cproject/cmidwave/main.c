#include "domainoriented.h"

#include <Windows.h>
#include <stdio.h>

#define NAME_SIZE_LIMIT 30


#define MODULE_Index_LIMIT 65535




#define MODULE_STATUS_NOT_EXISTED -1
#define MODULE_STATUS_OUT_OF_INDEX_RANGE -2
#define MODULE_STATUS_REISTER_NIL_OPT -3
#define MODULE_STATUS_REG_SAME_OPT -4

#define DeleteGen(type)\
	void type##Delete(type*this)\
	{\
		type##Destruct(this);\
		this->base.delete(this);\
	}


//通过枚举来框定数据选择范围

enum  _ModuleType {
	BASE=0,
	MODULE_NIC=1,
	MODULE_DISK = 2,
};
typedef  enum  _ModuleType ModuleType;

//模块就是一个 逻辑的容器
struct _ModuleBase;
typedef struct _ModuleBase ModuleBase;


struct _ModuleInerLogicOperation;
typedef struct _ModuleInerLogicOperation ModuleInerLogicOperation;


struct _ModuleCtl;
typedef struct _ModuleCtl ModuleCtl;

struct _ModContext;
typedef struct _ModContext ModContext;

struct _ModContext {
	ModuleCtl *ctl;
	void(*regLogicOpt)(ModContext* this, int midx, ModuleInerLogicOperation *opt);
	void(*destruct)(ModContext* this);

};



struct _ModuleCtl {
	ModuleBase *mods[MODULE_Index_LIMIT];
	ModuleInerLogicOperation *opts[MODULE_Index_LIMIT];

};


//方便扩展容器的内部业务逻辑的行为
struct _ModuleInerLogicOperation {
	int(*sendPack)(ModuleBase *this, int pack);
	void(*onSwitchOff)(ModuleBase *this);
	void(*onSwitchOn)(ModuleBase *this);
};


struct _ModuleBase {
	int mid;
	char name[30];

	//导航上下文信息
	ModContext *ctx;

	//容器的方法,生命周期的方法
	void(*init)(ModuleBase* this);
	void(*exit)(ModuleBase* this);
	void(*destrcut)(ModuleBase* this);

	void(*onSwitchOpt)(ModuleBase* this, ModuleInerLogicOperation * newOpt, ModuleInerLogicOperation *oldOpt);
	//模块的行为被初始化的时候
	void(*onAttachOpt)(ModuleBase* this, ModuleInerLogicOperation *opt);

	//delete操作符
	void(*delete)(ModuleBase* this);
};


void ModuleBaseInit(ModuleBase* this);
void ModuleBaseExit(ModuleBase* this);
void ModuleBaseDestruct(ModuleBase*this);
void ModuleBaseOnSwitchOpt(ModuleBase* this, ModuleInerLogicOperation * newOpt, ModuleInerLogicOperation *oldOpt);
void ModuleBaseOnAttachOpt(ModuleBase* this, ModuleInerLogicOperation *opt);
void ModuleBaseDelete(ModuleBase* this); 


ModuleBase * ModuleBaseConstruct(ModuleBase* this, int mid, const char *name) {
	this->mid = mid;
	strcpy_s(this->name, NAME_SIZE_LIMIT, name);
	this->init = ModuleBaseInit;
	this->exit = ModuleBaseExit;
	this->destrcut = ModuleBaseDestruct;
	this->onSwitchOpt = ModuleBaseOnSwitchOpt;
	this->onAttachOpt = ModuleBaseOnAttachOpt;
	this->delete = ModuleBaseDelete;
	return this;
}

//模块的行为被切换的时候调用
void ModuleBaseOnSwitchOpt(ModuleBase* this, ModuleInerLogicOperation * newOpt, ModuleInerLogicOperation *oldOpt)
{



}

//新的行为初始化
void ModuleBaseOnAttachOpt(ModuleBase* this, ModuleInerLogicOperation *opt)
{


}

void ModuleBaseDelete(ModuleBase* this) {
	ModuleBaseDestruct(this);
	this->delete(this);
}

int sendPack(ModuleBase *this, int pack) {


}




void ModContextRegLogicOptImpl(ModContext* this, int midx, ModuleInerLogicOperation *opt);
void ModContextDestruct(ModContext *this);
 
ModContext* ModContextConstruct(ModContext *this) {
//	this->regLogicOpt = ModContextRegLogicOptImpl;
	this->destruct = ModContextDestruct;
	return this;
}

void ModContextDestruct(ModContext *this) {


}

int ModuleCtlRegLogicOpt(ModuleCtl* this, int midx, ModuleInerLogicOperation *opt);

void ModContextRegLogicOptImpl(ModContext* this, int midx, ModuleInerLogicOperation *opt) {
	int res = ModuleCtlRegLogicOpt(this->ctl, midx, opt);
	
}


ModuleInerLogicOperation baseOpt;

//初始化基类模块容器
void ModuleBaseInit(ModuleBase* this) {
	baseOpt.sendPack = sendPack;
//注册逻辑行为
	this->ctx->regLogicOpt(this->ctx,this->mid,&baseOpt);
}
//模块退出时候触发
void ModuleBaseExit(ModuleBase* this) {

}
//模块销毁
void ModuleBaseDestruct(ModuleBase*this)
{

}





ModuleCtl * ModuleCtlConstruct(ModuleCtl* this) {
	
	return this;
}

int ModuleCtlRegMod(ModuleCtl* this, ModuleBase* mod) {
	if (mod != 0 && this->mods[mod->mid] == 0) {
		this->mods[mod->mid] = mod;
	}
}

int ModuleCtlRegLogicOpt(ModuleCtl* this,int midx , ModuleInerLogicOperation *opt) {

	if (this->mods[midx] == 0) return  MODULE_STATUS_NOT_EXISTED;
	if (opt == 0) return MODULE_STATUS_REISTER_NIL_OPT;
	ModuleInerLogicOperation *ori = 0;
	if (midx > MODULE_Index_LIMIT) return MODULE_STATUS_OUT_OF_INDEX_RANGE;
	ModuleBase *m = this->mods[midx];
	ori = this->opts[midx];
	if (ori == opt) {
		return MODULE_STATUS_REG_SAME_OPT;
	}
	
	if (ori != 0) {
		if (ori->onSwitchOff != 0) {
			ori->onSwitchOff(m);
		}
	}

	if (opt != 0) {
		if (opt->onSwitchOn!=0) {
			opt->onSwitchOn(m);
		}
	
	}

	
	m->onSwitchOpt(m, ori,opt);

}

//只初始化 模块容器
void ModuleCtlPowerOnAll(ModuleCtl* this) {
	int i=0;
	for (; i < MODULE_Index_LIMIT; i++) {
		if (this->mods[i] != NULL) {
			this->mods[i]->init(this->mods[i]);
			Sleep(20);
		}
	}

}


void ModuleCtlPowerOffAll(ModuleCtl* this) {
	int i = 0;
	for (; i < MODULE_Index_LIMIT; i++) {
		if (this->mods[i] != NULL) {
			this->mods[i]->exit(this->mods[i]);
			Sleep(20);
		}
	}

}


void ModuleCtlPowerOn(ModuleCtl* this,int midx) {
	ModuleBase *m = 0;
	if (midx <= MODULE_Index_LIMIT) {
		m = this->mods[midx];
	}
	if (m != 0) {
		//doPrefitler(m->prefilter);
		m->init(m);
		//doPostfilter(m->postfilter);
	}
	 
}

void ModuleCtlPowerOff(ModuleCtl* this, int midx) {


}

static void doPrefitler(ModuleBase *target) {
	
}


static void doPostfilter(ModuleBase *target) {
	if (target == 0) return;
#if 0
	if (target->postfilter != 0) {
		doPostfilter(target->postfilter);
	}
	else {
		target->init(target);
		Sleep(10);
	}
#endif
}



struct _NICMod;
typedef struct _NICMod NICMod;

void NICModDelete(NICMod* this);


struct _NICMod {
	ModuleBase base;

	//void(*copyFromUser)(NICMod *this);
	//void(*copyToUser)(NICMod *this);

	void(*delete)(NICMod* this);

};
void NICModInit(NICMod* this);
void NICModExit(NICMod* this);
void NICModOnAttachOpt(ModuleBase *this);
void NICModOnSwitchOpt(ModuleBase* this, ModuleInerLogicOperation * newOpt, ModuleInerLogicOperation *oldOpt);
NICMod* NICModDestruct(NICMod* this);


NICMod * NICModConstruct(NICMod *this)
{
	ModuleBaseConstruct((ModuleBase*)this, MODULE_NIC,"nic_module");
	this->base.onAttachOpt = NICModOnAttachOpt;
	this->base.onSwitchOpt = NICModOnSwitchOpt;
	this->base.init = NICModInit;
	this->base.exit = NICModExit;

	//析构函数
	this->base.destrcut = NICModDestruct;
	//delete操作符
	this->delete = NICModDelete;
	
	return this;
}


void  NICModOnAttachOpt(ModuleBase *this)
{
	printf("wenweiping  NICModOnAttachOpt....\n");

}

void NICModOnSwitchOpt(ModuleBase* this, ModuleInerLogicOperation * newOpt, ModuleInerLogicOperation *oldOpt){


}

void NICModExit(NICMod* this) {
	printf("wenweiping  NICModExit....\n");
}

void NICModInit(NICMod* this) {

	printf("wenweiping  NICModInit....\n");

}



NICMod* NICModDestruct(NICMod* this) {
	printf("wenweiping  NICModDestruct....\n");
	return this;
}

//释放操作符

DeleteGen(NICMod)


/***
void NICModDelete(NICMod* this) {
	NICModDestruct(this);
	this->base.delete(this);
}
***/



struct _DiskMod;
typedef struct _DiskMod DiskMod;

void DiskMododDelete(DiskMod* this);


struct  _DiskMod {
	ModuleBase base;

	//void(*copyFromUser)(NICMod *this);
	//void(*copyToUser)(NICMod *this);

	void(*delete)(DiskMod* this);
	
};



void DiskModExit(DiskMod* this);
void DiskModDestruct(DiskMod* this);
void DiskModOnSwitchOpt(DiskMod* this, ModuleInerLogicOperation * newOpt, ModuleInerLogicOperation *oldOpt);
void DiskModOnAttachOpt(DiskMod *this);
void DiskModInit(DiskMod* this);

DiskMod * DiskModConstruct(DiskMod *this)
{
	ModuleBaseConstruct((ModuleBase*)this, MODULE_DISK, "disk_module");
	this->base.onAttachOpt = DiskModOnAttachOpt;
	this->base.onSwitchOpt = DiskModOnSwitchOpt;
	this->base.init = DiskModInit;
	this->base.exit = DiskModExit;

	//析构函数
	this->base.destrcut = NICModDestruct;
	//delete操作符
	this->delete = NICModDelete;

	return this;
}


void DiskModOnAttachOpt(DiskMod *this)
{
	printf("wenweiping  DiskModOnAttachOpt....\n");

}

void DiskModOnSwitchOpt(DiskMod* this, ModuleInerLogicOperation * newOpt, ModuleInerLogicOperation *oldOpt) {
	 

}

void DiskModExit(DiskMod* this) {
	printf("wenweiping  DiskModExit....\n");
}

void DiskModInit(DiskMod* this) {

	printf("wenweiping  DiskModInit....\n");

}



void DiskModDestruct(DiskMod* this) {

	printf("wenweiping  DiskModDestruct....\n");

}

DeleteGen(DiskMod)


//todo 后期优化 ModuleCtl ModContext 和 ModuleBase 的组织关系 解耦 通过索引
//todo 加入过滤器filter(继承模块的实现方式)，外置FilterModule ，形成
// 一个业务模块，可以定制注册 多个prefilter postfilter 
int main(int argc, const char *argvs[]) {

	ModuleCtl *modCtl = NEW(ModuleCtl);
	ModContext *ctx = NEW(ModContext);
	ctx->ctl = modCtl;

	DiskMod * d = NEW(DiskMod);
	NICMod * nic = NEW(NICMod);

	d->base.ctx = ctx;
	nic->base.ctx = ctx;

	ModuleCtlRegMod(modCtl, (ModuleBase*)d);
	ModuleCtlRegMod(modCtl, (ModuleBase*)nic);

	ModuleCtlPowerOnAll(modCtl);

	Sleep(3000);

	ModuleCtlPowerOffAll(modCtl);

	system("pause");

	return 0;
}