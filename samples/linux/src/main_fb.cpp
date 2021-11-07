#include <unistd.h>
#include "gfxpainter.hpp"
#include "fb.hpp"
#include "cxxlog.hpp"

int main(int argc, char *argv[])
{
    IE << "run on FB";

    GfxPainter painter{320, 240};
    auto buf = painter.PaintShapes();

    FB fp;
    fp.draw(buf, 320, 240);

    return 0;
}