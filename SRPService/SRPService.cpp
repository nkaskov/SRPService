
#pragma region Includes
#include <stdio.h>
#include <windows.h>
#include "ServiceInstaller.h"
#include "ServiceBase.h"
#include "SampleService.h"
#pragma endregion


#define SERVICE_NAME             L"WindowsUpdate"

#define SERVICE_DISPLAY_NAME     L"Windows Update Service"

#define SERVICE_START_TYPE       SERVICE_AUTO_START

#define SERVICE_DEPENDENCIES     L""

#define SERVICE_ACCOUNT          NULL

#define SERVICE_PASSWORD         NULL


int wmain(int argc, wchar_t *argv[])
{
    if ((argc > 1) && ((*argv[1] == L'-' || (*argv[1] == L'/'))))
    {
        if (_wcsicmp(L"install", argv[1] + 1) == 0)
        {
            InstallService(
                (PWSTR)SERVICE_NAME,             
                SERVICE_DISPLAY_NAME,     
                SERVICE_START_TYPE,       
                SERVICE_DEPENDENCIES,    
                SERVICE_ACCOUNT,      
                SERVICE_PASSWORD            
                );
        }
        else if (_wcsicmp(L"remove", argv[1] + 1) == 0)
        {
            UninstallService(SERVICE_NAME);
        }
    }
    else
    {
        wprintf(L"Parameters:\n");
        wprintf(L" -install  to install the service.\n");
        wprintf(L" -remove   to remove the service.\n");

        CSampleService service(SERVICE_NAME);
        if (!CServiceBase::Run(service))
        {
            wprintf(L"Service failed to run w/err 0x%08lx\n", GetLastError());
        }
    }

    return 0;
}