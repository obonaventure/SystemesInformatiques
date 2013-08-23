/**************************************
 * strcpy.c
 *
 * Programme d'exemple pour strcpy
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
///AAA
#include <string.h>

char *duplicate(char * str) {
  int i;
  size_t len=strlen(str);
  char *ptr=(char *)malloc(sizeof(char)*(len+1));
  if(ptr!=NULL) {
    for(i=0;i<len+1;i++) {
	*(ptr+i)=*(str+i);
      }
  }
  return ptr;
}
///BBB
char *duplicate2(char * str) {
  int i;
  size_t len=strlen(str);
  char str2[len+1];
  for(i=0;i<len+1;i++) {
    str2[i]=*(str+i);
  }
  return str2;
}
///CCC

int main(int argc, char *argv[]) {

  char str[]="Hello, world";
  char *str2=duplicate(str);
  char *str3=duplicate2(str);
  printf("str:  %s\n",str);
  printf("str2: %s\n",str2);
  printf("str3: %s\n",str3);

  return(EXIT_SUCCESS);
}
