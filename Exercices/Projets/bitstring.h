#ifndef __BITSTRING_H__
#define __BITSTRING_H__

/* /!\ Fichier à ne pas changer */

struct bitstring;
/* A vous de définir votre structure dans bitstring.c */

typedef struct bitstring bitstring_t;
typedef unsigned char bit_t;

/* Alloue une bitstring de <code>n</code> bits initialisés à 0 */
bitstring_t *bitstring_alloc(size_t n);

/* Met le <code>n</code>ième bit à la valeur de <code>bit</code>
 * du bitstring <code>b</code>
 *
 * <code>n</code> est plus grand ou égale à 0 et strictement plus petit que 
 * <code>bitstring_len(b)</code>
 */
void bitstring_set(bitstring_t *b, unsigned int n, bit_t bit);

/* Retourne la valeur du <code>n</code>ième bit du bitstring <code>b</code>
 *
 * <code>n</code> est plus grand ou égale à 0 et strictement plus petit que 
 * <code>bitstring_len(b)</code>
 */
bit_t bitstring_get(bitstring_t *b, int n);

/* Renvoi la longueur du bitstring */
size_t bitstring_len(bitstring_t *b);

/* Applique une rotation vers la gauche de <code>n</code> bits sur le bitstring
 * <code>b</code>.
 * Par exemple, pour un <code>b = 0111101</code> et <code>n = 3</code>,
 * <code>b</code> deviendra <code>1101011</code> après l'appel à cette fonction.
 */
void bitstring_rotate(bitstring_t *b, int n);

/* Applique un déclage de <code>n</code> bits vers la gauche sur le bitstring
 * <code>b</code> sans perte d'information. Les nouveaux bits ajoutés sont des
 * <code>0</code>. Après l'appel de cette fonction le nombre de bits de
 * <code>b</code> est donc augementée de <code>n</code>.
 * Par exemple, pour un <code>b = 0111101</code> et <code>n = 3</code>,
 * <code>b</code> deviendra <code>0111101000</code> après l'appel à cette
 * fonction.
 */
void bitstring_shift(bitstring_t *b, int n);

/* Effectue l'opération ou exclusif entre <code>b1</code> et <code>b2</code> 
 * (<code>b1 ^ b2</code>).
 *
 * Le résultat est fourni à l'appellant via <code>res</code>.
 * La valeur de retour est 0 en cas de succès, -1 en cas d'erreur.
 */
int bitstring_xor(bitstring_t *b1, bitstring_t *b2, bitstring_t **res);

/* Affiche en représentation hexadécimale le bitstring <code>b</code> dans
 * le buffer <code>buf</code> de taille <code>*len</code>. Retourne 
 * <code>-1</code> si le buffer ne peut contenir toute la representation.
 * Retourne <code>0</code> sinon. <code>len</code> est mis à jour pour valoir
 * le nombre de caractères hexadécimals affiché dans <code>buf</code> + le
 * caractère '\0'.
 */
int bitstring_print(bitstring_t *b, char *buf, size_t *len);

/* Libère la mémoire du bitstring */
void bitstring_free(bitstring_t *b);

#endif
