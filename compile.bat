call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
mkdir build
cd build
cl ../source.c ../utilityWindow.c gdi32.lib user32.lib /std:c17 /W4
pause