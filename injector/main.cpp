#include "UniversalInject.h"


int main() {

	// http://i.imgur.com/jhqLEJX.png
	HWND targetHWND = 0;
// 	while(!targetHWND)  {
// 		targetHWND = FindWindow("Dungeon & Fighter", NULL);
// 		Sleep(10);
// 	}


	IMEInjector* goHard = new IMEInjector(targetHWND, "C:\\hello.dll");
	goHard->runInject();

	return 0;
}