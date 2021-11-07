#include "story.hpp"

const int width = 320;
const int height = 240;

Story::Story()
    : painter{width, height}
{
}

void Story::paint(HWND hWnd)
{
    BITMAPINFO bmi = {
        sizeof(BITMAPINFOHEADER),
        width,
        -height,
        1,
        imColorDepth,
        BI_RGB,
        ((((width * imBytesPerColor * 8) + 31) & ~31) >> 3) * height,
        0, 0, 0, 0};

    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hWnd, &ps);

    RECT rect = {0};
    GetClientRect(hWnd, &rect);

    auto buf = painter.PaintShapes();

    SetDIBitsToDevice(
        hDC,
        0, 0,
        width, height,
        0, 0,
        0, height,
        buf, &bmi,
        DIB_RGB_COLORS);

    ReleaseDC(hWnd, hDC);

    EndPaint(hWnd, &ps);
}
