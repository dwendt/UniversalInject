#include "main.h"
// Credit to the Chinese communities for much of the code in this file. 

// Handles loading the real target DLL
void injectDLL() {
	if(injectedDLL) return;

	MessageBox(0, TEXT("Injecting..."), TEXT("Going hard"), 0);

	injectedDLL = LoadLibrary(pathToInjectableDLL);

	if(!injectedDLL) { MessageBox(0, TEXT("Could not load injectable DLL at path."), pathToInjectableDLL, 0); return; }

	POSTINJECTIONCALLBACK goCallback = (POSTINJECTIONCALLBACK)GetProcAddress(injectedDLL, "PostLoadCallback");

	if(!goCallback) { MessageBox(0, TEXT("No postload callback..."), 0, 0); return; }

	goCallback(CallBackData1, CallBackData2, CallBackData3);	
}

BOOL CALLBACK DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	char tbuf[500] = "";

	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:

		GetModuleFileName(0, tbuf, 500);
		MessageBox(NULL, tbuf,TEXT("dllmain"), 0);
		WNDCLASSEX wc;

		wc.cbSize         = sizeof(WNDCLASSEX);
		wc.style          = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_IME;
		wc.lpfnWndProc    = UIWndProc;
		wc.cbClsExtra     = 0;
		wc.cbWndExtra     = 2 * sizeof(LONG);
		wc.hInstance      = hinstDLL;
		wc.hCursor        = NULL; //IDC_ARROW
		wc.hIcon          = NULL;
		wc.lpszMenuName   = (LPTSTR)NULL;
		wc.lpszClassName  = TEXT("UInjWindow");
		wc.hbrBackground  = NULL;
		wc.hIconSm        = NULL;

		if( !RegisterClassEx( (LPWNDCLASSEX)&wc ) )
			return FALSE;

//		if(injectedDLL == NULL)
//			injectDLL();

		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
//		MessageBox(0, TEXT("Unloading IME"), TEXT("Going hard"), 0);
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
	MessageBox(0,TEXT("selected :D"),0,0);
	if(injectedDLL == NULL)
		injectDLL();

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

BOOL WINAPI ImeConfigure(HKL hKL,HWND hWnd, DWORD dwMode, LPVOID lpData)
{
	MessageBox(0,TEXT("ImeConfigure :D"),0,0);
	switch (dwMode) {
	case IME_CONFIG_GENERAL:
		MessageBox(NULL,"UInject IME","UInject IME",48);
		break;
	default:
		return (FALSE);
		break;
	}
	return (TRUE);
}

// Note -- only ImeInquire is ever being run for some
BOOL WINAPI ImeInquire(LPIMEINFO lpIMEInfo,LPTSTR lpszUIClass,LPCTSTR lpszOption)
{
	MessageBox(0,TEXT("ImeInquire :D"),0,0);
	lpIMEInfo->dwPrivateDataSize = 0;

	lpIMEInfo->fdwProperty = IME_PROP_KBD_CHAR_FIRST | 
		IME_PROP_IGNORE_UPKEYS |
		IME_PROP_END_UNLOAD; 

	lpIMEInfo->fdwConversionCaps = IME_CMODE_FULLSHAPE |
		IME_CMODE_NATIVE;

	lpIMEInfo->fdwSentenceCaps = IME_SMODE_NONE;
	lpIMEInfo->fdwUICaps = UI_CAP_2700;

	lpIMEInfo->fdwSCSCaps = 0;

	lpIMEInfo->fdwSelectCaps = SELECT_CAP_CONVERSION;

	_tcscpy(lpszUIClass,"UInjWindow"); 

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




