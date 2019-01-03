#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct fraction {
    int num;
    int den;
};


struct fraction * simp1(struct fraction f);
struct fraction * simp2(struct fraction * f);
struct fraction simp3(struct fraction f) {
  struct fraction f2= {.num=1, .den=2};
  return f2;
}


int main(int argc, char **argv){
  double d;
  double tab[4]={1,2,3,4};
  double mat[3][4]={ {1,2,3,4},{5,6,7,8},{9,10,11,12}} ;
  double *ptr1;
  double *ptrl;
  double *ptr2;

  ptr1=tab;

  printf("sizeof(d)=%d\n",sizeof(d));
  printf("&d=%p\n",&d);
  for(int i=0;i<4;i++){
    printf("tab[%d]=%f at address %p\n",i,tab[i],&(tab[i]) );
    printf("tab[%d]=%f at address %p\n",i,*(ptr1+i),ptr1+i);
    printf("tab[%d]=%f at address %p\n",i,*ptr1+i,ptr1+i);
    printf("tab[%d]=%f at address %p\n",i,(*(ptr1))+(double)i,ptr1+i);
  }

  ptr2=&(mat[0][0]);

  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++) {
      printf("mat[%d][%d]=%f at address %p\n",i,j,mat[i][j],&(mat[i][j]));
      printf("mat[%d][%d]=%f at relative address %d\n",i,j,mat[i][j],&(mat[i][j])-&(mat[0][0]));
      printf("mat[%d][%d]=%f at address %p\n",i,j,*(ptr2+i*4+j),ptr2+i*4+j);
    }
  }
  
  int l=1;
  ptrl=mat[1];
  for(int c=0;c<4;c++){
    printf("mat[%d][%d]=%f at address %p\n",l,c,mat[l][c],&(mat[l][c]));
    printf("mat[%d][%d]=%f at address %p\n",l,c,*(ptrl+c),ptrl+c);
  }


  struct record {
    char c[3];
    double num;
    char d;
    int data[4];
  };

  struct record t1;
  t1.c[0]='A';
  t1.c[1]='B';
  t1.c[2]='C';
  t1.num=42.0;
  t1.d='Z';
  t1.data[1]=2;
  printf("sizeof(test)=%d\n",sizeof(t1));
  printf("&(t1)=%p\n",&(t1));
  printf("&(t1.c[0])=%p\n",&(t1.c[0]));
  printf("&(t1.num)=%p\n",&(t1.num));
  printf("&(t1.d)=%p\n",&(t1.d));
  printf("&(t1.data)=%p\n",&(t1.data));

  char *dp=(char *) &(t1) + 4 + 8;
  printf("%p\n",dp);



  struct fraction f1;
  f1.num=1;
  f1.den=17;

  printf("sizeof(fraction)=%d\n",sizeof(f1));
  printf("&(f1)=%p\n",&(f1));
  printf("&(f1.num)=%p\n",&(f1.num));
  printf("&(f1.num)+1=%p\n",&(f1.num)+1);
  printf("&(f1.den)=%p\n",&(f1.den));

  struct fraction f2;
  f2=simp3(f1);
  printf("%d/%d\n",f2.num,f2.den);

  struct fraction tabfract[2];
  tabfract[0].num=1;
  tabfract[0].den=7;
  tabfract[1].num=2;
  tabfract[1].den=3;

  struct fraction *p=tabfract;
  printf("%d \n",(p+1)->den);
  printf("&(tabfract[0])=%p\n",&(tabfract[0]));
  printf("&(tabfract)=%p\n",&(tabfract));
  printf("tabfract=%p\n",tabfract);

  printf("&(tabfract[1])=%p\n",&(tabfract[1]));

  printf("argc=%d\n",argc);
  for(int i=0;i<argc;i++) {
    char *ptr=*(argv+i);
    printf("argv[%d]=%s\n",i,ptr);
    for(int j=0;j<strlen(ptr);j++) {
      printf("%c is at %p\n",*(ptr+j),ptr+j);
    }
  }

  char *string="abcdef";
  char string2[]="abcdef";
  /*
  char string3="ab";
  char *string4='A';
  char string5='B';
  char *string6="C";
  */
  printf("%s\n",string);
  printf("%s\n",string2);


  printf("%s\n",string+2);


  printf("%c\n",*(string+3));

  printf("%c\n",*(string+6));
  printf("test\n");

  string2[0]='A';
  *(string2)='A';
  *(string2+5)='F';
  *(string2+strlen(string2))='G';
  *(string2+strlen(string2)+1)='H';

  printf("%s\n",string2);

  // see https://stackoverflow.com/questions/1335786/c-differences-between-char-pointer-and-array

  //  string++;
  // printf("%s\n",string);





}
