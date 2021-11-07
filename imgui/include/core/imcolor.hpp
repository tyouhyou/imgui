#pragma once

#define im_COLORTYPE_ARGB 0

#ifndef im_COLORTYPE
#define im_COLORTYPE im_COLORTYPE_ARGB32 // default color type
#endif

// TOOD: define in ColorType class
#if (im_COLORTYPE == im_COLORTYPE_ARGB32)

typedef unsigned int imColor;

#define imColorDepth 32
#define imBytesPerColor (imColorDepth / 8)

#define imAlphaMask 0xFF000000
#define imRedMask 0x00FF0000
#define imGreenMask 0x0000FF00
#define imBlueMask 0x000000FF
#define imAlphaShift 24
#define imRedShift 16
#define imGreenShift 8
#define imBlueShift 0

// #define imAlphaMask 0x000000FF
// #define imRedMask 0x0000FF00
// #define imGreenMask 0x00FF0000
// #define imBlueMask 0xFF000000
// #define imAlphaShift 0
// #define imRedShift 8
// #define imGreenShift 16
// #define imBlueShift 24

#endif // color definition: im_COLORTYPE_ARGB32

// #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
// #elif __APPLE__ // mac
// #else // linux
// #endif // os

#define imMaskAlpha(color) (color & imAlphaMask)
#define imMaskRed(color) (color & imRedMask)
#define imMaskGreen(color) (color & imGreenMask)
#define imMaskBlue(color) (color & imBlueMask)

#define imSetAlpha(alpha, baseColor) (imMaskAlpha(alpha << imAlphaShift | baseColor))
#define imSetRed(red, baseColor) (imMaskRed(red << imRedShift) | baseColor)
#define imSetGreen(green, baseColor) (imMaskGreen(green << imGreenShift) | baseColor)
#define imSetBlue(blue, baseColor) (imMaskBlue(blue << imBlueShift) | baseColor)

#define imARGB(a, r, g, b) (a << imAlphaShift | r << imRedShift | g << imGreenShift | b << imBlueShift)
