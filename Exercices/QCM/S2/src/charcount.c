#include <stdio.h>
#include <stdlib.h>

int count1(char *s, char c) {
  int i=0;
  int count=0;
  while(*(s+i)!='\0') {
    if(*(s+i)==c) {
       count++;
    }
    i++;
  }
  return(count);
}


int count2(char *s, char c) {
  int count=0;
  while(*(s)!='\0') {
    if(*(s)==c) {
       count++;
    }
    s++;
  }
  return(count);
}



int main() {

  char* s1="absbbbsba";
  char* s2="xbbsjjjqiz";
  printf("%s -> %d\n",s1,count1(s1,'a'));
  printf("%s -> %d\n",s2,count1(s2,'a'));

  printf("%s -> %d\n",s1,count2(s1,'a'));
  printf("%s -> %d\n",s2,count2(s2,'a'));


}


