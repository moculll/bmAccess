#include <windows.h>
#include <Psapi.h>
#include <stdio.h>
#include <memory>

#include "dataMgr.h"


DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    
    dataMgr *mgr = reinterpret_cast<dataMgr*>(lpParameter);
    if (mgr->init()) {
        printf("init successful!");
        mgr->start();
    }
    else {
        MessageBox(NULL, "bmDLL init failed, check!", "Error", MB_OK | MB_ICONERROR);
    }
    
    return 0;
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    static dataMgr *mgr = new dataMgr;
    static HANDLE hThread = NULL;
    switch (ul_reason_for_call)
    {
        
    case DLL_PROCESS_ATTACH:
        
        hThread = CreateThread(
            NULL,
            0,
            ThreadProc,
            mgr,
            0,
            NULL
        );
        if (hThread == NULL)
        {
            MessageBox(NULL, "Failed to create thread", "Error", MB_OK | MB_ICONERROR);
            return FALSE;
        }
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        mgr->exit();
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
        hThread = nullptr;
        delete mgr;
        mgr = nullptr;
        break;
    }
    return TRUE;
}

