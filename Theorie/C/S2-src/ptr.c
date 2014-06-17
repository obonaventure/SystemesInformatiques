/***********************************************
 * ptr
 *
 * Programme d'exemple d'utilisation de pointeurs
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  ///AAA

  int i = 1252;
  char str[] = "sinf1252";
  char c = 'c';

  printf("i vaut %d, occupe %ld bytes et est stocké à l'adresse : %p\n", 
         i, sizeof(i), &i);
  printf("c vaut %c, occupe %ld bytes et est stocké à l'adresse : %p\n", 
         c, sizeof(c), &c);
  printf("str contient \"%s\" et est stocké à partir de l'adresse : %p\n", 
         str, &str);
  
  ///BBB
  return EXIT_SUCCESS;
}
