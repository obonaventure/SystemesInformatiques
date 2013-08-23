/**************************************
 * fctptr.c
 *
 * Programme d'exemple pour les pointeurs
 * vers des fonctions
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
///AAA
int g=1;
int debug_level;

void empty (char *str) {
  return;
}

void oneline(char *str) {
  fprintf(stderr,"debug: %s\n",str);
}

void detailed(char *str) {
  fprintf(stderr, "debug: %s\n",str);
  fprintf(stderr,"g=%d\n",g);
}

void (* debug_print[])(char *) = { empty,
				   oneline,
				   detailed };

int main(int argc, char *argv[]) {

  if(argc!=2)
    return(EXIT_FAILURE);

  debug_level=atoi(argv[1]);
  if((debug_level<0) || (debug_level>2) )
    return(EXIT_FAILURE);
  printf("fct debug_print : %p\n",debug_print[debug_level]);
  (debug_print[debug_level])("Hello");

   return(EXIT_SUCCESS);
}
///BBB
