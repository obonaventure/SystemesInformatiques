// Conversion entre types de données

#include <stdio.h>

int main() {

  #define SIZE 5
  int tab[]={1,-7, 1025,234567890, -2345678901};


  int i;

  for(i=0; i<SIZE;i++) {
    int n=tab[i];
    short s=(short) n;
    long l=(long) n;
    unsigned int ui=(unsigned int) n;
    unsigned char uc=(unsigned char) n;
    unsigned long ul=(unsigned long) n;
    unsigned short us=(unsigned short) n;
  printf("%d -> %d (short) %ld (long) %d (unsigned int) %d (unsigned char) %ld (unsigned long) %d (unsigned short)\n",n,s,l,ui,uc,ul,us);
  }



}

