/***********************************************
 * strlen.c
 *
 * Calcul de longueur de chaînes avec pointeurs
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA

int length(char *s)
{
  int i = 0;
  while (*(s+i) != '\0')
    i++;
  return i;
}

///BBB

int main(int argc, char *argv[])
{
  int i;
  char name1[] = "str";
  //  char name2[] = "SINF1252";

  printf("Longueur de name1 [%s] : %d\n", name1, length(name1));
  for (i = 0; i < 10; i++) {
    printf("%c", name1[i]);
  }

  return EXIT_SUCCESS;
}

