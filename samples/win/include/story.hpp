#pragma once
#include <windows.h>
#include "gfxpainter.hpp"

class Story
{
public:
    Story();
    void paint(HWND hwnd);

private:
    GfxPainter painter;
};
