// WindowsProject1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#include "stdafx.h"
#include "SystemClass.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    SystemClass* System = new SystemClass{};
    if (!System)
        return -1;

    if (System->Initialize()) {
        System->Run();
    }


    System->ShutDown();
    delete System;
    System = nullptr;

    return 0;
}
