#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  int m[3][4]= { { 1, 2, 3, 4} ,
		 { 5, 6, 7, 8} ,
		 { 9, 10, 11, 12} };

  printf("%p %d %d %d\n",m, m[1][2], m[0][5], m[2][2]);

  int *ptr;

  ptr=&(m[0][0]);
  printf("%p %d %d %d\n",ptr, *(ptr+4*1+2), *(ptr+4*0+5), *(ptr+2*4+2));

  /* invalide
  int **ptr=m;
  printf("%p %d %d %d\n",ptr, *(ptr+4*1+2), *(ptr+4*0+5), *(ptr+2*4+2));
  */

  /*  invalide
  int *ptr1=m;
  printf("%p %d %d %d\n",ptr1, *(ptr1+4*1+2), *(ptr1+4*0+5), *(ptr1+2*4+2));
   */


  /*

ptr5.c:28:26: warning: format specifies type 'void *' but the argument has type
      'int' [-Wformat]
  printf("%p %d %d %d\n",*ptr, ptr+4*1+2, ptr+4*0+5, ptr+2*4+2);
          ~~             ^~~~
          %d
ptr5.c:28:32: warning: format specifies type 'int' but the argument has type
      'int *' [-Wformat]
  printf("%p %d %d %d\n",*ptr, ptr+4*1+2, ptr+4*0+5, ptr+2*4+2);
             ~~                ^~~~~~~~~
ptr5.c:28:43: warning: format specifies type 'int' but the argument has type
      'int *' [-Wformat]
  printf("%p %d %d %d\n",*ptr, ptr+4*1+2, ptr+4*0+5, ptr+2*4+2);
                ~~                        ^~~~~~~~~
ptr5.c:28:54: warning: format specifies type 'int' but the argument has type
      'int *' [-Wformat]
  printf("%p %d %d %d\n",*ptr, ptr+4*1+2, ptr+4*0+5, ptr+2*4+2);
                   ~~                                ^~~~~~~~~

  ptr=&(m[0][0]);
  printf("%p %d %d %d\n",*ptr, ptr+4*1+2, ptr+4*0+5, ptr+2*4+2);
  */

  /*
  ptr=&(m);
  printf("%p %d %d %d\n",&ptr, *ptr+4*1+2, *ptr+4*0+5, *ptr+2*4+2);
  */



}


