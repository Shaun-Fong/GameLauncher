#include "PrecompiledHeader.h"
#include "..\UnityPlayerStub\Exports.h"
#include <windows.h>

// Hint that the discrete gpu should be enabled on optimus/enduro systems
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
    __declspec(dllexport) extern const UINT D3D12SDKVersion = 610;
    __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\D3D12\\";
}

// TimerWindow
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_TIMER: {
        if (wp == 1) {
            DestroyWindow(hwnd);
        }
        break;
    }

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"UnityLauncherClass";

    // Register Class
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, L"Register Failed!", L"ERROR", MB_OK);
        return 0;
    }

	// Define Window Size
    const int windowWidth = 400;
    const int windowHeight = 200;

    // Get screen width and height
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Make window center
    int xPos = (screenWidth - windowWidth) / 2;
    int yPos = (screenHeight - windowHeight) / 2;

    // Create window
    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        L"Unity Launcher",
        WS_POPUP,  // using WS_POPUP style£¬remove all layout
        xPos, yPos,  // set window position
        windowWidth, windowHeight,  // set window size
        nullptr, nullptr, hInstance, nullptr
    );

    // Create label
    CreateWindow(
        L"STATIC",
        L"START THE GAME IN FIVE SECONDS",  // content
        WS_VISIBLE | WS_CHILD,
        50, 50, 300, 40,
        hwnd, nullptr, hInstance, nullptr
    );

    // Set timer
    SetTimer(hwnd, 1, 5000, nullptr);  // 5s

    // Show window
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // Keep window alive
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Quit message and invoke UnityMain
    UnityMain(hInstance, nullptr, nullptr, SW_SHOWNORMAL);

    return 0;
}
