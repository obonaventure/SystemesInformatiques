/**************************************
 * union.c
 *
 * Programme d'exemple de union
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA

struct s_t {
  int i;
  char c;
} s;

union u_t {
  int i;
  char c;
} u;

///BBB

typedef enum { INTEGER, CHAR } Type;

typedef struct
{
  Type type;
  union {
  int i;
  char c;
  } x;
} Value;


///XXX

int main(int argc, char *argv[]) {
  ///CCC
  // initialisation
  s.i=1252;
  s.c='A';
  u.i=1252;
  // u contient un int
  u.c='Z';
  // u contient maintenant un char (et u.i est perdu)
  ///DDD
  printf("sizeof(s_t) : %ld\n",sizeof(s));
  printf("sizeof(u_t) : %ld\n",sizeof(u));
  ///EEE
  u.i=1252;
  printf("char : %c\n", u.c);

  ///FFF
Value v;
v.type=INTEGER;
v.x.i=1252;
///GGG
  return(EXIT_SUCCESS);
}
