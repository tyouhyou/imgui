#include "gfx.hpp"

class GfxPainter
{
public:
    GfxPainter(int w, int h);
    char* PaintShapes();

private:
    im::Gfx gfx;
};