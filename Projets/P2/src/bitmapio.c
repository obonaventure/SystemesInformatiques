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

u_int32_t power(a, b)
{
    int i;
    int res = 1;
    for (i = 0; i < b ; i++)
        res *= a;

    return res;
}

struct image *load_bmp(char *file)
{
    FILE *fp;
    struct bitmap_file_header hdr;
    struct bitmap_info_header infohdr;
    struct image *img;
    int num_pixels;
    int i;

    img = (struct image *) malloc(sizeof(*img));
    if (!img) {
        perror("Malloc failed");
        return NULL;
    }

    /* open the file */
    if ((fp = fopen(file,"r")) == NULL) {
        printf("Error opening file %s.\n", file);
        perror("");
        return NULL;
    }

    /* Read bitmap header */
    if (fread(&hdr, sizeof(hdr), 1, fp) != 1)
        goto seek_error;

    /* Check format */
    if (hdr.id[0] != 'B' || hdr.id[1] != 'M') {
        printf("%s is not a bitmap file in windows-format.\n", file);
        goto seek_error;
    }

    /* Read bitmap info header */
    if (fread(&infohdr, sizeof(infohdr), 1, fp) != 1)
        goto seek_error;

    if (infohdr.num_colors == 0) {
        /* This means, the number of colors in the color-pallette is 2**bits_per_pixel */
        infohdr.num_colors = power(2, infohdr.bits_per_pixel);
    }

    if (infohdr.color_planes != 1 || infohdr.bits_per_pixel != 24 ||
        infohdr.compression != 0 || infohdr.num_colors != 0 ||
        infohdr.important_colors != 0) {
        printf("The bmp image is not in a supported format!\n");
        goto error;
    }

    img->width = infohdr.width;
    img->height = infohdr.height;
    img->hor_res = infohdr.hor_res;
    img->ver_res = infohdr.ver_res;

    /* Now, move the pointer to the pixel-array */
    if (fseek(fp, infohdr.hdrsize - sizeof(infohdr), SEEK_CUR))
        goto seek_error;

    num_pixels = img->width*img->height;
    img->pixels = (struct pixel *) malloc(sizeof(struct pixel)*num_pixels);
    if (!img->pixels) {
        perror("Error allocating memory");
        goto error;
    }

    for (i = 0; i < num_pixels; i++) {
        if (fread(&img->pixels[i].b, 1, 1, fp) != 1)
            goto seek_error;
        
        if (fread(&img->pixels[i].g, 1, 1, fp) != 1)
            goto seek_error;
        
        if (fread(&img->pixels[i].r, 1, 1, fp) != 1)
            goto seek_error;
    }

    fclose(fp);
    return img;

seek_error:
    perror("Error happened on the file:");
error:
    fclose(fp);
    return NULL;
}


int write_bmp(struct image *img, char *file)
{
    FILE *fp;
    struct bitmap_file_header hdr;
    struct bitmap_info_header infohdr;
    int num_pixels = img->width * img->height;
    int i;
    
    /* open the file */
    if ((fp = fopen(file,"w")) == NULL) {
        printf("Error opening file %s.\n", file);
        perror("");
        return 1;
    }

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
    infohdr.important_colors = 0;

    if (fwrite(&infohdr, sizeof(infohdr), 1, fp) != 1)
        goto write_error;

    for (i = 0; i < num_pixels; i++) {
        if (fwrite(&img->pixels[i].b, 1, 1, fp) != 1)
            goto write_error;

        if (fwrite(&img->pixels[i].g, 1, 1, fp) != 1)
            goto write_error;

        if (fwrite(&img->pixels[i].r, 1, 1, fp) != 1)
            goto write_error;
    }

    fclose(fp);
    return 0;

write_error:
    perror("Error happened on the file:");
    fclose(fp);
    return -1;
}

/**************************************************************************
 *  Main                                                                  *
 *    Draws opaque and transparent bitmaps                                *
 **************************************************************************/

int main(int argc, char *argv[])
{
    struct image *img = load_bmp(argv[1]);

    write_bmp(img, argv[2]);
    
    return 0;
}
