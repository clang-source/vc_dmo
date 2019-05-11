#include "base.h"
#include "briage.h"


struct _DBModule;

typedef struct _DBModule DBModule;
static void DBModuleSetImpl(DBModule* this, NetBase * net, DBBase *  db);
struct _DBModule {
	NetBase * net;
	DBBase *  db;

	//DBDeleteCmd *deleteCmdList;
	//DBUpdateCmd *updateCmdList;
	//DBQueryCmd * queryCmdList;
	//DBCreateCmd *createCmdList;

};


DBModule * DBModuleConstruct(DBModule* this, NetBase * net, DBBase *  db) {
	DBModuleSetImpl(this,net,db);
	return this;
}
static void DBModuleSetImpl(DBModule* this, NetBase * net, DBBase *  db) {
	this->db = db;
	this->net = net;
}
void DBModuleDestruct(DBModule* this) {
	//this->net.Release();
	//this->db.Release();Ïß³Ì¾ºÕù£¬atomic
}

static int DBModuleConnect(DBModule* this){

	return 0;
}

static void DBModulePollMsg(DBModule* this) {

}

static void DBModuleSyn(DBModule* this) {
	//this->db->syn(this->db,)
}




int main(int argc, const char *argvs[]) {
	NetBase * tcpNet =NEW(TcpNet);
	DBBase *  odb = NEW(OracleDb);

	DBModule * dbm = NEW(DBModule, tcpNet, odb);

	DBModuleConnect(dbm);
	DBModuleSyn(dbm);

	NetBase * udpNet = NEW(UdpNet);
	DBBase *  mysqldb = NEW(MySqlDb);

	DBModuleSetImpl(dbm, udpNet, mysqldb);

	return 0;
}

