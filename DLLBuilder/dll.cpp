#include "dll.h"
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>

DLLEXPORT void mess() {
    MessageBoxA(0, "HELLO THERE :)", "From Notepad", MB_ICONINFORMATION);
}
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: mess(); break;
    case DLL_THREAD_ATTACH:  break;
    case DLL_THREAD_DETACH:  break;
    case DLL_PROCESS_DETACH: break;
    }
    return TRUE;
}