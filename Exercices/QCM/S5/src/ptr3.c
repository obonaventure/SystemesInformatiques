#include <stdio.h>
#include <stdlib.h>

int main() {
  int c;

  int a[3][4]={ {0, 1, 2, 3} ,
		{4, 5, 6, 7} ,
		{8, 9, 10, 11} };


  int *ptr;
  ptr=&(a[0][0]);

  int (*p_ptr)[4];
  p_ptr=a;

 /*
 int a2[][]= { {0, 1} ,
	       {2, 3, 4} ,
	       {5, 6, 7 , 8} };
 */


 int* a1[3];
 int l0[]={0, 1};
 int l1[]={2, 3, 4};
 int l2[]={5, 6, 7, 9};
 a1[0]=l0;
 a1[1]=l1;
 a1[2]=l2;

 /*
 int *a2=(int *) malloc(9*sizeof(int));
 int val=0;
 for(int i=0;i<3;i++) {
   for(int j=0;j<3+j++) {
     *(a2+

 int* a1[3];
 int l0[]={0, 1, 2};
 int l1[]={3, 4, 5};
 int l2[]={6, 7, 8};
 a1[0]=&(l0[0]);
 a1[1]=&(l1[0]);
 a1[2]=&(l2[0]);
 */


 f0: // correct
 printf("%d %d %d \n", a[0][2], a[2][1], a[1][3]);

 f1: // correct
 printf("%d %d %d \n", *(ptr+2), *(ptr+2*4+1), *(*(p_ptr+1)+3));

 f2: // incorrect
 printf("%d %d %d \n", *(ptr+2), *(ptr+2*4+1), *(*(p_ptr+4*1)+3));

 f3: // incorrect
 printf("%d %d %d \n", *(ptr+2), *(ptr+2*3+1), *(*(p_ptr+3*1)+3));


 f4:  // incorrect - compile pas
 printf("%d %d %p \n", *ptr+2, *(ptr+2*4+1), *((p_ptr+1)+3));


 f5:  // incorrect
 printf("%d %d %d \n", *(ptr+2), *(ptr+2*4+1), *(*(p_ptr+1+3)));



}


