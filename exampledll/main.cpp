#include <windows.h>
#include <stdlib.h>

#define DLLAPI extern "C" __declspec(dllexport)

BOOL CALLBACK DllMain(HINSTANCE hModule, DWORD call, LPVOID lpReserved) {
	MessageBoxA(NULL, "Messagebox from inside DFO", "This is run from DFO memory", 48);

	return true;
}

DLLAPI DWORD CALLBACK PostLoadCallback(DWORD calldata1, DWORD calldata2,DWORD calldata3) {

	MessageBoxA(NULL, "Messagebox from inside DFO", "This is run from DFO memory", 48);

	return true;
}