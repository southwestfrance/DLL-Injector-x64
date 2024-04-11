#ifndef _PROC
#define _PROC

#include <windows.h>
#include <TlHelp32.h>

DWORD GetProcId(const wchar_t* procName);

#endif 