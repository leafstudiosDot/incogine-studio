#include <iostream>

#ifdef WIN32
    #ifndef UNICODE
    #define UNICODE
    #endif 

    #include <windows.h>
    #include <commctrl.h>
    #pragma comment(lib, "comctl32.lib")

    HWND mainWindow = NULL;
    HWND launcherWindow = NULL;
    HINSTANCE hInstance;
    HFONT hFont = CreateFontA(-13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");

    LRESULT CALLBACK StudioWindowProc(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK LauncherWindowProc(HWND, UINT, WPARAM, LPARAM);

    BOOL FileExists(LPCSTR path) {
        DWORD attrib = GetFileAttributesA(path);
        return (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
    }

    // Simulated check for project file from cmd args
    BOOL IsProjectFileOpened(LPSTR lpCmdLine) {
        return lpCmdLine != NULL && lpCmdLine[0] != '\0' && FileExists(lpCmdLine);
    }

    LRESULT CALLBACK StudioWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
                EndPaint(hwnd, &ps);
                return 0;
            }

            case WM_ERASEBKGND:
                return 1;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    LRESULT CALLBACK LauncherWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        static HWND settingsbtn;
        static HWND openbtn;
        static HWND skipbtn;

        switch (msg) {
            case WM_CREATE: {
                settingsbtn = CreateWindow(L"BUTTON", L"Settings",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    10, 520, 80, 30,
                    hwnd, (HMENU)1, hInstance, NULL);
                SendMessage(settingsbtn, WM_SETFONT, (WPARAM)hFont, TRUE);

                openbtn = CreateWindow(L"BUTTON", L"Open Project",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    600, 520, 110, 30,
                    hwnd, (HMENU)1, hInstance, NULL);
                SendMessage(openbtn, WM_SETFONT, (WPARAM)hFont, TRUE);

                skipbtn = CreateWindow(L"BUTTON", L"Skip",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    720, 520, 50, 30,
                    hwnd, (HMENU)1, hInstance, NULL);
                SendMessage(skipbtn, WM_SETFONT, (WPARAM)hFont, TRUE);
            }
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                TextOutA(hdc, 10, 10, "Welcome! Choose a project to open.", 33);
                EndPaint(hwnd, &ps);
                return 0;
            }
            case WM_DESTROY: 
                PostQuitMessage(0);
                return 0;
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    // WinMain: Entry Point
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
        hInstance = hInstance;

        INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_STANDARD_CLASSES };
        InitCommonControlsEx(&icex);

        const wchar_t STUDIO_CLASS[] = L"IncogineStudioClass";
        const wchar_t LAUNCHER_CLASS[] = L"LauncherWindowClass";

        // Register the window class
        WNDCLASS wc = { 0 };
        wc.lpfnWndProc = StudioWindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = STUDIO_CLASS;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

        RegisterClass(&wc);

        // Register Launcher Class
        wc.lpfnWndProc = LauncherWindowProc;
        wc.lpszClassName = LAUNCHER_CLASS;
        RegisterClass(&wc);

        // Create the window
        HWND hwnd;

        if (IsProjectFileOpened(lpCmdLine)) {
            // Open main app with project
            hwnd = CreateWindowEx(
                0,
                STUDIO_CLASS,
                L"Incogine Studio",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
                NULL,       // Parent window    
                NULL,       // Menu
                hInstance,  // Instance handle
                NULL        // Additional application data
            );
        } else {
            // No project, show launcher
            hwnd = CreateWindowEx(
                0, 
                LAUNCHER_CLASS, 
                L"Incogine Studio", 
                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 
                NULL, 
                NULL, 
                hInstance, 
                NULL
            );
        }

        if (hwnd == NULL) return 0;

        ShowWindow(hwnd, nCmdShow);
        UpdateWindow(hwnd);

        // Message loop
        MSG msg = { 0 };
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 0;
    }
#else
    #include <iostream>
    using namespace std;

    int main(int argc, char* argv[])
    {
        std::cout << "Unsupported platform to run Incogine Studio!" << std::endl;
        return 0;
    }
#endif