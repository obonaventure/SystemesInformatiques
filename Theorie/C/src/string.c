/**************************************
 * string.c
 *
 * Programme d'expemple avec les strings
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  ///AAA
  
  char string[10];
  string[0] = 'j';
  string[1] = 'a';
  string[2] = 'v';
  string[3] = 'a';
  string[4] = '\0';
  printf("String : %s\n", string);
  
  ///BBB
  
  return EXIT_SUCCESS;
}
