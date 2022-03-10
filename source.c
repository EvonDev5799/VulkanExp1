#include "utilityWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	createConsole(L"console");
	createWindow(L"window", 1024, 512, 0, 0, hInstance);
	renderLoop();
	return(0);
}