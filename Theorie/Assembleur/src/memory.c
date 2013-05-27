/**************************************
 * memory.c
 *
 * Programme de manipulation de la mémoire
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>


#define SIZE 1000000

struct s1 {
  int i;
  char c[1];
  int j;
};

struct s100 {
  int i;
  char c[100];
  int j;
};


int main(int argc, char *argv[]) {

  struct s1 *s1_ptr=(struct s1 *)malloc(sizeof(struct s1)*SIZE);
  struct s100 *s100_ptr=(struct s100 *)malloc(sizeof(struct s100)*SIZE);


  return(EXIT_SUCCESS);
}
