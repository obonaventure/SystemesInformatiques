/**********************************************
 * int2bin
 *
 * Conversion d'entier non signé en binaire
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 33 // nombre maximum de bits+1

void print_bin(int num) {
  int i;
  int n=num;
  char str[MAXSIZE];
  i=MAXSIZE;
  while (--i>=0) {
    str[i] = n & 1 ? '1' : '0';
    n >>= 1;
  }
  printf("La valeur de %d en hexadécimal est %x  et en binaire : %s\n",num,num,str);

}

int main(int argc, char *argv[]) {

  int n=7654321;
  print_bin(n);
  print_bin(123);
  print_bin(987654321);

  return(EXIT_SUCCESS);
}

// inspiré de http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
