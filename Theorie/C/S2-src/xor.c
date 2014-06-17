/***********************************************
 * xor.c
 *
 * Programme d'exemple d'encryptage avec XOR
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// affiche un message d'erreur
void usage(char *msg)
{
  fprintf(stderr,"Usage : %s\n",msg);
  exit(EXIT_FAILURE);
}

///AAA
int main(int argc, char* argv[])
{
  if (argc != 2)
    usage("ce programme prend une clé comme argument");

  char *key = argv[1];
  char c;
  int i = 0;
  while (((c = getchar()) != EOF) && (i < strlen(key))) {
    putchar(c ^ *(key + i));
    i++;
  }
  return EXIT_SUCCESS;
}
///BBB
