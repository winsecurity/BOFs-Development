// boftest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// cl.exe /c /nologo /O2 /GS- boftest.c /Fo:boftest2.obj


#include <Windows.h>
#include "beacon.h"
#include <DsGetDC.h>
#include <iphlpapi.h>
#include <iptypes.h>
#include <winternl.h>

#include "definitions.h"


DECLSPEC_IMPORT int WINAPI USER32$MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);


DECLSPEC_IMPORT DWORD WINAPI NETAPI32$DsGetDcNameA(LPCSTR, LPCSTR, PVOID, LPCSTR, ULONG, PDOMAIN_CONTROLLER_INFOA*);

DECLSPEC_IMPORT	BOOL WINAPI KERNEL32$GetComputerNameExA(COMPUTER_NAME_FORMAT, LPSTR, LPDWORD);
DECLSPEC_IMPORT	DWORD WINAPI KERNEL32$GetLastError();

DECLSPEC_IMPORT LPVOID WINAPI KERNEL32$VirtualAlloc(LPVOID, SIZE_T, DWORD, DWORD);
DECLSPEC_IMPORT BOOL WINAPI KERNEL32$VirtualFree(LPVOID, SIZE_T, DWORD);


DECLSPEC_IMPORT DWORD WINAPI NETAPI32$NetApiBufferFree(LPVOID);

DECLSPEC_IMPORT BOOL WINAPI ADVAPI32$GetUserNameA(LPSTR, LPDWORD);


DECLSPEC_IMPORT BOOL WINAPI KERNEL32$GetVersionExA(LPOSVERSIONINFOEXA);


DECLSPEC_IMPORT CHAR* WINAPI WS2_32$inet_ntoa(in_addr);

DECLSPEC_IMPORT NTSTATUS WINAPI NTDLL$NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);


DECLSPEC_IMPORT ULONG WINAPI IPHLPAPI$GetAdaptersAddresses(ULONG, ULONG, PVOID, PVOID, PULONG);


DECLSPEC_IMPORT BOOL WINAPI USER32$OpenClipboard(HWND);
DECLSPEC_IMPORT BOOL WINAPI USER32$CloseClipboard();
DECLSPEC_IMPORT HANDLE WINAPI USER32$GetClipboardData(UINT);


void go() {
	
	
	LPVOID base= KERNEL32$VirtualAlloc(NULL, 128, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (base == NULL) { return; }
	
	DWORD size = 128;
	BOOL res = ADVAPI32$GetUserNameA(base, &size);
	if (res != 0) {
		BeaconPrintf(CALLBACK_OUTPUT, "Username: %s\n", base);
	}

	KERNEL32$VirtualFree(base, 0, MEM_RELEASE);

}



