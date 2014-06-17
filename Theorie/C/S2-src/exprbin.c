/***********************************************
 * exprbin.c
 *
 * Programme d'exemple d'utilisation d'expressions
 * binaires
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>
#define BITS_CHAR 8

///EEE
#define BITS_INT 32
// str[BITS_INT]
void int2bin(unsigned int num, char *str)
{
  int i;
  str[BITS_INT] = '\0';
  for (i = BITS_INT - 1; i >= 0; i--) {
    if ((num & 1) == 1)
      str[i] = '1';
    else
      str[i] = '0';
    num = num >> 1;
  }
}
///FFF

// str[32]
void char2bin(unsigned char num, char *str)
{
  int i;
  str[BITS_CHAR]='\0';
  for(i=BITS_CHAR-1; i>=0; i--) {
    if( (num & 1)==1)
      str[i]='1';
    else
      str[i]='0';
    num = num >> 1;
  }
}



int main(int argc, char *argv[]) {

  unsigned char zero='\0'; ///EEE
  unsigned char a=0xFA;
  unsigned char b=0x5F;
  unsigned char c=0x50;
  unsigned char d=0x50;

  unsigned char r;
  unsigned int i1,i2,i3;
  i1=0;
  i2=0x4;
  i3=0x5;

  char str1[32];
  char str2[32];
  char str3[32];

  char2bin(zero,str1);
  char2bin(~zero,str2);
  printf("~ %s = %s\n",str1,str2);
  char2bin(a,str1);
  char2bin(b,str2);
  char2bin(a&b,str3);
  printf("%s & %s = %s\n",str1,str2,str3);
  char2bin(a,str1);
  char2bin(b,str2);
  char2bin(a|b,str3);
  printf("%s | %s = %s\n",str1,str2,str3);
  char2bin(a^b,str3);
  printf("%s ^ %s = %s\n",str1,str2,str3);

///AAA

r = ~a;    // négation bit à bit
r = a & b; // conjonction bit à bit
r = a | b; // disjonction bit à bit
r = a ^ b; // xor bit à bit

///BBB

///CCC

r = c & 0x7E; // 0b01111110 force les bits de poids faible et fort à 0
r = d | 0x18; // 0b00011000 force les bits 4 et 3 à 1

///DDD

  /*
  printf("0x%x & 0x%x = 0x%x\n",i2,i3,i2 & i3);
  printf("0x%x && 0x%x = 0x%8x\n",i2,i3,i2 && i3);
  printf("0x%x | 0x%x = 0x%8x\n",i2,i3,i2 | i3);
  printf("0x%x || 0x%x = 0x%8x\n",i2,i3,i2 || i3);
  */

  return(EXIT_SUCCESS);
}
