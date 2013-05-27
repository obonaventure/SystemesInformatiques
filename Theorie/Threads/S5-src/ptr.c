/**************************************
 * ptr.c
 *
 * Programme d'exemple pour les pointeurs
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int a=1252;
  int b=1;
  int *p=&a;
  int **pp=&(p);

  printf("a=%d [%p], b=%d [%p], p=%p, *p=%d, pp=%p, *pp=%p, **pp=%d\n",a,&a,b,&b,p,*p,pp,*pp,**pp);

  a++;

  printf("a=%d [%p], b=%d [%p], p=%p, *p=%d, pp=%p, *pp=%p, **pp=%d\n",a,&a,b,&b,p,*p,pp,*pp,**pp);


  *p=*p+1;
  printf("a=%d [%p], b=%d [%p], p=%p, *p=%d, pp=%p, *pp=%p, **pp=%d\n",a,&a,b,&b,p,*p,pp,*pp,**pp);

  *pp=&b;

  printf("a=%d [%p], b=%d [%p], p=%p, *p=%d, pp=%p, *pp=%p, **pp=%d\n",a,&a,b,&b,p,*p,pp,*pp,**pp);



}




