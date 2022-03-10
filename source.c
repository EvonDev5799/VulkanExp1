#include "utilityWindow.h"
#include "C:\VulkanSDK\1.3.204.1\Include\vulkan\vulkan.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	createConsole(L"console");
	createWindow(L"window", 1024, 512, 0, 0, hInstance);
	int i;
	vkEnumerateInstanceExtensionProperties(NULL, &i, NULL);
	renderLoop();
	return(0);
}