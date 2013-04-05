#include "filter.h"

int filter_green(struct image *img)
{
	int x, y;
	for (x = 0; x < img->width * img->height; ++x)
		img->pixels[x].g = 0;

	return 0;
}

/* TODO implémenter les filtres */
