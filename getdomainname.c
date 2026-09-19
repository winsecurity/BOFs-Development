// boftest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// COMPILE USING
// cl.exe /c /nologo /O2 /GS- boftest.c /Fo:boftest2.obj

#include <Windows.h>
#include "beacon.h"


DECLSPEC_IMPORT int WINAPI USER32$MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);


DECLSPEC_IMPORT	BOOL WINAPI KERNEL32$GetComputerNameExA(COMPUTER_NAME_FORMAT, LPSTR, LPDWORD);
DECLSPEC_IMPORT	DWORD WINAPI KERNEL32$GetLastError();

DECLSPEC_IMPORT LPVOID WINAPI KERNEL32$VirtualAlloc(LPVOID, SIZE_T, DWORD, DWORD);
DECLSPEC_IMPORT BOOL WINAPI KERNEL32$VirtualFree(LPVOID, SIZE_T, DWORD);


void go() {
	
	LPVOID base = KERNEL32$VirtualAlloc(NULL, 64, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (base) {

		DWORD size = 64;
		BOOL res = KERNEL32$GetComputerNameExA(ComputerNameDnsDomain, (LPSTR)base, &size);
		if (res != 0) {
			BeaconPrintf(CALLBACK_OUTPUT, "Domain name: %s", (char*)base);
		}


		KERNEL32$VirtualFree(base, 0, MEM_RELEASE);
	}




}



