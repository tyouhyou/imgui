#include <windows.h>
#include "story.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    Story story;

    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
        WNDCLASSEX wcx;
        HWND hwnd;
        MSG msg;
        LPTSTR clsname = (TCHAR *)"MainWindow";

        wcx.cbSize = sizeof(wcx);
        wcx.style = CS_HREDRAW | CS_VREDRAW;
        wcx.lpfnWndProc = WndProc;
        wcx.cbClsExtra = 0;
        wcx.cbWndExtra = 0;
        wcx.hInstance = hInstance;
        wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wcx.lpszMenuName = NULL;
        wcx.lpszClassName = clsname;
        wcx.hIconSm = (HICON)LoadImage(hInstance,
                                       MAKEINTRESOURCE(5),
                                       IMAGE_ICON,
                                       GetSystemMetrics(SM_CXSMICON),
                                       GetSystemMetrics(SM_CYSMICON),
                                       LR_DEFAULTCOLOR);

        if (!RegisterClassEx(&wcx))
        {
            return -1;
        }

        hwnd = CreateWindow(
            clsname,
            TEXT("imgui"),
            WS_TILEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            640,
            480,
            (HWND)NULL,
            (HMENU)NULL,
            hInstance,
            (LPVOID)NULL);

        if (!hwnd)
        {
            return -1;
        }

        ShowWindow(hwnd, SW_RESTORE);
        UpdateWindow(hwnd);

        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            story.paint(hwnd);
        }

        return 0;
    }

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        int ret = 0;

        switch (msg)
        {
        case WM_PAINT:
            story.paint(hwnd);
            break;
        case WM_DESTROY:
            //ExitThread(0);
            PostQuitMessage(0);
            break;

        default:
            ret = (int)DefWindowProc(hwnd, msg, wparam, lparam);
        }

        return ret;
    }

#ifdef __cplusplus
}
#endif
