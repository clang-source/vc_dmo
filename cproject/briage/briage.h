#ifndef __BRIAGE__H_
#define __BRIAGE__H_

struct _NetBase;
typedef struct _NetBase NetBase;

struct _DBBase;
typedef struct _DBBase DBBase;


struct _PackBase ;
typedef struct _PackBase PackBase;

struct _PackBase {
	int age;

};


struct _NetBase {
	void(*sendPack)(NetBase*this, PackBase* pack);
	void(*destruct)(NetBase* db);
};


struct _TcpNet;
typedef struct _TcpNet TcpNet;

struct _TcpNet {
	NetBase base;

};
struct _UdpNet;
typedef struct _UdpNet UdpNet;
struct _UdpNet {
	NetBase base;

};

struct _DBCommandBase;
typedef struct _DBCommandBase DBCommandBase;

struct _DBCommandBase {
	void* (*execute)(DBCommandBase* this);
	void(*destruct)(DBCommandBase* this);
};



struct _DBDeleteCmd {
	DBCommandBase base;
	char statement[0];

};


struct _DBBase {
	void(*syn)(DBBase* db, DBCommandBase *cmd);
	void(*destruct)(DBBase* db);
};


struct _MySqlDb;
typedef struct _MySqlDb MySqlDb;

struct _MySqlDb {
	 DBBase base;


};
struct _OracleDb;
typedef struct _OracleDb  OracleDb;

struct _OracleDb {
	DBBase base;
	
};


#endif // !__BRIAGE__H_

