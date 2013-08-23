/**************************************
 * stresep.c
 *
 * Implementation partielle de strtol
 *
 **************************************/
///AAA
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int mystrtol(const char *restrict str,
	     char **restrict endptr,
	     int base) {

  int val;
  int i=0;
  int err=false;
  while(!err && *(str+i)!='\0')
    {
      if(!isdigit(*(str+i))) {
	err=true;
	*endptr=(char *)(str+i);
      }
      i++;
    }
  // ...
  return val;
}
///BBB

int main(int argc, char *argv[])
{
  char *p, *s;
  long li;
  s = "1252m";
  li = mystrtol(s,&p,10);
  if(p!=NULL) {
    printf("Caractère erronné : %c\n",*p);
      // p pointe vers le caractère en erreur
  }
  printf("Valeur convertie : %s -> %ld\n",s,li);
  return(EXIT_SUCCESS);

}
