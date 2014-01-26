#include "bitmap.h"

/* Signature de fonction pour les filtres.
 * Chaque filtre prend une image en argument et
 * lui applique une opération. Retourne 0 en cas
 * de succès, -1 sinon.
 */
typedef int(filter_t)(struct image *);

/* Retire la composante rouge de l'image */
filter_t filter_red;

/* Retire la composante verte de l'image */
filter_t filter_green;

/* Retire la composante bleue de l'image */
filter_t filter_blue;

/* Transforme l'image en niveau de gris en calculant
 * la moyenne sur les différentes composantes.
 */
filter_t filter_grayscale;

/* Ajoute de flou gaussien dans l'image en utilisant la
 * matrice carrée de taille 3 comme matrice de poids:
 *   0.0  0.2  0.0
 *   0.2  0.2  0.2
 *   0.0  0.2  0.0
 *
 * Si on considère la composante rouge de l'image suivante
 * (chaque element a une valeur entre 0 et 255) de taille
 * 6x5:
 *
 *	1  2  5  2  0  3
 *	   -------
 *	3 |2  5  1| 6  0	   0.0*2 + 0.2*5 + 0.0*1 +
 *	  |	   |
 *	4 |3  6  2| 1  4   ->  0.2*3 + 0.2*6 + 0.2*2 +   ->  3.2
 *	  |	   |
 *	0 |4  0  3| 4  2	   0.0*4 + 0.2*0 + 0.0*3
 *	   -------
 *	9  6  5  0  3  9
 *
 * La nouvelle valeur du pixel (3, 4) devient round(3.2) = 3.
 *
 * Lorsque les élements de la matrice se retrouvent en dehors
 * de l'image (c'est-à-dire pour les pixels à la bordure de l'image),
 * la valeur du pixel central sera utilisé pour les valeurs des pixels
 * en dehors des limites de l'image. C'est-à-dire, la nouvelle valeur
 * du pixel (0, 0) dans l'image précédente sera:
 *	0.2 * 0 + 0.2 * 9 + 0.2 * 6 + 0.2 * 9 + 0.2 * 9 = 6.6 -> 7
 */
filter_t filter_blur;

