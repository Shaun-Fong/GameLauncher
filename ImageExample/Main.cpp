#include "PrecompiledHeader.h"
#include "..\UnityPlayerStub\Exports.h"
#include "resource.h"
#include <windows.h>
#include <iostream>

extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
    __declspec(dllexport) extern const UINT D3D12SDKVersion = 610;
    __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\D3D12\\";
}

// Window procedure function
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);  // Post quit message
        break;

    case WM_TIMER: {
        // If the timer expires (5 seconds), destroy the window
        if (wp == 1) {
            DestroyWindow(hwnd);  // Destroy window
        }
        break;
    }

    default:
        return DefWindowProc(hwnd, msg, wp, lp);  // Default window processing
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
    // Window class structure
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;  // Window procedure function
    wc.hInstance = hInstance;  // Current application instance
    wc.lpszClassName = L"UnityLauncherClass";  // Window class name

    // Register window class
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, L"Window class registration failed", L"Error", MB_OK);
        return 0;
    }

    // Directly load the embedded bitmap resource using LoadBitmap
    HBITMAP hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_MYIMAGE));
    if (!hBitmap) {
        MessageBox(NULL, L"Image resource loading failed", L"Error", MB_OK);
        return 0;
    }

    // Get the width and height of the image
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    // Set the window width and height to match the image size
    const int windowWidth = bitmap.bmWidth;
    const int windowHeight = bitmap.bmHeight;

    // Get the screen width and height
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Calculate the window position to center it on the screen
    int xPos = (screenWidth - windowWidth) / 2;
    int yPos = (screenHeight - windowHeight) / 2;

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        L"Unity Launcher",  // Window title
        WS_POPUP,  // Use WS_POPUP style to remove borders, title, etc.
        xPos, yPos,  // Set window position
        windowWidth, windowHeight,  // Set window size based on image
        nullptr, nullptr, hInstance, nullptr
    );

    // Create a static control within the window to display the image
    HWND hImage = CreateWindow(
        L"STATIC",  // Control type: static control
        NULL,       // Control text
        WS_VISIBLE | WS_CHILD | SS_BITMAP,  // Show as bitmap
        0, 0, windowWidth, windowHeight,  // Control position and size
        hwnd, nullptr, hInstance, nullptr
    );

    // Set the control image to the loaded bitmap
    SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

    // Set a timer to trigger after 5 seconds
    SetTimer(hwnd, 1, 5000, nullptr);  // 5000 milliseconds = 5 seconds

    // Show and update the window
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Call UnityMain after the message loop ends
    UnityMain(hInstance, nullptr, nullptr, SW_SHOWNORMAL);

    return 0;
}
