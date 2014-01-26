#include <stdio.h>
#include "bitmap.h"
#include "filter.h"

/* Exemple d'utilisation des fonctions fournies.
 * Vous devez impérativement changer le code ci-dessous.
 */
int main(int argc, char *argv[])
{
	struct image *img;

	if (load_bmp(argv[1], &img)) {
		perror("Error calling load_bmp");
		return 1;
	}

	if (filter_green(img)) {
		perror("Error calling filter_green");
		return 1;
	}

	if (write_bmp(img, argv[2])) {
		perror("Error calling write_bmp");
		return 1;
	}

	return 0;
}
