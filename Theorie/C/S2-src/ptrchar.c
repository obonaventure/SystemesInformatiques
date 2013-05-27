/***********************************************
 * ptrchar
 *
 * Programme d'exemple d'utilisation de pointeurs
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  ///AAA
  char c='Z';
  char str[]="sinf1252";
  char *str_ptr=NULL;
  int i;

  str_ptr=&c;
  printf("c vaut %c et est stocké à l'adresse : %p\n",c,&c);
  printf("*str_ptr vaut %p et pointe vers %c\n",str_ptr,*(str_ptr));
  str_ptr=str; // équivaut à  str_ptr=&(str[0]);
  printf("après str_ptr=str[];\n");
  printf("*str_ptr vaut %p et pointe vers %c\n",str_ptr,*(str_ptr));
  printf("Contenu du tableau\n");
  for(i=0;i<strlen(str);i++) {
    printf("str[%d]=%c et *(str_ptr+%d) contient %c\n",i,str[i],i,*(str_ptr+i));
  }


   ///BBB
   return(EXIT_SUCCESS);
}
