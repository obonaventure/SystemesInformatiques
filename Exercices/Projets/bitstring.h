#ifndef __BITSTRING_H__
#define __BITSTRING_H__

/* /!\ Fichier à ne pas changer */

struct bitstring;
/* A vous de définir votre structure dans bitstring.c */

typedef struct bitstring bitstring_t;
typedef unsigned char bit_t;

/* Alloue une bitstring de <code>n</code> bits initialisés à 0 */
bitstring_t * bitstring_alloc(int n);

/* Met le <code>n</code>ième bit à la valeur de <code>bit</code>
 * du bitstring <code>b</code>
 */
void bitstring_set(bitstring_t *b, int n, bit_t bit);

/* Retourne la valeur du <code>n</code>ième bit du bitstring <code>b</code> */
bit_t bitstring_get(bitstring_t *b, int n);

/* Applique une rotation vers la droite de <code>n</code> bits sur le bitstring
 * <code>b</code>.
 * Par exemple, pour un <code>b = 0111101</code> et <code>n = 3</code>,
 * <code>b</code> deviendra <code>1010111</code> après l'appel à cette fonction.
 */
void bitstring_rotate(bitstring_t *b, int n);

/* Applique un déclage de <code>n</code> bits vers la droite sur le bitstring
 * <code>b</code> sans perte d'information. Les nouveaux bits ajoutés sont des
 * <code>0</code>. Après l'appel de cette fonction le nombre de bits de
 * <code>b</code> est donc augementée de <code>n</code>.
 * Par exemple, pour un <code>b = 0111101</code> et <code>n = 3</code>,
 * <code>b</code> deviendra <code>0000111101</code> après l'appel à cette fonction.
 */
void bitstring_shift(bitstring_t *b, int n);

/* Effectue l'opération ou exclusif entre <code>b1</code> et <code>b2</code> 
 * (<code>b1 ^ b2</code>). Retourne le résultat sous forme d'un nouveau
 * bitstring si <code>b1</code> et <code>b2</code> sont de même taille,
 * <code>NULL</code> sinon. <code>b1</code> et <code>b2</code> restent
 * intouchés.
 */
bitstring_t *bitstring_xor(bitstring_t *b1, bitstring_t *b2);

/* Affiche en représentation hexadécimale le bitstring <code>b</code> dans
 * le buffer <code>buf</code> de taille <code>*len</code>. Retourne 
 * <code>-1</code> si le buffer ne peut contenir toute la representation.
 * Retourne <code>0</code> sinon. <code>len</code> est mis à jour pour valoir
 * le nombre de caractères hexadécimals affiché dans <code>buf</code> + le
 * caractère '\0'.
 */
int bitstring_print(bitstring_t *b, char *buf, size_t *len);

#endif
