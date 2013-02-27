#ifndef BITMAP_H
#define BITMAP_H

struct pixel {
    unsigned char b; /* Blue */
    unsigned char g; /* Green */
    unsigned char r; /* Red */
};

struct image {
    int     width;   /* Width in pixels */
    int     height;  /* Height in pixels */
    int     hor_res; /* horizontal resolution */
    int     ver_res; /* vertical resolution */
    struct pixel *pixels;
};

#endif
