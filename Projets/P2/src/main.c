#include "bitmap.h"
#include "filter.h"

int main(int argc, char *argv[])
{
    struct image *img;

    if (load_bmp(argv[1], &img)) {
        perror("Error calling load_bmp");
        return 1;
    }

    img = filter_green(img);

    if (write_bmp(img, argv[2])) {
        perror("Error calling write_bmp");
        return 1;
    }
    
    return 0;
}
