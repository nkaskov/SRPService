
#pragma region Includes
#include "SampleService.h"
//#include "ThreadPool.h"
//#include "../include/Inject.h"
#pragma endregion
#include <Windows.h>
#include <stdio.h>

#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

#pragma comment(lib, "strmiids")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "Setupapi.lib")

#include <tchar.h>
#include <strsafe.h>

DWORD WINAPI InternalServiceWorkerThread(LPVOID lpParam);

CSampleService::CSampleService(PCWSTR pszServiceName, 
                               BOOL fCanStop, 
                               BOOL fCanShutdown,
                               BOOL fCanPauseContinue)
: CServiceBase(pszServiceName, fCanStop, fCanShutdown, fCanPauseContinue)
{
    m_fStopping = FALSE;

    m_hStoppedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (m_hStoppedEvent == NULL)
    {
        throw GetLastError();
    }
}


CSampleService::~CSampleService(void)
{
    if (m_hStoppedEvent)
    {
        CloseHandle(m_hStoppedEvent);
        m_hStoppedEvent = NULL;
    }
}

DWORD worker_thread_id = 0;
DWORD thread_id = 0;
HANDLE worker_handle;
HANDLE thread_handle;

void CSampleService::OnStart(DWORD dwArgc, LPWSTR *lpszArgv)
{
    WriteEventLogEntry(L"WindowsUpdateService in OnStart", 
        EVENTLOG_INFORMATION_TYPE);

	worker_handle = CreateThread(NULL, 0, &InternalServiceWorkerThread, NULL, 0, &worker_thread_id);
}

DWORD WINAPI StartActivity(LPVOID lpParam) {
			//Inject();
}

DWORD WINAPI InternalServiceWorkerThread(LPVOID lpParam)
{	

	//freopen("c:\\WindowsUpdate.log", "a", stdout);
	//freopen("c:\\WindowsUpdate.log", "a", stderr);

	fflush(stdout);
	//Inject();
	//thread_handle = CreateThread(NULL, 0, &StartActivity, NULL, 0, &thread_id);
	
	//WaitForSingleObject(thread_handle, INFINITE);
	return 0;
}

void CSampleService::OnStop()
{
    WriteEventLogEntry(L"WindowsUpdateService in OnStop", 
        EVENTLOG_INFORMATION_TYPE);
	TerminateThread(thread_handle, 0x00);
	TerminateThread(worker_handle, 0x00);

	WaitForSingleObject(worker_handle, INFINITE);

}