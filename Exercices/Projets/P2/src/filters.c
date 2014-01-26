#include "filter.h"
#include <stdio.h>

int filter_green(struct image *img)
{
    int x, y;
    for (x = 0; x < img->width; ++x) {
        for (y = 0; y < img->height; y++)
                img->pixels[x + y * img->width].g = 0;
    }

    return 0;
}

/* TODO implémenter les filtres */
