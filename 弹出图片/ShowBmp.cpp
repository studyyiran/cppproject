// 文件名：ShowBmp.cpp
#include <windows.h>

const char g_szClassName[] = "MyBmpWindow";
HBITMAP hBmp = 0;

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch (msg) {
    case WM_CREATE:
        // 从文件加载位图
        hBmp = (HBITMAP)LoadImageA(
            NULL,
            "test.bmp",       // 文件名
            IMAGE_BITMAP,     // 类型：位图
            0, 0,             // 原始尺寸
            LR_LOADFROMFILE   // 从文件加载
        );
        if (!hBmp) {
            MessageBoxA(hwnd, "无法加载 test.bmp", "错误", MB_OK | MB_ICONERROR);
            PostQuitMessage(0);
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        if (hBmp) {
            // 创建与屏幕兼容的 DC
            HDC hMemDC = CreateCompatibleDC(hdc);
            // 选入位图
            HBITMAP oldBmp = (HBITMAP)SelectObject(hMemDC, hBmp);

            // 获取位图尺寸
            BITMAP bm;
            GetObject(hBmp, sizeof(bm), &bm);

            // 将位图绘制到客户区左上角
            BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);

            // 清理
            SelectObject(hMemDC, oldBmp);
            DeleteDC(hMemDC);
        }
        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        if (hBmp) DeleteObject(hBmp);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASSEXA wc = { 0 };
    wc.cbSize        = sizeof(wc);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = g_szClassName;

    if (!RegisterClassExA(&wc)) {
        MessageBoxA(NULL, "窗口注册失败！", "Error", MB_ICONERROR);
        return 0;
    }

    // 创建窗口，窗口大小根据图片调整也可以手动改
    HWND hwnd = CreateWindowExA(
        0,
        g_szClassName,
        "显示位图 Demo",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,          // 初始窗口大小
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        MessageBoxA(NULL, "窗口创建失败！", "Error", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    MSG Msg;
    while (GetMessageA(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    return (int)Msg.wParam;
}

