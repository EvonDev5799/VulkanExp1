#define VK_USE_PLATFORM_WIN32_KHR
#include "C:\VulkanSDK\1.3.204.1\Include\vulkan\vulkan.h"

void f(HINSTANCE windowInstance, HWND window, VkInstance instance)
{
	VkSurfaceKHR surface;

	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo;
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = NULL;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.hinstance = windowInstance;
	surfaceCreateInfo.hwnd = window;

	VkResult result =
    vkCreateWin32SurfaceKHR(instance, &surfaceCreateInfo, NULL, &surface);
	assert(result == VK_SUCCESS);
}