// TLS_test.cpp: 定义控制台应用程序的入口点。
//
/*
TLS回调函数中第二个参数决定了函数在那种情况下（DllMain函数一样）被调用：

DLL_PROCESS_ATTACH：是指新进程创建时，初始化主线程时执行。
DLL_PROCESS_DETACH：是指在进程终止时执行。
DLL_THREAD_ATTACH：是指创建新线程时，但是不包括主线程。
DLL_THREAD_DETACH：是指在所有线程终止时执行，但是同样不包括主线程。
*/
#include "stdafx.h"
#include<Windows.h>

#ifdef _WIN64
#pragma comment(linker,"/INCLUDE:_tls_used")
#else
#pragma comment(linker,"/INCLUDE:__tls_used")
#endif // _WIN64

void NTAPI TlsCallBac(PVOID h, DWORD dwReason, PVOID pv);

extern "C"
#ifdef _WIN64
#pragma const_seg(".CRT$XLX")
	const
#else
#pragma data_seg(".CRT$XLX")
#endif
	PIMAGE_TLS_CALLBACK p_thread_callback[] = { TlsCallBac,0 };
#ifdef _WIN64
#pragma const_seg()
#else
#pragma data_seg()
#endif // _WIN64

void NTAPI TlsCallBac(PVOID h, DWORD dwReason, PVOID pv)
{
	MessageBoxA(NULL, "In TLS", "In TLS", MB_OK);
	return;
}

int main()
{
	printf("hello world");
	system("pause");
	return 0;
}
