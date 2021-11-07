#include <linux/fb.h>

class FB
{
public:
    FB();
    ~FB();

    void draw(char *b, int w, int h);

private:
    int init();
    int dispose();

    int screen_width;       // screen width
    int screen_height;      // screen height
    int screen_line_len;    // screen width in bytes
    int bits_per_pixel;
    int bytes_per_pixel;
    size_t screen_mem_len;
    struct fb_var_screeninfo bk_vinfo;
    int ffb;
    char *buf;
};