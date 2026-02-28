#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "Graphics.hpp"
#include <iostream>
#include "renderer.hpp"

LRESULT CALLBACK fnWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow){
    TCHAR szAppName[] = _TEXT("Buttons With Rounded Corners");
    HWND hwnd;
    WNDCLASSEX wndClass;
    MSG msg;

    wndClass.cbSize         = sizeof(WNDCLASSEX);
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hbrBackground  = (HBRUSH) ::GetStockObject(WHITE_BRUSH);
    wndClass.hCursor        = LoadCursor(NULL,IDC_ARROW);
    wndClass.hIcon          = LoadIcon(NULL,IDI_APPLICATION);
    wndClass.hIconSm        = LoadIcon(NULL,IDI_APPLICATION); // Small icon for taskbar / ALT+TAB
    wndClass.hInstance      = hInstance;
    wndClass.lpfnWndProc    = fnWinProc;
    wndClass.lpszClassName  = szAppName;
    wndClass.lpszMenuName   = NULL;
    wndClass.style          = CS_HREDRAW | CS_VREDRAW;

    if (! ::RegisterClassEx(&wndClass)){
        constexpr int ErrorBuffSize = 256;
        TCHAR szErrBuff[ErrorBuffSize];
        StringCchPrintf(
            szErrBuff,
            ErrorBuffSize,
            _T("Cannot Register Window Class Of Name %s"),
            wndClass.lpszClassName
        );
        ::MessageBox(
            NULL,
            szErrBuff,
            _TEXT("Internal Error : Cannot Register Window Class"),
            MB_OK | MB_APPLMODAL | MB_ICONERROR
        );
        return 0;
    }

    hwnd = ::CreateWindowEx(
        WS_EX_APPWINDOW,
        szAppName,
        szAppName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ::ShowWindow(hwnd,iCmdShow);
    ::UpdateWindow(hwnd);

    ::InvalidateRect(hwnd,NULL,TRUE);

    while(::GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK fnWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    static HWND DefWinStyleBtn;
    static Renderer* MainWindowRenderer = nullptr;
    int cxPadding = 50;
    int cyPadding = 50;
    switch (msg)
    {
    case WM_CREATE:{
        DefWinStyleBtn = CreateWindowEx(
            0,
            _T("button"),
            _TEXT("Win Button"),
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 
            cxPadding, 
            cyPadding, 
            100, 
            30, 
            hwnd,
            NULL, 
            GetModuleHandle(NULL),
            NULL
        );
        MainWindowRenderer = new Renderer();
        MainWindowRenderer->SetStage(hwnd);
        return 0;
    }
    case WM_PAINT:{
        if (!MainWindowRenderer) break;
        hdc = ::BeginPaint(hwnd,&ps);
        MainWindowRenderer->Render();
        ::EndPaint(hwnd,&ps);
        return 0;
    }
    case WM_SIZE:
    return 0;
    case WM_DESTROY:
        ::PostQuitMessage(0);
    return 0;
    default:
        break;
    }
    return DefWindowProc(hwnd,msg,wParam,lParam);
}