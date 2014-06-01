#pragma region INCLUDES
#include "windows.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Shlobj.h"
#include "Imm.h"
#include <direct.h>
#pragma endregion
#include "resource.h"

#define IMENAME "UInject"
typedef int (CALLBACK * IMESetPubStringFunc) (LPCTSTR tmpStr, DWORD UnloadDLL, DWORD loadNextIme, DWORD DllData1, DWORD DllData2, DWORD DllData3);

class IMEInjector {
public:
	IMEInjector(HWND processID, char *dllpath);
	~IMEInjector();

	void runInject();

	BOOL FileExists(LPCTSTR szPath);
	void copy(std::ifstream &infile, std::ofstream &outfile);
	void removeIME(HKL installRes);
	HWND processID;
	char *dllpath;
	char windir[MAX_PATH];
};
