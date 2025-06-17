// �ļ�����ShowBmp.cpp
#include <windows.h>

const char g_szClassName[] = "MyBmpWindow";
HBITMAP hBmp = 0;

// ���ڹ��̺���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch (msg) {
    case WM_CREATE:
        // ���ļ�����λͼ
        hBmp = (HBITMAP)LoadImageA(
            NULL,
            "test.bmp",       // �ļ���
            IMAGE_BITMAP,     // ���ͣ�λͼ
            0, 0,             // ԭʼ�ߴ�
            LR_LOADFROMFILE   // ���ļ�����
        );
        if (!hBmp) {
            MessageBoxA(hwnd, "�޷����� test.bmp", "����", MB_OK | MB_ICONERROR);
            PostQuitMessage(0);
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        if (hBmp) {
            // ��������Ļ���ݵ� DC
            HDC hMemDC = CreateCompatibleDC(hdc);
            // ѡ��λͼ
            HBITMAP oldBmp = (HBITMAP)SelectObject(hMemDC, hBmp);

            // ��ȡλͼ�ߴ�
            BITMAP bm;
            GetObject(hBmp, sizeof(bm), &bm);

            // ��λͼ���Ƶ��ͻ������Ͻ�
            BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);

            // ����
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
        MessageBoxA(NULL, "����ע��ʧ�ܣ�", "Error", MB_ICONERROR);
        return 0;
    }

    // �������ڣ����ڴ�С����ͼƬ����Ҳ�����ֶ���
    HWND hwnd = CreateWindowExA(
        0,
        g_szClassName,
        "��ʾλͼ Demo",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,          // ��ʼ���ڴ�С
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        MessageBoxA(NULL, "���ڴ���ʧ�ܣ�", "Error", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // ��Ϣѭ��
    MSG Msg;
    while (GetMessageA(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    return (int)Msg.wParam;
}

