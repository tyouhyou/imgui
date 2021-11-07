#include "gfxpainter.hpp"

using namespace im;

GfxPainter::GfxPainter(int w, int h)
    : gfx{w, h}
{
}

char* GfxPainter::PaintShapes()
{
    imColor red = imSetRed(127, 0);
    imColor green = imSetGreen(127, 0);
    imColor blue = imSetBlue(127, 0);
    imColor ground = red | green | blue;

    gfx.Fill(ground);
    gfx.DrawLine(0, 0, 100, 50, red);
    gfx.FillCircle(100, 100, 50, blue);
    gfx.FillRect(0, 150, 200, 200, green);

    return gfx.Data();
}