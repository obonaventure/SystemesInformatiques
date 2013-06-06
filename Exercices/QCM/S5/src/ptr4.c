#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  int i=0;

 f0: // correct
  while(i<argc) {
    printf("%d %p %s\n",i,&(argv[i]),argv[i]);
    i++;
  }


  i=0;
  char **ptr3;
  ptr3=argv;
  while(i<argc) {
    printf("%d %p %s\n",i,&(*ptr3),*ptr3);
    i++;
    ptr3++;
  }

  i=0;
  char **ptr;
  ptr=argv;
  while(i<argc) {
    printf("%d %p %s\n",i,&(ptr),*ptr);
    i++;
    ptr++;
  }



  // provoque un segmentation fault
  /*
  i=0;
  char *ptr2;
  ptr2=*argv;
  while(i<argc) {
    printf("%d %p %s\n",i,&(ptr2),*ptr2);
    i++;
    ptr2++;
  }
  */

  /* ptr4.c:50:27: error: address expression must be an lvalue or a function
      designator
    printf("%d %p %s\n",i,&(argv+i),*(argv+i));


  i=0;
  while(i<argc) {
    printf("%d %p %s\n",i,&(argv+i),*(argv+i));
    i++;
  }

  */
  /*
ptr4.c:61:40: warning: format specifies type 'char *' but the argument has type
      'char **' [-Wformat]
    printf("%d %p %s\n",i,&(*(argv+i)),(argv+i));
                  ~~                   ^~~~~~~~

  i=0;
  while(i<argc) {
    printf("%d %p %s\n",i,&(*(argv+i)),(argv+i));
    i++;
  }

  */




}


