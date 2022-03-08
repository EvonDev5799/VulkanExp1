#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#define APPLINATION_NAME "Vulkan Test"

void exitOnError(char *msg)
{
	MessageBox(NULL, msg, APPLINATION_NAME, MB_ICONERROR);
}

void createConsole(void)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
	SetConsoleTitle(TEXT(APPLINATION_NAME));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int r = 0;
	switch (message)
	{
	case WM_DESTROY:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		break;
	default:
		r = DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return(r);
}

void createWindow(HINSTANCE hInstance)
{
	const uint32_t windowWidth = 1280;
	const uint32_t windowHeight = 720;

	HINSTANCE windowInstance = hInstance;
	HWND window;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = APPLINATION_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
		exitOnError("Failed to register window");

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int windowLeft = screenWidth / 2 - windowWidth / 2;
	int windowTop = screenHeight / 2 - windowHeight / 2;

	window = CreateWindow(
		APPLINATION_NAME,
		APPLINATION_NAME,
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		windowLeft,
		windowTop,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		windowInstance,
		NULL);

	if (!window)
		exitOnError("Failed to create window");

	ShowWindow(window, SW_SHOW);
	SetForegroundWindow(window);
	SetFocus(window);
}

void renderLoop()
{
	MSG message;

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	createConsole();
	createWindow(hInstance);
	renderLoop();
	return(0);
}