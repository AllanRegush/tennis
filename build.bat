
mkdir .\build
pushd .\build
echo %cd%
cl -Zi /I C:\sdk\SDL2\include ..\src\tennis.c /link c:\sdk\SDL2\lib\x64\SDL2main.lib c:\sdk\SDL2\lib\x64\SDL2test.lib c:\sdk\SDL2\lib\x64\SDL2.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /SUBSYSTEM:CONSOLE
popd
