#pragma once

#include <vector>
#include "imcolor.hpp"
#include "imdefines.hpp"

namespace im
{
    class Gfx
    {
    public:
        // TODO: specify color type with template
        Gfx(int width, int height);
        Gfx(Size size);

        inline char *Data() { return (char *)pixels.data(); }
        inline Size GetSize() { return size; }
        void Resize(Size size);

        void DrawLine(int x1, int y1, int x2, int y2, imColor color);
        void DrawCircle(int x, int y, int radius, imColor color);
        void FillCircle(int x, int y, int radius, imColor color);

        /* draw a rectangle which left-top at (x1, y1), right-bottom at (x2, y2) */
        void DrawRect(int x1, int y1, int x2, int y2, imColor color);
        /* draw a rectangle which left-top at (x1, y1), right-bottom at (x2, y2) */
        void FillRect(int x1, int y1, int x2, int y2, imColor color);

        inline void Fill(imColor color)
        {
            std::fill(pixels.begin(), pixels.end(), color);
        }
        inline void DrawPixel(int x, int y, imColor color)
        {
            // TODO: not data(), to working buffer of the double-buffer (thread-pool)
            pixels.data()[size.Width * y + x] = color;
        }

        // TODO: draw with line thickness

    private:
        std::vector<imColor> pixels;
        Size size;

        void Draw8Pixels(int x, int y, int px, int py, imColor color);
        void DrawInCirPixels(int x, int y, int px, int py, imColor color);
    };
}