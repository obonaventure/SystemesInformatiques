/**************************************
 * enum.c
 *
 * Programme d'exemple de enum
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA
// les jours de la semaine
typedef enum  {
      monday, tuesday, wednesday, thursday, friday, saturday, sunday
   } day;

// jeu de carte
typedef enum {
  coeur, carreau, trefle, pique
} carte;

// bits
typedef enum {
        BITRESET = 0,
        BITSET = 1
} bit_t;

///BBB


int main(int argc, char *argv[]) {
  ///CCC
  bit_t bit=BITRESET;
  day jour=monday;
  if(jour==saturday||jour==sunday)
    printf("Congé\n");
  ///DDD
  printf("jour: %d\n",jour);
  printf("sizeof(day) %ld\n",sizeof(day));
  printf("sizeof(bit_t) %ld\n",sizeof(bit_t));


  return(EXIT_SUCCESS);
}
