/**************************************
 * longjmp.c
 *
 * Programme d'exemple de longjmp
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf label;

void f() {

  printf("Début fonction f\n");
  if(setjmp(label)==0) {
    printf("Exécution normale\n");
  }
  else {
    printf("Exécution après longjmp\n");
  }
}

void g() {
  printf("Début fonction g\n");
  longjmp(label,1);
  printf("Ne sera jamais affiché\n");
}

int main (int argc, char *argv[])  {
  f();
  g();
  return(EXIT_SUCCESS);
}
///BBB
