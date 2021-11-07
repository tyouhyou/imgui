#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "gfxpainter.hpp"
#include "cxxlog.hpp"

/* To flush out any errors */
#ifdef DEBUG
#define XSYNC(dpy, do) XSynchronize(dpy, True)
#else
#define XSYNC(dpy, do)
#endif

int draw();
void refresh(XImage *xi, GfxPainter &painter);

int main(int argc, char *argv[])
{
    IE << "run on X";
    draw();
}

int draw()
{
    int width = 320, height = 240;

    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        EE << "Cannot open display";
        return 1;
    }

    XSYNC(display, True);

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, 
                        RootWindow(display, screen), 
                        0, 0, width, height, 1,
                        BlackPixel(display, screen),
                        WhitePixel(display, screen));
    
    int depth = DefaultDepth(display, screen);
    IE << "default depth is " << depth;

    Atom del_window = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(display, window, &del_window, 1);

    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask| ButtonReleaseMask | PointerMotionMask);
    XMapWindow(display, window);

    GC gc = DefaultGC(display, screen);

    // 32 is for test
    int paint_depth = 32;
    GfxPainter painter{width, height};
    auto data = (unsigned int*)painter.PaintShapes();

    XImage *xi = XCreateImage(display,
                    DefaultVisual(display, screen),
                    depth, ZPixmap, 0, (char*)data, 
                    width, height, paint_depth,  0);
    if (xi == NULL)
    {
        IE << "null ximage";
        return 2;
    }

    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        switch (event.type) {
            case KeyPress:
                //IE << "key preessed";
                //goto endwhile;
                continue;
            case ClientMessage:
                IE << "client message";
                goto endwhile;
            case Expose:
                refresh(xi, painter);
                XPutImage(display, window, gc, xi, 0,0, 0, 0, xi->width, xi->height);
                usleep(30000);
        }
    }
endwhile:

    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}

void refresh(XImage *xi, GfxPainter &painter)
{
    auto data = (unsigned int*)painter.PaintShapes();
	for (int y = 0; y < xi->height; ++y)
    {
       for (int x = 0; x < xi->width; ++x)
        {
            unsigned int rgb = *data++;
            XPutPixel(xi, x, y, rgb);
        } 
    }
}

// not used
int make_gc_depth(int depth, Display *dpy, Window scr, Window root, GC *gc)
{

    Window win;
    Visual *visual;
    XVisualInfo vis_info;
    XSetWindowAttributes win_attr;
    unsigned long win_mask;

    if(!XMatchVisualInfo(dpy, scr, depth, TrueColor, &vis_info)) {
            EE << " * ERR: " << depth << "depth not supported";
            return 1;
    }

    visual = vis_info.visual;

    win_attr.colormap = XCreateColormap(dpy, root, visual, AllocNone);
    win_attr.background_pixel = 0;
    win_attr.border_pixel = 0;

    win_mask = CWBackPixel | CWColormap | CWBorderPixel;

    IE << "create window -> color depth " << depth;
    win = XCreateWindow(
                    dpy, root,
                    0, 0,
                    320, 240,        /* dummy size */
                    0, depth,
                    InputOutput, visual,
                    win_mask, &win_attr);
    XSYNC(display, True);

    *gc = XCreateGC(dpy, win, 0, 0);
    XSYNC(display, True);

    XDestroyWindow(dpy, win);
    XSYNC(display, True);

    return 0;
}
