#ifndef BITMAP_H
#define BITMAP_H

struct pixel {
	unsigned char b; /* Bleu */
	unsigned char g; /* Vert */
	unsigned char r; /* Rouge */
} __attribute__((packed));

struct image {
	int	 width;   /* Largeur en pixels */
	int	 height;  /* Hauteur en pixels */

	int	 hor_res; /* Résolution horizontale - Ne pas modifier */
	int	 ver_res; /* Résolution verticale - Ne pas modifier */

	/* pixel est un tableu de taille width * height et représente les composantes
	 * RGB de tous les pixels. Le pixel (0,0) est le pixel en bas à gauche et
	 * le pixel (width-1, height-1) est celui en haut à droite.
	 */
	struct pixel *pixels;
} __attribute__((packed));

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
