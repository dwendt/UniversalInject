#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "imm.h"
#include <tchar.h>
#pragma comment(lib,"imm32.lib")

// Shared code segment. If this DLL is loaded into any process, 
// this segment of code will point to the same physical memory in each of those processes. (...on the next episode of My Little DLL: Windows Is Magic)
#pragma data_seg(".shared")
DWORD CallBackData1=0;
DWORD CallBackData2=0;
DWORD CallBackData3=0;

DWORD UnloadDllWhenExit=0;   // Unload the injected DLL on IME exit?
DWORD LoadNextWhenActive=0;  // Go to the next IME if this IME is made active
char pathToInjectableDLL[MAX_PATH]="C:\\inject.dll"; // Full path to the injectable DLL
#pragma data_seg()
#pragma comment(linker,"/section:.shared,RWS")   

// Callback to call after the IME injects something
typedef DWORD (CALLBACK * POSTINJECTIONCALLBACK)(DWORD calldata1, DWORD calldata2,DWORD calldata3);

// Posts messages safely.
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

// Handle to the injected DLL, and a pointer to the function to be called after injection(for giving the DLL extra data).
HMODULE injectedDLL = NULL;
POSTINJECTIONCALLBACK postInjectionCallback = NULL;