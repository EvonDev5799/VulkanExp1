call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
mkdir build
cd build
cl ../source.c ../utilityWindow.c gdi32.lib user32.lib C:\VulkanSDK\1.3.204.1\Lib\vulkan-1.lib /std:c17 /W4
pause