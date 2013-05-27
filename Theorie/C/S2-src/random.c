/***********************************************
 * random
 *
 * Utilisation de nombres aléatoires
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  ///AAA

 long int r;
 int i;
 int pair=0;
 unsigned int seed=1252;  // semence initiale
 srandom(seed);
 for(i=0;i<10000;i++) {
   r=random();
   if (r%2==0)
     pair++;
 }
 printf("%d nombres pairs ont été générés\n",pair);
   ///BBB
   return(EXIT_SUCCESS);
}

