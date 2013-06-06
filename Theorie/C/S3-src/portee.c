/**************************************
 * portee.c
 *
 * Programme d'exemple pour la portée de
 * variables
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA

int g1;
int g2=1;

void f(int i) {
  int loc;    //def1a
  int loc2=2; //def2a
  int g2=-i*i;
  g1++;

  printf("[f-%da] \t\t %d \t %d \t %d \t %d\n",i,g1,g2,loc,loc2);
  loc=i*i;
  g1++;
  g2++;
  printf("[f-%db] \t\t %d \t %d \t %d \t %d\n",i,g1,g2,loc,loc2);

}


int main(int argc, char *argv[]) {
  int loc; //def1b
  int loc2=1; //def2b

  printf("Valeurs de : \t g1 \t g2\t loc\t loc2\n");
  printf("===================================================\n");

  printf("[main1] \t %d \t %d \t %d \t %d\n",g1,g2,loc,loc2);

  loc=1252;
  loc2=1234;
  g1=g1+1;
  g1=g1+2;

  printf("[main2] \t %d \t %d \t %d \t %d\n",g1,g2,loc,loc2);

  for(int i=1;i<3;i++) {
    int loc=i; //def1c
    int g2=-i;
    loc++;
    g1=g1*2;
    f(i);
    printf("[main-for-%d] \t %d \t %d \t %d \t %d\n",i,g1,g2,loc,loc2);
  }
  f(7);
  g1=g1*3;
  g2=g2+2;
  printf("[main3] \t %d \t %d \t %d \t %d\n",g1,g2,loc,loc2);

  return(EXIT_SUCCESS);
}
///BBB
