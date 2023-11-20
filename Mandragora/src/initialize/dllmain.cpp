#include "pch.h"

extern void initialize(uintptr_t module_base, size_t module_size);

DWORD WINAPI thread_proc_entry(_In_ LPVOID lpParameter)
{
    initialize(reinterpret_cast<uintptr_t>(lpParameter), 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CreateThread(nullptr, 0, thread_proc_entry, hModule, 0, nullptr);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

