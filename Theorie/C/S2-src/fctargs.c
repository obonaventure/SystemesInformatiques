/***********************************************
 * fctargs.c
 *
 * Programme d'exemple d'utilisation de fonctions
 * montre l'importance de traiter les arguments en
 * ordre
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 5
///AAA
int length(char c[]) {
  int i=0;
  while(c[i]!='\0')
    i++;
  return (i);
}
///BBB

///CCC
void plusun(int size, int *v)
{
  int i;
  for (i = 0; i < size; i++)
    v[i]++;
}

void print_vecteur(int size, int*v) {
  int i;
  printf("v={");
  for (i = 0;i < size - 1; i++)
    printf("%d,", v[i]);
    
  if (size > 0)
    printf("%d}", v[size - 1]);
  else
    printf("}");
}
///DDD

void wrong() {
  int vecteur[N]={1,2,3,4,5};
  /// provoque un segmentation fault
  ///GGG
  plusun(vecteur,N);
  print_vecteur(N,vecteur);
  ///HHH
}


int main(int argc, char *argv[]) {

///EEE
int vecteur[N] = {1, 2, 3, 4, 5};
plusun(N, vecteur);
print_vecteur(N, vecteur);
///FFF

  return EXIT_SUCCESS;
}
