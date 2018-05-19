
#pragma once

#include <windows.h>


class CServiceBase
{
public:

    static BOOL Run(CServiceBase &service);

    CServiceBase(PCWSTR pszServiceName, 
        BOOL fCanStop = TRUE, 
        BOOL fCanShutdown = TRUE, 
        BOOL fCanPauseContinue = FALSE);

    virtual ~CServiceBase(void);

    void Stop();

protected:

    virtual void OnStart(DWORD dwArgc, PWSTR *pszArgv);

    virtual void OnStop();

    virtual void OnPause();

    virtual void OnContinue();

    virtual void OnShutdown();

    void SetServiceStatus(DWORD dwCurrentState, 
        DWORD dwWin32ExitCode = NO_ERROR, 
        DWORD dwWaitHint = 0);

    void WriteEventLogEntry(PCWSTR pszMessage, WORD wType);

    void WriteErrorLogEntry(PCWSTR pszFunction, 
        DWORD dwError = GetLastError());

private:

    static void WINAPI ServiceMain(DWORD dwArgc, LPWSTR *lpszArgv);

    static void WINAPI ServiceCtrlHandler(DWORD dwCtrl);

    void Start(DWORD dwArgc, PWSTR *pszArgv);
    
    void Pause();

    void Continue();

    void Shutdown();

    static CServiceBase *s_service;

    PCWSTR m_name;

    SERVICE_STATUS m_status;

    SERVICE_STATUS_HANDLE m_statusHandle;
};