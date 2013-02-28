#include "bitmap.h"
#include "filter.h"

struct image *filter_identity(struct image *img)
{
    return img;
}


struct image *filter_green(struct image *img)
{
    int x, y;
    for (x = 0; x < img->width; ++x)
        for (y = 0; y < img->height; ++y)
            img->pixels[x * img->height + y].g = 0;
    return img;
}
