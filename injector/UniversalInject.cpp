// POC IME injector. designed for 7 x64. based off RE work on the SUPER-EC EasyLanguage library.

#pragma region NOTES
//notes
//hooked chinese program, on installation of keyboard calls:
/*
#	TID	Module	API	Return	Error
10982	7668	DFO-Cn.exe	CreateFileA ( "C:\Windows\system32\\SouGoo.ime", GENERIC_WRITE, 0, 0x0018f1f8, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL )	0x00000510	
10983	7668	DFO-Cn.exe	WriteFile ( 0x00000510, 0x004aeb58, 81920, 0x0018f214, NULL )	TRUE	
10984	7668	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
10985	7668	DFO-Cn.exe	GetProcAddress ( 0x747e0000, "LoadLibraryA" )	0x747f49a7	
10986	7668	DFO-Cn.exe	LoadLibraryA ( "imm32.dll" )	0x75e40000	
10987	7668	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
10988	7668	DFO-Cn.exe	GetProcAddress ( 0x747e0000, "GetProcAddress" )	0x747f1222	
10989	7668	DFO-Cn.exe	GetProcAddress ( 0x75e40000, "ImmInstallIMEA" )	0x75e5af74	
10990	7668	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
10991	7668	DFO-Cn.exe	GetProcAddress ( 0x747e0000, "lstrcpyn" )	0x748018fa	
10992	7668	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
10993	7668	DFO-Cn.exe	GetProcAddress ( 0x747e0000, "CallWindowProcA" )	NULL	127 = The specified procedure could not be found. 
10994	7668	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
10995	7668	DFO-Cn.exe	GetProcAddress ( 0x74750000, "CallWindowProcA" )	NULL	127 = The specified procedure could not be found. 
10996	7668	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
10997	7668	DFO-Cn.exe	GetProcAddress ( 0x76310000, "CallWindowProcA" )	0x7633792f	
10998	7668	DFO-Cn.exe	CallWindowProcA ( 0x005b44ef, 0x10045fe0, 8364968, 2, 0 )	-534312956	
10999	7668	DFO-Cn.exe	ImmInstallIMEA ( "C:\Windows\system32\\SouGoo.ime", "DFO - Cn" )	0xe0270804	
11000	7668	IMM32.DLL	LoadLibraryW ( "version.dll" )	0x744b0000	
11001	7668	IMM32.DLL	GetProcAddress ( 0x744b0000, "GetFileVersionInfoW" )	0x744b19f4	
11002	7668	IMM32.DLL	GetProcAddress ( 0x744b0000, "GetFileVersionInfoSizeW" )	0x744b19d9	
11003	7668	IMM32.DLL	GetProcAddress ( 0x744b0000, "VerQueryValueW" )	0x744b1b51	
11004	7668	VERSION.dll	LoadLibraryExW ( "C:\Windows\system32\SOUGOO.IME", NULL, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE )	0x020a0002	
11005	7668	VERSION.dll	LoadLibraryExW ( "C:\Windows\system32\SOUGOO.IME", NULL, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE )	0x020a0002	
11006	7668	IMM32.DLL	LoadKeyboardLayoutW ( "E0270804", 16 )	0xe0270804	
11007	7668	USER32.dll	LoadLibraryW ( "kbdus.dll" )	0x6ba90000	
11008	7668	USER32.dll	GetProcAddress ( 0x6ba90000, 3 )	NULL	182 = The operating system cannot run %1. 
11009	7668	USER32.dll	GetProcAddress ( 0x6ba90000, 5 )	NULL	182 = The operating system cannot run %1. 
11010	7668	USER32.dll	GetProcAddress ( 0x6ba90000, 6 )	NULL	182 = The operating system cannot run %1. 
11011	7668	USER32.dll	GetProcAddress ( 0x6ba90000, 1 )	0x6ba91d24	
11012	7668	USER32.dll	GetProcAddress ( 0x6ba90000, 2 )	NULL	182 = The operating system cannot run %1. 
11013	7668	USER32.dll	CreateFileW ( "C:\Windows\system32\kbdus.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL )	0x00000534	
11014	7668	IMM32.DLL	LoadLibraryW ( "version.dll" )	0x744b0000	
11015	7668	IMM32.DLL	GetProcAddress ( 0x744b0000, "GetFileVersionInfoW" )		
11016	7668	IMM32.DLL	GetProcAddress ( 0x744b0000, "GetFileVersionInfoSizeW" )	0x744b19d9	
11017	7668	IMM32.DLL	GetProcAddress ( 0x744b0000, "VerQueryValueW" )	0x744b1b51	
11018	7668	VERSION.dll	LoadLibraryExW ( "C:\Windows\system32\SOUGOO.IME", NULL, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE )	0x020a0002	
11019	7668	VERSION.dll	LoadLibraryExW ( "C:\Windows\system32\SOUGOO.IME", NULL, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE )	0x020a0002	
11020	7668	DFO-Cn.exe	CreateFileA ( "C:\Windows\system32\\dfocn.dll", GENERIC_WRITE, 0, 0x0018f1f8, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL )	0x00000534	
11021	7668	DFO-Cn.exe	WriteFile ( 0x00000534, 0x004c2b74, 987136, 0x0018f214, NULL )	TRUE	
11022	7668	DFO-Cn.exe	LoadLibraryA ( "C:\Windows\system32\\Sougoo.ime" )	0x020a0000	
11023	7668	DFO-Cn.exe	GetProcAddress ( 0x020a0000, "IMESetPubString" )	0x020a10c0	
11024	7668	DFO-Cn.exe	CallWindowProcA ( 0x005b44ef, 0x020a10c0, 103622384, 6, 0 )	1	
11025	7668	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
11026	7668	DFO-Cn.exe	GetProcAddress ( 0x747e0000, "MessageBoxA" )	NULL	127 = The specified procedure could not be found. 
11027	7668	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
11028	7668	DFO-Cn.exe	GetProcAddress ( 0x74750000, "MessageBoxA" )	NULL	127 = The specified procedure could not be found. 
11029	7668	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
11030	7668	DFO-Cn.exe	GetProcAddress ( 0x76310000, "MessageBoxA" )	0x7637fd1e	
	
*/

//on uninstallation of keyboard:
/*
#	TID	Module	API	Return	Error
2540	5128	DFO-Cn.exe	LoadLibraryA ( "C:\Windows\system32\\Sougoo.ime" )	0x02430000	
2541	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2542	5128	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
2543	5128	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
2544	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2545	5128	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
2546	5128	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
2547	5128	DFO-Cn.exe	GetKeyboardLayout ( 0 )	0x04090409	
2548	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2549	5128	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
2550	5128	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
2551	5128	DFO-Cn.exe	ActivateKeyboardLayout ( 0xe0270804, 0 )	0x04090409	
2552	5128	IMM32.DLL	GetKeyboardLayout ( 0 )	0x04090409	
2553	5128	IMM32.DLL	GetKeyboardLayout ( 0 )	0x04090409	
2554	5128	MSCTF.dll	ImmGetDefaultIMEWnd ( NULL )	0x001018a6	
2555	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2556	5128	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
2557	5128	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
2558	5128	DFO-Cn.exe	GetKeyboardLayoutNameA ( "        " )	TRUE	
2559	5128	DFO-Cn.exe	ActivateKeyboardLayout ( 0x04090409, 0 )	0xe0270804	
2560	5128	IMM32.DLL	GetKeyboardLayout ( 0 )	0xe0270804	
2561	5128	MSCTF.dll	ImmGetConversionStatus ( 0x06902a41, 0x0018ebcc, 0x0018ebc8 )	TRUE	
2562	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2563	5128	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
2564	5128	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
2565	5128	DFO-Cn.exe	UnloadKeyboardLayout ( 0xe0270804 )	TRUE	
2566	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2567	5128	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
2568	5128	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
2569	5128	DFO-Cn.exe	LoadLibraryA ( "Advapi32.dll" )	0x74a10000	
2570	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2571	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2572	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2573	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2574	5128	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
2575	5128	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
2576	5128	DFO-Cn.exe	LoadKeyboardLayoutA ( "00000804", 8 )	0x08040804	
2577	5128	DFO-Cn.exe	LoadKeyboardLayoutA ( "00000411", 8 )	0x04110411	
2578	5128	DFO-Cn.exe	LoadKeyboardLayoutA ( "d0010409", 8 )	0x04090409	
2579	5128	DFO-Cn.exe	LoadKeyboardLayoutA ( "00000409", 8 )	0x04090409	
2580	5128	DFO-Cn.exe	LoadLibraryA ( "Kernel32.dll" )	0x747e0000	
2581	5128	DFO-Cn.exe	LoadLibraryA ( "Gdi32.dll" )	0x74750000	
2582	5128	DFO-Cn.exe	LoadLibraryA ( "User32.dll" )	0x76310000	
*/
#pragma endregion

#include "UniversalInject.h"

IMEInjector::IMEInjector(HWND ID, char *path){
	this->processID = ID;
	this->dllpath = path;
};

IMEInjector::~IMEInjector() {

};

BOOL IMEInjector::FileExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void IMEInjector::copy(std::ifstream &infile, std::ofstream &outfile) {
	char * buffer;
	long size;

	// get size of file
	infile.seekg(0,std::ifstream::end);
	size=infile.tellg();
	if(!size) { 
		MessageBox(0, TEXT("Failed to get size of file to copy"), 0, 0);
		infile.close();
		return;
	}
	infile.seekg(0);

	// allocate memory for file content
	buffer = new char [size];

	// read content of infile
	infile.read (buffer,size);

	// write to outfile
	outfile.write (buffer,size);

	// release dynamically-allocated memory
	delete[] buffer;

	outfile.close();
	infile.close();
};

void IMEInjector::runInject() {
	PVOID OldValue = NULL;

	SHGetSpecialFolderPathA(0, windir, CSIDL_SYSTEM, FALSE);	
	
	std::string syspath(windir);
	std::string loadpath(dllpath);
	std::string imename(IMENAME);

	std::string imecopydestination = (syspath + "\\") + (imename + ".ime");
	std::string dllcopydestination = (syspath + "\\") + (imename + ".tmp");

	std::ifstream dllcopyfrom (loadpath,std::fstream::binary);
	std::ofstream dllcopyto (dllcopydestination,std::fstream::trunc|std::fstream::binary);
 
	if(!FileExists(loadpath.c_str())) {
		MessageBox(0, TEXT("Target DLL to inject does not exist"), loadpath.c_str(), 0);
	}
	copy(dllcopyfrom, dllcopyto);


	FILE *fp_writeime;
	fp_writeime = fopen(imecopydestination.c_str(), "wb");

	HRSRC hIMEResource = FindResource(NULL, MAKEINTRESOURCE(IDR_BINARY1), RT_RCDATA);
	DWORD tempErr = GetLastError();

	HGLOBAL hGlobal = LoadResource(NULL, hIMEResource);

	BYTE* pimeinmem = (BYTE*)LockResource(hGlobal);
	int size = SizeofResource(NULL, hIMEResource);


	fwrite(pimeinmem, size*sizeof(BYTE), 1, fp_writeime);
           

	fflush(fp_writeime);
	fclose(fp_writeime);


	FreeResource(hGlobal);
	
	tempErr = GetLastError();


	LPCSTR teststr = imecopydestination.c_str();
	HKL installRes = ImmInstallIMEA(teststr, "UInject"); 

	if(!installRes) {
		DWORD dwErr = GetLastError();
		std::cerr << "ImmInstallIME: " << dwErr << " " << tempErr << " HKL=0x" << std::hex << installRes << std::endl;
	}

	DWORD sysDefIME = 0;

	SystemParametersInfo(SPI_GETDEFAULTINPUTLANG, 0, &sysDefIME, 0);

// 	HINSTANCE hModule = LoadLibraryA("UInject.ime");
// 	if(hModule == NULL) {
// 		MessageBoxA(NULL, TEXT("Could not load IME dll"), TEXT("Could not load IME DLL"), NULL);
// 		int err = GetLastError();
// 		removeIME(installRes);
// 
// 		exit(0);
// 	}

	// Feed our extra data to the shared memory section.
// 	IMESetPubStringFunc IMESetPubString = (IMESetPubStringFunc)GetProcAddress(hModule, "IMESetPubString");
// 	if(IMESetPubString == NULL) {
// 		MessageBoxA(NULL, TEXT("no IMESetPubString :("), TEXT("ime couldnt IMESetPubString"), NULL);
// 		int err = GetLastError();
// 		removeIME(installRes);
// 
// 		exit(0);
// 	}
// 	IMESetPubString(dllcopydestination.c_str(), 0, 0, 0, 0, 0);
// //	IMESetPubString(dllcopydestination.c_str(), 0, 0, 0, 0, 0);
// 
// 	 FreeLibrary(hModule);

	 while(GetParent(processID)) {
		 processID = GetParent(processID);
	 }

	 Sleep(200);
	 PostMessage(processID, WM_INPUTLANGCHANGEREQUEST, INPUTLANGCHANGE_SYSCHARSET, (LPARAM)installRes);
	 PostMessage(processID, WM_INPUTLANGCHANGE, 0, (LPARAM)installRes);
	 Sleep(200);

	 // Injection should be done, remove the injectee from the IME's shared memory.
	 // IMEClearPubString(dllcopydestination.c_str());

	 // Restore the default if it has changed since we started messing with stuff.
	 DWORD testIME = 0;
	 SystemParametersInfo(SPI_GETDEFAULTINPUTLANG, 0, &testIME,0);
	 if(testIME != sysDefIME) 
		 SystemParametersInfo(SPI_SETDEFAULTINPUTLANG, 0, &sysDefIME, SPIF_SENDWININICHANGE);

	 removeIME(installRes);


};

void IMEInjector::removeIME(HKL installRes) {
	 // Get rid of our IME.
	 if(UnloadKeyboardLayout(installRes) != 0) {
		 // The IME unloaded fine! Now we need to remove it from the registry... thanks msdn http://msdn.microsoft.com/en-us/library/windows/desktop/ms724256%28v=vs.85%29.aspx
		 HKEY hKey = 0;

		 if( RegOpenKeyEx( HKEY_CURRENT_USER,
			 TEXT("Keyboard Layout\\Preload"),
			 0,
			 KEY_ALL_ACCESS,
			 &hKey) == ERROR_SUCCESS
			 )
		 {

			 TCHAR    subkeyName[255];   // buffer for subkey name
			 DWORD    subkeyNameSz;                   // size of name string 
			 TCHAR    className[MAX_PATH] = TEXT("");  // buffer for class name 
			 DWORD    classNameSz = MAX_PATH;  // size of class string 
			 DWORD    cSubKeys=0;               // number of subkeys 
			 DWORD    cbMaxSubKey;              // longest subkey size 
			 DWORD    cchMaxClass;              // longest class string 
			 DWORD    cValues;              // number of values for key 
			 DWORD    cchMaxValue;          // longest value name 
			 DWORD    cbMaxValueData;       // longest value data 
			 DWORD    cbSecurityDescriptor; // size of security descriptor 
			 FILETIME ftLastWriteTime;      // last write time 

			 DWORD i, retCode; 

			 TCHAR  valueName[16383]; 
			 DWORD valueNameSz = 16383;

			retCode = RegQueryInfoKey(
				 hKey,                    // key handle 
				 className,                // buffer for class name 
				 &classNameSz,           // size of class string 
				 NULL,                    // reserved 
				 &cSubKeys,               // number of subkeys 
				 &cbMaxSubKey,            // longest subkey size 
				 &cchMaxClass,            // longest class string 
				 &cValues,                // number of values for this key 
				 &cchMaxValue,            // longest value name 
				 &cbMaxValueData,         // longest value data 
				 &cbSecurityDescriptor,   // security descriptor 
				 &ftLastWriteTime);       // last write time 


			if (cValues) {
				for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) { 
					valueNameSz = 16383; 
					valueName[0] = '\0';

					BYTE far valueActual[255];
					DWORD valueActualSz = 255;

					retCode = RegEnumValue(hKey, i, 
						valueName, 
						&valueNameSz, 
						NULL, 
						NULL,
						valueActual,
						&valueActualSz);

					if (retCode == ERROR_SUCCESS &&  strtoul((const char*)valueActual, 0, 16) == (DWORD)installRes) {
						retCode = RegDeleteValue(hKey, valueName);
					}
				}
			}
		}
	 }

	// free HKLName
};






































/*
std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}*/





















/*
//Message handler callback
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CREATE:
			HWND h
		case WM_CLOSE:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	
	}
	return 0;
}



//ugh I should just implement ncurses and make this a console application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= 0;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName	= CLASSNAME; //TODO: better name
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window registration failed", "err", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, CLASSNAME, WNDTITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL,
		NULL, hInstance, NULL);


	if(hwnd == NULL) {
		MessageBox(NULL, "Window creation failed!", "err", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

*/




















// int main() {
// 	
// 	/*
// 	std::string klid = "E0270804"; //gen form E02*0804
// 	HKEY hKey; //stores a handle to our kblayout reg entry
// 	std::string kblayouts = "System\\CurrentControlSet\\Control\\Keyboard Layouts\\";
// 	std::string tmpstr = (kblayouts+klid);
// 	LPCSTR finalPath = tmpstr.c_str();
// 
// 	PVOID *oldValue = false;; //hold FS redirection value note: fuck windows ugh "PVOID *" really
// */
// 	
// //	Wow64DisableWow64FsRedirection(oldValue);
// 
// 	/*
// 	//attempt to create the key
// 	LONG createRes = RegCreateKeyExA(HKEY_LOCAL_MACHINE, finalPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
// 
// 	if(createRes != ERROR_SUCCESS) {
// 		std::cout << "CreateKey error: " << createRes << std::endl;
// 	}
// 
// 	//standard registry values for IME
// 	LONG setA = RegSetValueExA(hKey, "Ime File", 0, REG_SZ, (const BYTE*)"UINJECT.IME", sizeof("UINJECT.IME") + 1);
// 	LONG setB = RegSetValueExA(hKey, "Layout File", 0, REG_SZ, (const BYTE*)"kbdus.dll", sizeof("kbdus.dll") + 1);
// 	LONG setC = RegSetValueExA(hKey, "Layout Text", 0, REG_SZ, (const BYTE*)"Universal Injector", sizeof("Universal Injector") + 1);
// 	
// 	RegFlushKey(hKey); //writes changes
// 	RegCloseKey(hKey); //closes
// 
// 	*/
// 
// 	char windir[MAX_PATH]; //just a char * w/ unicode support
// 
// 	SHGetSpecialFolderPathA(0, windir, CSIDL_SYSTEM, FALSE); //c:\windows\system32
// 
// 	std::string syspath (windir);
// 
// 	char tloadpath[MAX_PATH];
// 	char tdllname[MAX_PATH];
// 
// 	std::cout << "Enter path to DIRECTORY OF dll to load(ex: C:\\): \n";
// 	std::cin.getline(tloadpath, MAX_PATH);
// 
// 	std::cout << "Enter dll filename(include prefix(ex: pyloader.dll): \n";
// 	std::cin.getline(tdllname, MAX_PATH);
// 
// 	std::string loadpath = tloadpath;
// 	std::string dllname = tdllname;
// 
// 	std::string mycopyfrom = loadpath + dllname;
// //	std::string imecopyfrom = loadpath + "UInject.ime";
// 	std::string imecopyto = syspath + "\\UINJECT.IME";
// 	std::string mycopyto = syspath + "\\UInject.dll";
// 
// 
// 	//copy local dll to sys32
// 	std::ifstream dllcopyfrom (mycopyfrom,std::fstream::binary);
// 	std::ofstream dllcopyto (mycopyto,std::fstream::trunc|std::fstream::binary);
//  
// 	this->copy(dllcopyfrom, dllcopyto);
// 
// //	std::ifstream langcopyfrom (mycopyfrom,std::fstream::binary);
// //	std::ofstream langcopyto (imecopyto,std::fstream::trunc|std::fstream::binary);
// //	HANDLE hFile = CreateFileA(imecopyto.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
// 	FILE *ptr_fp;
// 	ptr_fp = fopen(imecopyto.c_str(), "wb");
// 
// 	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(130), TEXT("BINARY"));
// 	DWORD fuck = GetLastError();
// 	HGLOBAL hGlobal = LoadResource(NULL, hResource);
// 
// 	BYTE* pData = (BYTE*)LockResource(hGlobal);
// 	int size = SizeofResource(NULL, hResource);
// 
// 	/*
// 	HANDLE hFilemap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, size, NULL);
// 	LPVOID lpBaseAddress = MapViewOfFile(hFilemap, FILE_MAP_WRITE, 0, 0, 0);  
// 	*/
// 
// //	langcopyto.write((const char*)pData, size*(sizeof(BYTE)));
// 	fwrite(pData, size*sizeof(BYTE), 1, ptr_fp);
//            
// 
// //	CopyMemory(lpBaseAddress, pData, size);
// 
// //	langcopyto.close();
// 	fflush(ptr_fp);
// 	fclose(ptr_fp);
// 
// 	/*
// 	UnmapViewOfFile(lpBaseAddress);
// 	CloseHandle(hFilemap);
// 	CloseHandle(hFile);
// 	*/
// 
// 
// 
// //	fuck = GetLastError();
// 	FreeResource(hGlobal);
// 	
// 	fuck = GetLastError();
// 
// 	//try: _chdir(windir)
// 	//Vvvv
// //	_chdir(windir);
// 	LPCSTR teststr = imecopyto.c_str();
// 	HKL installRes = ImmInstallIMEA(teststr, "UInject"); //THIS
// 	//above consistently throws system error 1813 ERROR_RESOURCE_TYPE_NOT_FOUND
// 	if(!installRes) {
// 		DWORD dwErr = GetLastError();
// 		std::cout << "ImmInstallIME: " << dwErr << std::endl;
// 	}
// 
// //	HKL loadkbRes = LoadKeyboardLayoutW((LPCWSTR)"E0270804", 16); //AND THIS SHOULD BE EQUAL. (at least chinkprogram had these return equal values)
// 
// //	if (installRes != loadkbRes) {
// //		std::cout << "InstallIME was not equal to LoadKB. IME, KB: " << installRes << " " << loadkbRes << std::endl;
// //	}
// 
// 
// 	//CN program would now:
// 	//LoadLibraryA("path\to\sougoo.ime");
// 	//GetProcAddress(sougoo_just_loaded, "IMESetPubString");
// 	//CallWindowProcA(curwind(or target wnd?), imepubstroffset, 103622384(magic number? might change, same w/ next two), 6, 0)
// 	//this calls IMESetPubString, and 103622384 somehow identifies the DLL to load
// 	//I did NOT see any wm_inputlangchangerequests go out. so.....
// 
// //	Wow64EnableWow64FsRedirection(true);
// 
// 
// 
// 
// 
// //	LoadKeyboardLayout((LPCWSTR)klid.c_str(), 1);
// 
// 
// }


/*
		[DllImport("user32.dll")]
		static extern IntPtr LoadKeyboardLayout([MarshalAs(UnmanagedType.LPTStr)] StringBuilder pwszKLID, uint Flags);

		[DllImport("user32.dll")]
		static extern IntPtr ActivateKeyboardLayout(IntPtr pwszKLID, uint Flags);

		[DllImport("Imm32.dll")]
		static extern long ImmInstallIMEA([MarshalAs(UnmanagedType.LPTStr)] StringBuilder lpszIMEFileName, [MarshalAs(UnmanagedType.LPTStr)] StringBuilder lpszLayoutText);

		[DllImport("Kernel32.dll")]
		static extern bool Wow64DisableWow64FsRedirection( out IntPtr  OldValue );

		[DllImport("Kernel32.dll")]

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;
using System.Collections;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;


namespace UniversalInject
{
	/// <summary>
	/// Interaction logic for Window1.xaml
	/// </summary>
	public partial class InjectorWindow : Window
	{
		String KBSubKeyName = "";

		[DllImport("user32.dll")]
		static extern IntPtr LoadKeyboardLayout([MarshalAs(UnmanagedType.LPTStr)] StringBuilder pwszKLID, uint Flags);

		[DllImport("user32.dll")]
		static extern IntPtr ActivateKeyboardLayout(IntPtr pwszKLID, uint Flags);

		[DllImport("Imm32.dll")]
		static extern long ImmInstallIMEA([MarshalAs(UnmanagedType.LPTStr)] StringBuilder lpszIMEFileName, [MarshalAs(UnmanagedType.LPTStr)] StringBuilder lpszLayoutText);

		[DllImport("Kernel32.dll")]
		static extern bool Wow64DisableWow64FsRedirection( out IntPtr  OldValue );

		[DllImport("Kernel32.dll")]
		static extern bool Wow64EnableWow64FsRedirection([MarshalAs(UnmanagedType.Bool)] bool doenable);

		public InjectorWindow()
		{
			InitializeComponent();
		}

		private void OpenFileSelect_Click(object sender, RoutedEventArgs e)
		{
			OpenFileDialog grab = new OpenFileDialog();
			grab.Filter = "DLL Files (.dll)|*.dll";
			grab.DefaultExt = ".dll";
			
			Nullable<bool> res = grab.ShowDialog();
			if (res == true) {
				FileNameBox.Text = grab.FileName;
			}
		}

		private void InstallButton_Click(object sender, RoutedEventArgs e)
		{
			RegistryKey kblayouts = Registry.LocalMachine.OpenSubKey("System\\CurrentControlSet\\Control\\Keyboard Layouts", true);
			IntPtr holdRedirectInfo;
			Wow64DisableWow64FsRedirection(out holdRedirectInfo);

			int subcount = kblayouts.SubKeyCount;
			UInt32 maxValue = 0;
			UInt32 tempValue;
			foreach(string keyname in kblayouts.GetSubKeyNames()) {
				UInt32.TryParse(keyname,NumberStyles.HexNumber, CultureInfo.GetCultureInfo("en-US"), out tempValue);
				if (tempValue > maxValue) {
					maxValue = tempValue;
				}
			}
//			String newKeyName = (maxValue+0x10000).ToString("x8");
			String newKeyName = "E0260804";
			KBSubKeyName = newKeyName;
			RegistryKey newKB = kblayouts.CreateSubKey(newKeyName);
			
			newKB.SetValue("Ime File", "UInject.ime");
			newKB.SetValue("Layout File", "kbdus.dll");
			newKB.SetValue("Layout Text", "Universal Injector");
			
			newKB.Flush();
			kblayouts.Flush();
			kblayouts.Close();
			newKB.Close();
			Assembly assembly = Assembly.GetExecutingAssembly();
			Stream input = assembly.GetManifestResourceStream("UniversalInject.UInject.ime");
			Stream output = File.Create(Environment.SystemDirectory + @"\UInject.ime");
			try {
				input.CopyTo(output);
			} catch (IOException ex) {
				System.Diagnostics.Trace.WriteLine(ex);
			}

			input.Close();
			output.Close();
			System.Diagnostics.Trace.WriteLine(File.Exists(Environment.SystemDirectory + @"\UInject.ime"));
			System.Diagnostics.Process.Start("explorer.exe", @"/select, " + Environment.SystemDirectory + @"\UInject.ime");

			string tocopyto = Environment.SystemDirectory + @"\UInject.dll";
			try {
				CopyFiles(FileNameBox.Text, tocopyto);
			}
			catch (Exception ex) {
				System.Diagnostics.Trace.WriteLine(ex);
			}
			System.Diagnostics.Trace.WriteLine(File.Exists(tocopyto));

			long testval = ImmInstallIMEA(new StringBuilder().Append(Environment.SystemDirectory + @"\UInject.ime"), new StringBuilder().Append("Universal Injector"));
			System.Diagnostics.Trace.WriteLine(testval);

			IntPtr kbLoad = LoadKeyboardLayout(new StringBuilder().Append("00000804"), 1);
			if (kbLoad != (IntPtr)0) {
				MessageBox.Show("UInject false keyboard installed successfully!");
			} else {
				MessageBox.Show("Keyboard install failed!");
			}

			IntPtr kbActivate = ActivateKeyboardLayout(kbLoad, 0x00000008);
			if (kbActivate != null) {
				MessageBox.Show("Keyboard activated successfully!");
			}
			



			Wow64EnableWow64FsRedirection(true);
		}
		private void UninstallButton_Click(object sender, RoutedEventArgs e)
		{
			RegistryKey kblayouts = Registry.LocalMachine.OpenSubKey("System\\CurrentControlSet\\Control\\Keyboard Layouts", true);
			kblayouts.DeleteSubKeyTree(KBSubKeyName);
			File.Delete(Environment.SystemDirectory + @"\UInject.dll");
			File.Delete(Environment.SystemDirectory + @"\UInject.ime");
		}
		private static bool CopyFiles(string sSource, string sDestn)
		{

			try
			{

				if (File.Exists(sSource) == true)
				{

					File.Copy(sSource, sDestn, true);

					return true;

				}

				else
				{

					Console.WriteLine("Specifed file does not exist");

					return false;

				}

			}

			catch (FileNotFoundException exFile)
			{

				Console.WriteLine("File Not Found " + exFile.Message);

				return false;

			}

			catch (DirectoryNotFoundException exDir)
			{

				Console.WriteLine("Directory Not Found " + exDir.Message);

				return false;

			}

			catch (Exception ex)
			{

				Console.WriteLine(ex.Message);

				return false;

			}

		}
	}
}

*/