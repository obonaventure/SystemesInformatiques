#ifndef __BITSTRING_H__
#define __BITSTRING_H__

/* /!\ Fichier à ne pas changer */

#include <stdlib.h>

struct bitstring;
/* A vous de définir votre structure dans bitstring.c */

typedef struct bitstring bitstring_t;
typedef enum {
        BITNULL = 0,
        BITSET = 1
} bit_t;

/* Alloue un bitstring de 'n' bits initialisés à 0.
 * 'n' est un multiple de 8!
 *
 * En cas d'erreur, NULL est retourné.
 */
bitstring_t *bitstring_alloc(size_t n);

/* Alloue un bitstring dont la séquence de bits représente 'x'.
 *
 * En cas d'erreur, NULL est retourné.
 */
bitstring_t *bitstring_alloc_from_int(unsigned int x);

/* Met le n'ième bit du bitstring 'b' à la valeur de 'bit'.
 * Pour trouver le n'ième bit on compte à partir du bit de poids fort.
 *
 * 'n' est plus grand ou égal à 0 et strictement plus petit que
 * bitstring_len(b)
 */
void bitstring_set(bitstring_t *b, unsigned int n, bit_t bit);

/* Retourne la valeur du n'ième bit du bitstring 'b'
 * Pour trouver le n'ième bit on compte à partir du bit de poids fort.
 *
 * 'n' est plus grand ou égal à 0 et strictement plus petit que
 * bitstring_len(b)
 */
bit_t bitstring_get(bitstring_t *b, int n);

/* Renvoi la longueur du bitstring */
size_t bitstring_len(bitstring_t *b);

/* Applique une rotation vers la gauche de 'n' bits sur le bitstring
 * 'b'.
 * Par exemple, pour un b = 00111101 et n = 3,
 * b deviendra 11101001 après l'appel à cette fonction.
 */
void bitstring_rotate(bitstring_t *b, int n);

/* Concate les bitstrings de 'b1' et 'b2'.
 *
 * Le résultat est stocké dans 'b1'.
 *
 * Retourne 0 en cas de succès, -1 en cas d'erreur.
 */
int bitstring_concat(bitstring_t *b1, bitstring_t *b2);

/* Effectue l'opération ou exclusif entre 'b1' et 'b2'
 * (b1 ^ b2).
 *
 * Si les bitstring 'b1' et 'b2' sont de taille
 * différente, une erreur est renvoyée. Sinon, le résultat est fourni à
 * l'appellant via 'res'. 'b1' et 'b2' sont inchangés.
 *
 * La valeur de retour est 0 en cas de succès, -1 en cas d'erreur.
 */
int bitstring_xor(bitstring_t *b1, bitstring_t *b2, bitstring_t **res);

/* Affiche en représentation hexadécimale le bitstring 'b' dans
 * le buffer 'buf' de taille 'len'.
 * Retourne -1 si le buffer ne peut contenir toute la representation.
 * Retourne le nombre de caractères hexadécimals (+'\0') écrits sinon.
 */
int bitstring_print(bitstring_t *b, char *buf, size_t len);

/* Libère la mémoire du bitstring */
void bitstring_free(bitstring_t *b);

#endif
