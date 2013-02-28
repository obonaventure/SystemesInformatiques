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

    int     hor_res; /* horizontal resolution - DO NOT MODIFY */
    int     ver_res; /* vertical resolution - DO NOT MODIFY */

    /* pixels is an array of size image->width * image->height and represents
     * the RGB-values of each pixel. Starting from the bottom left pixel, going
     * to the right until the bottom right pixel and moving row by row from the
     * bottom to the top.
     */
    struct pixel *pixels;
};

/* Loads the bitmap file specified by 'file' into the newly allocated image
 * 'res_image'.
 *
 * Upon successfull return, *res_image points a newly allocated memory region,
 * containting the bitmap. 0 is returned by the function.
 *
 * Upon error a non-zero value is returned and errno is set appropriatly.
 */
int load_bmp(char *file, struct image **res_image);

/* Writes the bitmap specified by 'img' to the file whose name is 'file'.
 *
 * Upon success, 0 is returned. A non-zero value otherwise and errno is set
 * accordingly.
 */
int write_bmp(struct image *img, char *file);

#endif
