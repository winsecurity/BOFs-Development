// boftest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <Windows.h>
#include "beacon.h"
#include <DsGetDC.h>

DECLSPEC_IMPORT int WINAPI USER32$MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);


DECLSPEC_IMPORT DWORD WINAPI NETAPI32$DsGetDcNameA(LPCSTR, LPCSTR, PVOID, LPCSTR, ULONG, PDOMAIN_CONTROLLER_INFOA*);

DECLSPEC_IMPORT	BOOL WINAPI KERNEL32$GetComputerNameExA(COMPUTER_NAME_FORMAT, LPSTR, LPDWORD);
DECLSPEC_IMPORT	DWORD WINAPI KERNEL32$GetLastError();

DECLSPEC_IMPORT LPVOID WINAPI KERNEL32$VirtualAlloc(LPVOID, SIZE_T, DWORD, DWORD);
DECLSPEC_IMPORT BOOL WINAPI KERNEL32$VirtualFree(LPVOID, SIZE_T, DWORD);


DECLSPEC_IMPORT DWORD WINAPI NETAPI32$NetApiBufferFree(LPVOID);

void go() {
	
	PDOMAIN_CONTROLLER_INFOA infoa = NULL;
	DWORD res = NETAPI32$DsGetDcNameA(NULL, NULL, NULL, NULL, DS_DIRECTORY_SERVICE_PREFERRED, &infoa);

	if (res == ERROR_SUCCESS) {
		BeaconPrintf(CALLBACK_OUTPUT, "Dc name: %s\n", infoa->DomainControllerName);
		BeaconPrintf(CALLBACK_OUTPUT, "Forest name: %s\n", infoa->DnsForestName);
		BeaconPrintf(CALLBACK_OUTPUT, "Dc address: %s\n", infoa->DomainControllerAddress);
	}

	if (infoa) {
		NETAPI32$NetApiBufferFree(infoa);
	}




}



