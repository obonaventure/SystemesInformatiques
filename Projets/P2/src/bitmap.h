#ifndef BITMAP_H
#define BITMAP_H

struct pixel {
    unsigned char b; /* Bleu */
    unsigned char g; /* Vert */
    unsigned char r; /* Rouge */
} __attribute__((packed));

struct image {
    int     width;   /* Largeur en pixels */
    int     height;  /* Hauteur en pixels */

    int     hor_res; /* Résolution horizontale - Ne pas modifier */
    int     ver_res; /* Résolution verticale - Ne pas modifier */

    /* pixels is an array of size image->width * image->height and represents
     * the RGB-values of each pixel. Starting from the bottom left pixel, going
     * to the right until the bottom right pixel and moving row by row from the
     * bottom to the top.
     */
    struct pixel *pixels;
};

/* Charge le bitmap spécifié par 'file' dans la nouvelle image 'res_image'.
 *
 * Si la fonction retourne 0 (succès), *res_image pointe vers une nouvelle
 * zone mémoire allouée contenant le bitmap. Si la fonction retourne une
 * une valeur différente de zero, une erreur s'est produite et la valeur 
 * errno est mis à jour.
 */
int load_bmp(char *file, struct image **res_image);

/* Ecrit le bitmap spécifié par 'img' dans le fichier nomé 'file'.
 *
 * Si l'écriture est réussie, 0 est renvoyé. Lors d'une erreur, une valeur
 * différente de zero est renvoyée et errno est mis à jour.
 */
int write_bmp(struct image *img, char *file);

#endif
