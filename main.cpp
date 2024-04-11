#include <iostream>
#include <Windows.h>
#include <libloaderapi.h>
#include "proc.h"

int main()
{
	DWORD pId = 0;
	HANDLE hProc;
	LPVOID lpBaseAddress;

	const char* dllPath;
	size_t dllSize = 0;


	dllPath = ""; // Place DLL path in strings      Example: "C:\\User\\test.dll"
    dllSize = strlen(dllPath);

	pId = GetProcId(L"Injector.exe"); // Name of EXE of the process you want to inject into

    hProc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pId);
    lpBaseAddress = VirtualAllocEx(hProc, NULL, dllSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(hProc, lpBaseAddress, dllPath, dllSize, NULL);

    HMODULE hModule = GetModuleHandle(L"kernel32.dll");
    LPVOID lpStartAddress = GetProcAddress(hModule, "LoadLibraryA");

    HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)lpStartAddress, lpBaseAddress, 0, NULL);
    if (hThread)
    {
        printf("DLL Injected. . . . .\n");
    }
    else
    {
        printf("DLL Injection Failed. . . . .\n");
    }

	getchar();
}