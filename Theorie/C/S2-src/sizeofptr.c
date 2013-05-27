/**********************************************
 * sizeofptr
 *
 * Programme d'exemple d'utilisation de sizeof
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {


  printf("Type\t\t\tTaille\n");
  printf("\n");
  printf("char *\t\t\t%ld octet(s)\n",sizeof(char *));
  printf("unsigned char *\t\t%ld octet(s)\n",sizeof(unsigned char *));
  printf("short *\t\t\t%ld octet(s)\n",sizeof(short *));
  printf("unsigned short *\t%ld octet(s)\n",sizeof(unsigned short *));
  printf("int *\t\t\t%ld octet(s)\n",sizeof(int *));
  printf("unsigned int *\t\t%ld octet(s)\n",sizeof(unsigned int *));
  printf("long *\t\t\t%ld octet(s)\n",sizeof(long *));
  printf("unsigned long *\t\t%ld octet(s)\n",sizeof(unsigned long *));
  printf("long long *\t\t%ld octet(s)\n",sizeof(long long *));
  printf("unsigned long long *\t%ld octet(s)\n",sizeof(unsigned long long *));
  printf("float *\t\t\t%ld octet(s)\n",sizeof(float *));
  printf("double *\t\t%ld octet(s)\n",sizeof(double *));
  printf("long double *\t\t%ld octet(s)\n",sizeof(long double *));

   ///BBB
   return(EXIT_SUCCESS);
}
