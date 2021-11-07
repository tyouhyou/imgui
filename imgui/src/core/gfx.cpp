#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "gfx.hpp"

using namespace im;

Gfx::Gfx(int width, int height)
    : size{width, height}
    , pixels(width * height * imBytesPerColor)
{
}

Gfx::Gfx(Size size)
    : size(size)
{
}

void Gfx::Resize(Size size)
{
    if (pixels.size() == 0)
    {
        this->size = size;
        pixels.resize(size.Width * size.Height * imBytesPerColor);
    }
    else
    {
        // TODO: size.Resize
    }
}

void Gfx::FillRect(int x1, int y1, int x2, int y2, imColor color)
{
    int rowstep = y2 > y1 ? 1 : -1;
    for (int row = y1; row <= y2; row = row + rowstep)
    {
        DrawLine(x1, row, x2, row, color);
    }
}

void Gfx::DrawLine(int x1, int y1, int x2, int y2, imColor color)
{

    int nDx = x2 - x1;
    int nDy = y2 - y1;

    int nIx = abs(nDx);
    int nIy = abs(nDy);

    int nInc = (nIx > nIy ? nIx : nIy);

    if (nInc < 2)
        return;

    int nJudgeX = -nIy;
    int nJudgeY = -nIx;
    int x = x1;
    int y = y1;

    nInc--;
    int nTwoIx = 2 * nIx;
    int nTwoIy = 2 * nIy;

    for (int i = 0; i < nInc; i++)
    {
        nJudgeX += nTwoIx;
        nJudgeY += nTwoIy;

        bool bPlot = false;

        if (nJudgeX >= 0)
        {
            bPlot = true;
            nJudgeX -= nTwoIy;

            if (nDx > 0)
                x++;
            else if (nDx < 0)
                x--;
        }
        if (nJudgeY >= 0)
        {
            bPlot = true;
            nJudgeY -= nTwoIx;

            if (nDy > 0)
                y++;
            else if (nDy < 0)
                y--;
        }
        if (bPlot)
        {
            if (x >= 0 && y >= 0 && x < size.Width && y < size.Height)
                DrawPixel(x, y, color);
        }
    }
    if (x1 >= 0 && y1 >= 0 && x1 < size.Width && y1 < size.Height)
        DrawPixel(x1, y1, color);
    if (x2 >= 0 && y2 >= 0 && x2 < size.Width && y2 < size.Height)
        DrawPixel(x2, y2, color);
}

void Gfx::DrawCircle(int x, int y, int radius, imColor color)
{

    int px, py, d, x2m1;
    py = radius;
    d = -radius;
    x2m1 = -1;
    px = 0;

    Draw8Pixels(x, y, px, py, color);
    for (px = 1; px < radius / sqrt(2); px++)
    {
        x2m1 += 2;
        d += x2m1;
        if (d >= 0)
        {
            py--;
            d -= (py << 1);
        }
        Draw8Pixels(x, y, px, py, color);
    }
}

void Gfx::FillCircle(int x, int y, int radius, imColor color)
{

    int px, py, d, x2m1;
    py = radius;
    d = -radius;
    x2m1 = -1;
    px = 0;

    DrawInCirPixels(x, y, px, py, color);
    for (px = 1; px < radius / sqrt(2); px++)
    {
        x2m1 += 2;
        d += x2m1;
        if (d >= 0)
        {
            py--;
            d -= (py << 1);
        }
        DrawInCirPixels(x, y, px, py, color);
    }
}

void Gfx::DrawRect(int x1, int y1, int x2, int y2, imColor color)
{
    DrawLine(x1, y1, x1, y2, color);
    DrawLine(x1, y1, x2, y1, color);
    DrawLine(x1, y2, x2, y2, color);
    DrawLine(x2, y1, x2, y2, color);
}

/** draw 8 pixels for circle */
void Gfx::Draw8Pixels(int x, int y, int px, int py, imColor color)
{
    if (((x + px) >= 0 && (y + py) >= 0) && ((x + px) < size.Width && (y + py) < size.Height))
        DrawPixel((x + px), (y + py), color);
    if (((x + px) >= 0 && (y - py) >= 0) && ((x + px) < size.Width && (y - py) < size.Height))
        DrawPixel((x + px), (y - py), color);
    if (((x - px) >= 0 && (y + py) >= 0) && ((x - px) < size.Width && (y + py) < size.Height))
        DrawPixel((x - px), (y + py), color);
    if (((x - px) >= 0 && (y - py) >= 0) && ((x - px) < size.Width && (y - py) < size.Height))
        DrawPixel((x - px), (y - py), color);
    if (((x + py) >= 0 && (y + px) >= 0) && ((x + py) < size.Width && (y + px) < size.Height))
        DrawPixel((x + py), (y + px), color);
    if (((x + py) >= 0 && (y - px) >= 0) && ((x + py) < size.Width && (y - px) < size.Height))
        DrawPixel((x + py), (y - px), color);
    if (((x - py) >= 0 && (y + px) >= 0) && ((x - py) < size.Width && (y + px) < size.Height))
        DrawPixel((x - py), (y + px), color);
    if (((x - py) >= 0 && (y - px) >= 0) && ((x - py) < size.Width && (y - px) < size.Height))
        DrawPixel((x - py), (y - px), color);
}

/** draw the pixels within a circle */
void Gfx::DrawInCirPixels(int x, int y, int px, int py, imColor color)
{
    DrawLine((x + px), (y + py), (x + px), (y - py), color);
    DrawLine((x + py), (y + px), (x + py), (y - px), color);
    DrawLine((x - px), (y + py), (x - px), (y - py), color);
    DrawLine((x - py), (y + px), (x - py), (y - px), color);
}