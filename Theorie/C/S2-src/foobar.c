/***********************************************
 * foobar.c
 *
 * Exercice
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
void foo(void) {
  int a = 42;
}

void bar(void) {
  int a;
  printf("%d\n", a);
}

int main(int argc, char *argv[]) {
  foo();
  bar();
  return(EXIT_SUCCESS);
}
