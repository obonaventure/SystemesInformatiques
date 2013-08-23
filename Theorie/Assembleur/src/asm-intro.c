/**************************************
 * var.c
 *
 * Programme d'exemple pour localiser
 * les variables en mémoire
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>



int global_int=1;
int global_i=1;
int global_j=1;
float global_float=1.0;
char global_char='c';

int add() {
  int v=global_i+global_j;
  return(v);
}

int sum(int i, int j) {
  return (i+j);
}

int sumn(int n) {
  if(n>0)
     return (n + sumn(n-1));
  else
    return n;
}


int while_loop(void) {
  int i=1;
  int j=17;
  while(i<j)
    i=i+2;
  return i;
}

int main(int argc, char *argv[]) {

  int local_int=1;
  float local_float=1.0;
  char local_char='c';
  printf("while0=%d\n",while_loop());
  printf("add=%d\n",add());
  printf("sumn(3)=%d\n",sumn(3));
  return(EXIT_SUCCESS);
}
