#include "filter.h"

int filter_green(struct image *img)
{
    int x, y;
    for (x = 0; x < img->width; ++x)
        for (y = 0; y < img->height; ++y)
            img->pixels[x * img->height + y].g = 0;
    return 0;
}

/* TODO implémenter les filtres */
