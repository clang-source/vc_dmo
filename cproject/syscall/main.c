 
#include <stdio.h>
#include <stdlib.h>

#define SYS_init 0
#define SYS_socket  1
#define SYS_connect 2
#define SYS_bind	   3
#define SYS_listen  4
#define SYS_accept  5
#define SYS_gethostname  6





static int  sys_socket_socket(int af_inet,int family) {
	printf("sys_socket_socket,af_inet=%d , family=%d \n", af_inet, family);


	return 0;
}


static int sys_socket_connect(int fd,int ip,int port) {
	printf("sys_socket_connect,ip=%d , port=%d \n", ip, port);

	return 0;
}


static int sys_socket_bind() {

	return 0;
}

static int sys_socket_listen() {

	return 0;
}

static int sys_socket_accept() {

	return 0;
}

static int sys_socket_gethostname() {


	return 0;
}


//宏是下沉为编译期间代码的，动态传递的产生和它有冲突，除非 传递的参数是，编译期间可以确定的参数，否则会有冲突现象
#define sys_socket_calls(sockOpt,...)\
	 sys_socket_##sockOpt(##__VA_ARGS__##)

int main(int argc, const char *argvs[]) {
	//kernel_init();

	
	int fd = sys_socket_calls(socket,12,212);
	int res= sys_socket_calls(connect,fd, 1111, 2222);
	 

	system("pause");

	return 0;
}