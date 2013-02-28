
typedef struct image *(filter_t)(struct image *);

/* Ne fait rien */
filter_t filter_identity;

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

/* Ajouter du flou gaussien dans l'image en utilisant la
 * matrice carrée de taille 3 comme matrice de poids:
 *   0.0  0.2  0.0
 *   0.2  0.2  0.2
 *   0.0  0.2  0.0
 *
 * Si on considère la composante rouge de l'image suivante:
 *
 *    1  2  5  2  0  3
 *       -------
 *    3 |2  5  1| 6  0       0.0*2 + 0.2*5 + 0.0*1 +
 *      |       |
 *    4 |3  6  2| 1  4   ->  0.2*3 + 0.2*6 + 0.2*2 +   ->  3.2
 *      |       |
 *    0 |4  0  3| 4  2       0.0*4 + 0.2*0 + 0.0*3
 *       -------
 *    9  6  5  0  3  9
 * 
 * La nouvelle valeur du pixel 6 devient round(3.2) = 3.
 */
filter_t filter_blur;

