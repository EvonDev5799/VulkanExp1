call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
cd build
cl ../source.c gdi32.lib user32.lib /std:c17 /Wall
pause