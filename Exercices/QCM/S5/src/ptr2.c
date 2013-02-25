#include <stdio.h>
#include <stdlib.h>

int a[]={2,4,3,4,8};
int * ptr;
int b;

int main() {
  int c;

  ptr=&(a[0]);

 f0: // correct
  printf("%d %d %d %d\n",a[0],a[1],a[2],a[a[3]]);

 f1: // correct
  printf("%d %d %d %d\n",*ptr,*(ptr+1),*(ptr+2),*(ptr+*(ptr+3)));

 f2: // incorrect
  printf("%d %d %d %d\n",*ptr,*ptr+1,*ptr+2,*(ptr+*(ptr+3)));

 f3: // incorrect
  printf("%d %d %d %d\n",*ptr,*(ptr++),(*ptr++),*(ptr+*(ptr++)));

 f4:  // incorrect
  printf("%d %d %d %d\n",*ptr,*(ptr+0),*(ptr+1),*ptr+*(ptr+2));


 f5:  // incorrect
  printf("%d %d %d %d\n",*ptr,*ptr+1,(*ptr+1),*(ptr+*(ptr+3)));



}


