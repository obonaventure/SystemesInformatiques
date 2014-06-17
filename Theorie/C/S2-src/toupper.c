/***********************************************
 * toupper.c
 *
 * Conversion de caractères
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA

// conversion de minuscules en majuscules
int toUpper(char c) {
  if (c >= 'a' && c <= 'z')
    return c + ('A' - 'a');
  else
    return c;
}
///BBB

int main(int argc, char *argv[])
{

  printf("%c\n",toUpper('g'));
  printf("%c\n",toUpper('='));
  printf("%c\n",toUpper('Z'));
  printf("%c\n",toUpper('x'));

   return EXIT_SUCCESS;
}
