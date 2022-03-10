#include "settings.h"
#include "utilityWindow.h"
#include <windows.h>
#include <stdio.h>
#include <stdint.h>

void exitOnError(LPCWSTR msg)
{
	MessageBoxW(NULL, msg, ERRORTITLE, MB_ICONERROR);
}

int createConsole(LPCWSTR title)
{
	FILE *stream;

	int ret = 1;
	if (AllocConsole()) // if succes
	{		
		if (AttachConsole(GetCurrentProcessId())) // if fails
		{
			exitOnError(L"failed to attach console");
		}
		else
		{
			if (freopen_s(&stream, "CON", "w", stdout)) // if fails
			{
				exitOnError(L"failed to redirect stdout");
			}
			else
			{
				if (freopen_s(&stream, "CON", "w", stderr)) // if fails
				{
					exitOnError(L"failed to redirect stderr");
				}
				else
				{
					if (SetConsoleTitleW(title)) // if success
					{
						ret = 0;
					}
					else
					{
						exitOnError(L"failed to set console title");
					}
				}
			}
		}
	}
	else
	{
		exitOnError(L"failed to alloc Console");
	}
	return(ret);
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
		r = DefWindowProcW(hWnd, message, wParam, lParam);
		break;
	}
	return (r);
}

int setupWindowClass(HINSTANCE hInstance, LPCWSTR name)
{
	int ret = 0;
	if (GetClassInfoW(hInstance, name, NULL))
	{
		printf("attempt to register the same class more than once\n");
	}
	else
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_APPLICATION));
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = name;
		wcex.hIconSm = LoadIconW(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

		if (!RegisterClassExW(&wcex)) // if fails
		{
			ret = 1;
			exitOnError(L"Failed to register window");
		}
	}
	return (ret);
}

int createWindow(LPCWSTR name, int width, int height, int verticalOffset, int horizontalOffset, HINSTANCE hInstance)
{
	int ret = 0;
	HINSTANCE windowInstance = hInstance;
	HWND window;

	if(setupWindowClass(hInstance, name)) //if fails
	{

	}

	window = CreateWindowExW(
		0L,
		name,
		name,
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		horizontalOffset,
		verticalOffset,
		width,
		height,
		NULL,
		NULL,
		windowInstance,
		NULL);

	if (!window)
	{
		exitOnError(L"Failed to create window");
		ret = 1;
	}

	ShowWindow(window, SW_SHOW);
	SetForegroundWindow(window);
	SetFocus(window);
	return(ret);
}

void renderLoop(void)
{
	MSG message;

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}