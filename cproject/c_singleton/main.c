#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment(lib,"ntdll.lib")

void NTAPI __stdcall TLS_CALLBACK(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
	printf("I am premain xxxxx Reason=%d\n", Reason);
}

//linker spec通知链接器PE文件要创建TLS目录，注意X86和X64的区别
#ifdef _M_IX86
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:__tls_callback")
#else
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback")
#endif
//创建TLS段
EXTERN_C
#ifdef _M_X64
#pragma const_seg (".CRT$XLB")
const
#else
#pragma data_seg (".CRT$XLB")
#endif
//end linker

//tls import定义多个回调函数
PIMAGE_TLS_CALLBACK    _tls_callback[] = { TLS_CALLBACK, 0 };
#pragma data_seg ()
#pragma const_seg ()
//end 


void callFun2() {
	printf("callFun2....");
	exit(0);
}


void callFun() {
	callFun2();
	
}


int catchExit(void) {
	printf("catchExit.....\n");
	return 0;
}

int main()
{
 
	atexit(catchExit);
	callFun();

	printf("I am in main will exit\n");
	 
	return 0;

}