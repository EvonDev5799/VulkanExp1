#include "settings.h"
#include <windows.h>
#include <stdio.h>
#include <stdint.h>

void exitOnError(LPCWSTR msg);

int createConsole(LPCWSTR title);

int createWindow(LPCWSTR name, int width, int height, int verticalOffset, int horizontalOffset, HINSTANCE hInstance);

void renderLoop(void);