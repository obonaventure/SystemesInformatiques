/**************************************
 * strip.c
 *
 * Programme d'exemple de fonction avec char **
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strip(char **str) {
  int count=0;
  char *c;
  c=*str;
  int len=strlen(c);
  for(int i=0; i<len;i++) {
    if(*c==' ') {
      count++;
    }
    c++;
  }
  int removed=0;
  c=*str;
  char *string=(char *) malloc(sizeof(char)*count+1);
  char *r=string;
  for(int i=0; i<strlen(*str);i++) {
    if(*c!=' ') {
      *r=*c;
      r++;
      removed++;
    }
    c++;
  }
  *r='\0';
  *str=string;
  return removed;
}

int main(int  argc, char *argv[]) {
  char *s1=" lkslskldklqkds";
  char *s2="alkjlksj skdjlskd sqdlkj";
  char **s1ptr=&(s1);
  char **s2ptr=&(s2);
  int n1=strip(s1ptr);
  printf("n1=%d, %s\n",n1,s1);
  int n2=strip(s2ptr);
  printf("n2=%d, %s\n",n2,s2);


}


