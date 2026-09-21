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

void go() {
	
	


	LPVOID base = KERNEL32$VirtualAlloc(NULL, 15*1024, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (base == NULL) { return; }


	ULONG size = 15 * 1024;
	ULONG res = IPHLPAPI$GetAdaptersAddresses(AF_INET, 0x0010| 0x0080, NULL, base, &size);
	if (res == ERROR_SUCCESS) {

		PIP_ADAPTER_ADDRESSES_LH firstadapter = (PIP_ADAPTER_ADDRESSES_LH)base;

		while (firstadapter) {

			BeaconPrintf(CALLBACK_OUTPUT_UTF8, "Friendly Name: %ls\n", firstadapter->FriendlyName);
			BeaconPrintf(CALLBACK_OUTPUT, "Adapter Name: %s\n", firstadapter->AdapterName);
			BeaconPrintf(CALLBACK_OUTPUT_UTF8, "Description: %ls\n", firstadapter->Description);



			PIP_ADAPTER_UNICAST_ADDRESS_LH firstunicast = (PIP_ADAPTER_UNICAST_ADDRESS_LH)firstadapter->FirstUnicastAddress;
			while (firstunicast) {

				if (firstunicast->Address.lpSockaddr &&
					firstunicast->Address.lpSockaddr->sa_family == AF_INET) {

					SOCKADDR_IN* in = (SOCKADDR_IN*)firstunicast->Address.lpSockaddr;

					char* ip = WS2_32$inet_ntoa(in->sin_addr);
					if (ip) {
						BeaconPrintf(CALLBACK_OUTPUT, "IP Address: %s/%d\n", ip,
							firstunicast->OnLinkPrefixLength);
					}


				}


				firstunicast = firstunicast->Next;
			}



			PIP_ADAPTER_GATEWAY_ADDRESS_LH firstgateway = (PIP_ADAPTER_GATEWAY_ADDRESS_LH)firstadapter->FirstGatewayAddress;
			while (firstgateway) {

				if (firstgateway->Address.lpSockaddr &&
					firstgateway->Address.lpSockaddr->sa_family == AF_INET) {

					SOCKADDR_IN* in = (SOCKADDR_IN*)firstgateway->Address.lpSockaddr;

					char* ip = WS2_32$inet_ntoa(in->sin_addr);
					if (ip) {
						BeaconPrintf(CALLBACK_OUTPUT, "Gateway Address: %s\n", ip);
					}


				}


				firstgateway = firstgateway->Next;
			}


			PIP_ADAPTER_DNS_SERVER_ADDRESS_XP firstdns = (PIP_ADAPTER_DNS_SERVER_ADDRESS_XP)firstadapter->FirstDnsServerAddress;
			while (firstdns) {

				if (firstdns->Address.lpSockaddr &&
					firstdns->Address.lpSockaddr->sa_family == AF_INET) {

					SOCKADDR_IN* in = (SOCKADDR_IN*)firstdns->Address.lpSockaddr;

					char* ip = WS2_32$inet_ntoa(in->sin_addr);
					if (ip) {
						BeaconPrintf(CALLBACK_OUTPUT, "DNS Address: %s\n", ip);
					}


				}


				firstdns = firstdns->Next;
			}





			BeaconPrintf(CALLBACK_OUTPUT, "\n");
			firstadapter = firstadapter->Next;

		}


	}


	KERNEL32$VirtualFree(base, 0, MEM_RELEASE);

}



