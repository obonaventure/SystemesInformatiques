/**************************************
 * qosrt.c
 *
 * Programme d'exemple d'utilisation de qsort
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
///AAA
#define SIZE 5
double array[SIZE]= { 1.0, 7.32, -3.43, 8.7, 9.99 };

void print_array() {
  for(int i=0;i<SIZE;i++)
    printf("array[i]:%f\n",array[i]);
}

int cmp(const void *ptr1, const void *ptr2) {
  const double *a=ptr1;
  const double *b=ptr2;
  if(*a==*b)
    return 0;
  else
    if(*a<*b)
      return -1;
    else
      return +1;
}

int main(int argc, char *argv[]) {

  printf("Avant qsort\n\n");
  print_array();
  qsort(array,SIZE,sizeof(double),cmp);
  printf("Après qsort\n\n");
  print_array();

  return(EXIT_SUCCESS);
}
///BBB
