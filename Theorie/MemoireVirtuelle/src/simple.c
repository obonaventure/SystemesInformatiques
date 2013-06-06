/**************************************
 * simple.c
 *
 * Programme d'exemple qui affiche simplement
 * les adresses de argc, main et printf
 *
 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
///AAA
int main (int argc, char *argv[])  {
  printf("[pid=%ld] Adresse de argc : %p\n",(long) getpid(),&argc);
  printf("[pid=%ld] Adresse de main : %p\n",(long) getpid(),main);
  printf("[pid-%ld] Adresse de printf : %p\n",(long) getpid(),printf);
  sleep(20);
  return(EXIT_SUCCESS);
}
///BBB
