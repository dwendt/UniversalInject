#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "imm.h"
#include <tchar.h>
#pragma comment(lib,"imm32.lib")
// Credit to the Chinese communities for much of the code in this file. 

// Shared code segment. If this DLL is loaded into any process, 
// this segment of code will point to the same physical memory in each of those processes. (...on the next episode of My Little DLL: Windows Is Magic)
#pragma data_seg(".shared")
DWORD CallBackData1=0;
DWORD CallBackData2=0;
DWORD CallBackData3=0;

DWORD UnloadDllWhenExit=0;   // Unload the injected DLL on IME exit?
DWORD LoadNextWhenActive=0;  // Go to the next IME if this IME is made active
char pathToInjectableDLL[MAX_PATH]=""; // Full path to the injectable DLL
#pragma data_seg()
#pragma comment(linker,"/section:.shared,RWS")   

#pragma region defines
typedef DWORD (CALLBACK * POSTINJECTIONCALLBACK)(DWORD calldata1, DWORD calldata2,DWORD calldata3);

// Handle to the injected DLL, and a pointer to the function to be called after injection(for giving the DLL extra data).
HMODULE injectedDLL = NULL;
POSTINJECTIONCALLBACK postInjectionCallback = NULL;

BOOL ImeClass_Register(HINSTANCE hInstance);
void ImeClass_Unregister(HINSTANCE hInstance);

BOOL syncPostMessage(HIMC hIMC, UINT msg, WPARAM wParam, LPARAM lParam);

// The IME window doesn't need to do anything.
LRESULT WINAPI UIWndProc(HWND hUIWnd,UINT message,WPARAM wParam,LPARAM lParam) { return 0; }
LRESULT WINAPI StatusWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) { return 0; }
LRESULT WINAPI CompWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) { return 0; }
LRESULT WINAPI CandWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) { return 0; }

// Necessary IME exports
UINT WINAPI ImeEnumRegisterWord(REGISTERWORDENUMPROC lpfnRegisterWordEnumProc, LPCTSTR lpszReading, DWORD dwStyle, LPCTSTR lpszString, LPVOID lpData) { return 0; }
UINT WINAPI ImeGetRegisterWordStyle(UINT nItem, LPSTYLEBUF lpStyleBuf) { return 0; }
BOOL WINAPI ImeRegisterWord(LPCTSTR lpszReading, DWORD dwStyle, LPCTSTR lpszString) { return 0; }
BOOL WINAPI ImeUnregisterWord(LPCTSTR lpszReading, DWORD dwStyle, LPCTSTR lpszString) { return 0; }
BOOL WINAPI NotifyIME(HIMC hIMC,DWORD dwAction,DWORD dwIndex,DWORD dwValue) { return 0; }
UINT WINAPI ImeToAsciiEx (UINT uVKey,UINT uScanCode,CONST LPBYTE lpbKeyState,LPDWORD lpdwTransKey,UINT fuState,HIMC hIMC) { return 0; }
BOOL WINAPI ImeSetCompositionString(HIMC hIMC, DWORD dwIndex, LPCVOID lpComp, DWORD dwComp, LPCVOID lpRead, DWORD dwRead) { return 0; }
BOOL WINAPI ImeProcessKey(HIMC hIMC,UINT uKey,LPARAM lKeyData,CONST LPBYTE lpbKeyState) { return 0; }
LRESULT WINAPI ImeEscape(HIMC hIMC,UINT uSubFunc,LPVOID lpData) { return 0; }
DWORD WINAPI ImeConversionList(HIMC hIMC,LPCTSTR lpSource,LPCANDIDATELIST lpCandList,DWORD dwBufLen,UINT uFlag) { return 0; }
BOOL WINAPI ImeDestroy(UINT uForce) { return (uForce ? TRUE : 0); }
BOOL WINAPI ImeSetActiveContext(HIMC hIMC,BOOL fFlag) { return TRUE; }
#pragma endregion

// Handles loading the real target DLL
void injectDLL() {
	if(injectedDLL) return;

	MessageBox(0, TEXT("We would be injecting now..."), TEXT("Going hard"), 0);

	injectedDLL = LoadLibrary(pathToInjectableDLL);

	if(!injectedDLL) { MessageBox(0, TEXT("Could not load injectable DLL at that path."), TEXT("Going hard"), 0); return; }

	POSTINJECTIONCALLBACK goCallback = (POSTINJECTIONCALLBACK)GetProcAddress(injectedDLL, "PostLoadCallback");

	if(!goCallback) { MessageBox(0, TEXT("No postload callback..."), 0, 0); return; }

	goCallback(CallBackData1, CallBackData2, CallBackData3);	
}

BOOL CALLBACK DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		WNDCLASSEX wc;

		wc.cbSize         = sizeof(WNDCLASSEX);
		wc.style          = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_IME;
		wc.lpfnWndProc    = UIWndProc;
		wc.cbClsExtra     = 0;
		wc.cbWndExtra     = 2 * sizeof(LONG);
		wc.hInstance      = hinstDLL;
		wc.hCursor        = LoadCursor( NULL, IDC_ARROW );
		wc.hIcon          = NULL;
		wc.lpszMenuName   = (LPTSTR)NULL;
		wc.lpszClassName  = "UInjWindow";
		wc.hbrBackground  = NULL;
		wc.hIconSm        = NULL;

		if( !RegisterClassEx( (LPWNDCLASSEX)&wc ) )
			return FALSE;

		if(injectedDLL == NULL)
			injectDLL();

		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		MessageBox(0, TEXT("Unloading IME"), TEXT("Going hard"), 0);
		UnregisterClass("UInjWindow",hinstDLL);

		if (injectedDLL != NULL && UnloadDllWhenExit != 0 )
		{
			FreeLibrary(injectedDLL);
		}
		break;
	default:
		break;
	}
	return true;
}

int WINAPI IMESetPubString(LPCTSTR tmpStr,DWORD UnloadDLL,DWORD loadNextIme,DWORD DllData1,DWORD DllData2,DWORD DllData3)
{
	CallBackData1=DllData1;
	CallBackData2=DllData2;
	CallBackData3=DllData3;
	UnloadDllWhenExit=UnloadDLL;
	LoadNextWhenActive=loadNextIme;

	memset(pathToInjectableDLL,0,MAX_PATH);
	if (lstrlen(tmpStr)>MAX_PATH)
	{
		lstrcpyn(pathToInjectableDLL,tmpStr,MAX_PATH);
	}
	else
	{
		lstrcpy(pathToInjectableDLL,tmpStr);
	}
	return 1;
}

int WINAPI IMEClearPubString()
{
	CallBackData1=0;
	CallBackData2=0;
	CallBackData3=0;
	UnloadDllWhenExit=0;
	LoadNextWhenActive=0;

	memset(pathToInjectableDLL,0,802);
	return 1;
}


BOOL WINAPI ImeSelect(HIMC hIMC,BOOL fSelect)
{
//	injectDLL();

	if (!hIMC) {
		return (FALSE);
	}
	if (fSelect==TRUE && LoadNextWhenActive != 0)
	{
		//ActivateKeyboardLayout((HKL)HKL_NEXT,0);
		syncPostMessage(hIMC,WM_INPUTLANGCHANGEREQUEST,1,(LPARAM)HKL_NEXT);
	}
	return TRUE;
}



BOOL syncPostMessage(HIMC hIMC, UINT msg, WPARAM wParam, LPARAM lParam) {
	BOOL bRet = FALSE;

	LPINPUTCONTEXT lpIMC = ImmLockIMC(hIMC);
	if(lpIMC == NULL) return 0;

	if(IsWindow(lpIMC->hWnd)) {
		PostMessage(lpIMC->hWnd, msg, wParam, lParam);
		bRet = TRUE;
	}

	return bRet;
}




