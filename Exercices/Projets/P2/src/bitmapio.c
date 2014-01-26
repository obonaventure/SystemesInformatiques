#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

struct bitmap_file_header {
    char        id[2];
    u_int32_t   size;
    char        reserved[4];
    u_int32_t   offset;
} __attribute__((packed));

struct bitmap_info_header {
    u_int32_t   hdrsize;
    int32_t     width;
    int32_t     height;
    int16_t     color_planes; /* Must be 1 */
    int16_t     bits_per_pixel; /* We only support 24 */
    u_int32_t   compression; /* We only support '0' */
    u_int32_t   bitmap_size;
    u_int32_t   hor_res;
    u_int32_t   ver_res;
    u_int32_t   num_colors;
    u_int32_t   important_colors;
} __attribute__((packed));

static u_int32_t power(a, b)
{
    int i;
    int res = 1;
    for (i = 0; i < b ; i++)
        res *= a;

    return res;
}

int load_bmp(char *file, struct image **res_image)
{
    FILE *fp;
    struct bitmap_file_header hdr;
    struct bitmap_info_header infohdr;
    struct image *img;
    int num_pixels;
    int j, pad;


    if (!res_image) {
        printf("**res_image pointer to pointer is not initialized!!!\n");
        errno = -EAGAIN;
        return -EAGAIN;
    }

    img = (struct image *) malloc(sizeof(*img));
    if (!img)
        return errno;

    *res_image = img;

    /* open the file */
    if ((fp = fopen(file,"r")) == NULL)
        return errno;

    /* Read bitmap header */
    if (fread(&hdr, sizeof(hdr), 1, fp) != 1)
        goto error;

    /* Check format */
    if (hdr.id[0] != 'B' || hdr.id[1] != 'M') {
        printf("%s is not a bitmap file in windows-format.\n", file);
        errno = -EAGAIN;
        goto error;
    }

    /* Read bitmap info header */
    if (fread(&infohdr, sizeof(infohdr), 1, fp) != 1)
        goto error;

    if (infohdr.color_planes != 1 || infohdr.bits_per_pixel != 24 ||
        infohdr.compression != 0 || infohdr.num_colors != 0 ||
        infohdr.important_colors != 0) {
        printf("The bmp image is not in a supported format!\n");
        printf("The supported format requires: colorplanes == 0, 24 bits per "
               "pixel, no compression, num-colors == 0 and important-colors == 0\n");
        printf("But we got: colorplanes %u bits per pixel %u compression %u "
               "num-colors %u important-colors %u\n", infohdr.color_planes,
               infohdr.bits_per_pixel, infohdr.compression, infohdr.num_colors,
               infohdr.important_colors);
        errno = -EAGAIN;
        goto error;
    }

    if (infohdr.num_colors == 0)
        /* This means, the number of colors in the color-pallette is 2**bits_per_pixel */
        infohdr.num_colors = power(2, infohdr.bits_per_pixel);

    img->width = infohdr.width;
    img->height = infohdr.height;
    img->hor_res = infohdr.hor_res;
    img->ver_res = infohdr.ver_res;

    /* Now, move the pointer to the pixel-array */
    if (fseek(fp, infohdr.hdrsize - sizeof(infohdr), SEEK_CUR))
        goto error;

    num_pixels = img->width * img->height;
    img->pixels = (struct pixel *) malloc(sizeof(struct pixel)*num_pixels);

    if (!img->pixels)
        goto error;

    pad = (4 - (img->width * 3) % 4) % 4;
    for (j = 0; j < img->height; j++) {
        if (fread(&img->pixels[j*img->width], 3, img->width, fp) != img->width)
            goto error;

        if (fseek(fp, pad, SEEK_CUR))
            goto error;
    }

    fclose(fp);
    return 0;

error:
    fclose(fp);
    return errno;
}

int write_bmp(struct image *img, char *file)
{
    FILE *fp;
    struct bitmap_file_header hdr;
    struct bitmap_info_header infohdr;
    int num_pixels = img->width * img->height;
    int j, pad;
    struct pixel padding = {0,0,0};


    /* open the file */
    if ((fp = fopen(file,"w")) == NULL)
        return errno;

    hdr.id[0] = 'B';
    hdr.id[1] = 'M';
    hdr.size = sizeof(hdr) + sizeof(infohdr) + num_pixels * 3;
    hdr.reserved[0] = 0;
    hdr.reserved[1] = 0;
    hdr.reserved[2] = 0;
    hdr.reserved[3] = 0;
    hdr.offset = sizeof(hdr) + sizeof(infohdr);

    if (fwrite(&hdr, sizeof(hdr), 1, fp) != 1)
        goto write_error;

    infohdr.hdrsize = sizeof(infohdr);
    infohdr.width = img->width;
    infohdr.height = img->height;
    infohdr.color_planes = 1;
    infohdr.bits_per_pixel = 24;
    infohdr.compression = 0;
    infohdr.bitmap_size = num_pixels * 3;
    infohdr.num_colors = 0;
    infohdr.hor_res = img->hor_res;
    infohdr.ver_res = img->ver_res;
    infohdr.important_colors = 0;

    if (fwrite(&infohdr, sizeof(infohdr), 1, fp) != 1)
        goto write_error;

    pad = (4 - (img->width * 3) % 4) % 4;
    for (j = 0; j < img->height; j++) {
        if (fwrite(&img->pixels[j*img->width], 3, img->width, fp) != img->width)
            goto write_error;

        if (fwrite(&padding, 1, pad, fp) != pad)
            goto write_error;
    }

    fclose(fp);
    return 0;

write_error:
    fclose(fp);
    return errno;
}
