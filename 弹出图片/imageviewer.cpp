#include "imageviewer.h"
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
#pragma comment(lib, "gdi32")

using namespace Gdiplus;

class ImageWindow {
public:
    explicit ImageWindow(const wchar_t* path) : _image(path) {}
    bool ok() const { return _image.GetLastStatus() == Ok; }

    int run() {
        WNDCLASSEXW wc{ sizeof(wc) };
        wc.lpfnWndProc   = WndProc;
        wc.hInstance     = GetModuleHandleW(nullptr);
        wc.lpszClassName = L"SimpleImageWnd";
        wc.hCursor       = LoadCursorW(nullptr, IDC_ARROW);
        RegisterClassExW(&wc);

        UINT w = _image.GetWidth(), h = _image.GetHeight();
        _hwnd = CreateWindowExW(
            0, wc.lpszClassName, L"Image Preview",
            WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT, w, h,
            nullptr, nullptr, wc.hInstance, this);

        if (!_hwnd) return -1;
        ShowWindow(_hwnd, SW_SHOW);   UpdateWindow(_hwnd);

        MSG msg{};
        while (GetMessageW(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);   DispatchMessageW(&msg);
        }
        return static_cast<int>(msg.wParam);
    }
private:
    static LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
        auto* self = reinterpret_cast<ImageWindow*>(
            GetWindowLongPtrW(h, GWLP_USERDATA));

        if (m == WM_NCCREATE) {
            self = reinterpret_cast<ImageWindow*>(
                reinterpret_cast<CREATESTRUCTW*>(l)->lpCreateParams);
            SetWindowLongPtrW(h, GWLP_USERDATA, (LONG_PTR)self);
            return DefWindowProcW(h, m, w, l);
        }
        if (m == WM_PAINT && self) {
            PAINTSTRUCT ps; HDC dc = BeginPaint(h, &ps);
            Graphics g(dc);  g.DrawImage(&self->_image, 0, 0);
            EndPaint(h, &ps);  return 0;
        }
        if (m == WM_DESTROY) { PostQuitMessage(0); return 0; }
        return DefWindowProcW(h, m, w, l);
    }
    Image _image;
    HWND  _hwnd = nullptr;
};

void ShowImage(const wchar_t* path)
{
    GdiplusStartupInput in; ULONG_PTR tk;
    if (GdiplusStartup(&tk, &in, nullptr) != Ok) {
        MessageBoxW(nullptr, L"GDI+ init failed!", L"Error", MB_OK);
        return;
    }
    ImageWindow win(path);
    if (!win.ok()) {
        MessageBoxW(nullptr, L"Cannot load image!", L"Error", MB_OK);
        GdiplusShutdown(tk); return;
    }
    win.run();  GdiplusShutdown(tk);
}

