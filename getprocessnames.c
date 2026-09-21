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

#pragma comment(lib, "iphlpapi.lib")

DECLSPEC_IMPORT int WINAPI USER32$MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);


DECLSPEC_IMPORT DWORD WINAPI NETAPI32$DsGetDcNameA(LPCSTR, LPCSTR, PVOID, LPCSTR, ULONG, PDOMAIN_CONTROLLER_INFOA*);

DECLSPEC_IMPORT	BOOL WINAPI KERNEL32$GetComputerNameExA(COMPUTER_NAME_FORMAT, LPSTR, LPDWORD);
DECLSPEC_IMPORT	DWORD WINAPI KERNEL32$GetLastError();

DECLSPEC_IMPORT LPVOID WINAPI KERNEL32$VirtualAlloc(LPVOID, SIZE_T, DWORD, DWORD);
DECLSPEC_IMPORT BOOL WINAPI KERNEL32$VirtualFree(LPVOID, SIZE_T, DWORD);


DECLSPEC_IMPORT DWORD WINAPI NETAPI32$NetApiBufferFree(LPVOID);

DECLSPEC_IMPORT BOOL WINAPI ADVAPI32$GetUserNameA(LPSTR, LPDWORD);


DECLSPEC_IMPORT BOOL WINAPI KERNEL32$GetVersionExA(LPOSVERSIONINFOEXA);

DECLSPEC_IMPORT ULONG WINAPI IPHLPAPI$GetAdaptersAddresses(ULONG, ULONG, PVOID, PVOID, PULONG);

DECLSPEC_IMPORT CHAR* WINAPI WS2_32$inet_ntoa(in_addr);

DECLSPEC_IMPORT NTSTATUS WINAPI NTDLL$NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);


void go() {
	
	
	ULONG returnlength = 0;
	NTDLL$NtQuerySystemInformation(SystemProcessInformation, NULL, 0, &returnlength);

	if (returnlength == 0) { return; }

	LPVOID base = KERNEL32$VirtualAlloc(NULL, returnlength, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (base == NULL) { return; }


	NTSTATUS res = NTDLL$NtQuerySystemInformation(SystemProcessInformation, base, returnlength, &returnlength);
	if (res == 0) {


		SYSTEM_PROCESS_INFORMATION* firstprocess = (SYSTEM_PROCESS_INFORMATION*)base;

		while (TRUE) {

			BeaconPrintf(CALLBACK_OUTPUT, "Process Id: %d\n", firstprocess->UniqueProcessId);

			BeaconPrintf(CALLBACK_OUTPUT_UTF8, "Process image name: %ls\n",
				firstprocess->ImageName.Buffer);



			if (firstprocess->NextEntryOffset == 0) {
				break;
			}


			firstprocess = (PSYSTEM_PROCESS_INFORMATION)((char*)firstprocess + firstprocess->NextEntryOffset);

		}


	}


	KERNEL32$VirtualFree(base, 0, MEM_RELEASE);

}



