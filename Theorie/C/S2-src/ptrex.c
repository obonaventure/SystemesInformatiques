/***********************************************
 * ptrex.c
 *
 * Programme d'exemple d'utilisation de pointeurs
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  ///AAA

  int i = 1;           // entier
  int *ptr_i;          // pointeur vers un entier
  char str[] = "Unix";
  char *s;             // pointeur vers un char

  ptr_i = &i;
  printf("valeur de i : %d, valeur pointée par ptr_i : %d\n", i, *ptr_i);
  *ptr_i = *ptr_i + 1252;
  printf("valeur de i : %d, valeur pointée par ptr_i : %d\n", i, *ptr_i);
  s = str;
  for (i = 0; i < strlen(str); i++){
    printf("valeur de str[%d] : %c, valeur pointée par *(s+%d) : %c\n",
           i, str[i], i, *(s+i));
  }

  ///BBB
  return EXIT_SUCCESS;
}
