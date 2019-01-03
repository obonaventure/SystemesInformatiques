// arithmétique des pointeurs

#include <stdio.h>

int main(int argc, char *argv[])
{
///AAA
  
#define SIZE 3
unsigned int tab[3];
tab[0] = 0x01020304;
tab[1] = 0x05060708;
tab[2] = 0x090A0B0C;

///BBB

///CCC
  
int i;
for (i = 0; i < SIZE; i++) {
  printf("%X est à l'adresse %p\n", tab[i], &(tab[i]));
}

///DDD

///EEE
  
unsigned int* ptr = tab;
for (i = 0; i < SIZE; i++) {
  printf("%X est à l'adresse %p\n", *ptr, ptr);
  ptr++;
}

///FFF

///GGG
  
unsigned char* ptr_char = (unsigned char *) tab;
printf("ptr_char contient %p\n", ptr_char);
for (i = 0; i < SIZE + 1; i++) {
  printf("%X est à l'adresse %p\n", *ptr_char, ptr_char);
  ptr_char++;
}

///HHH
}
