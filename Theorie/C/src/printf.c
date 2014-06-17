/**************************************
 * printf.c
 *
 * Exemples d'utilisation de printfProgramme qui a réussi
 *
 **************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  ///AAA
  
  char weekday[] = "Monday";
  char month[] = "April";
  int day = 1;
  int hour = 12;
  int min = 42;
  char str[] = "SINF1252";
  int i;
  
  // affichage de la date et l'heure
  printf("%s, %s %d, %d:%d\n", weekday, month, day, hour, min);
  
  // affichage de la valeur de PI
  printf("PI = %f\n", 4 * atan(1.0));
  
  // affichage d'un caractère par ligne
  for(i = 0; str[i] != '\0'; i++)
    printf("%c\n", str[i]);
    
  ///BBB
  
  return EXIT_SUCCESS;
}
