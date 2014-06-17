/***********************************************
 * struct.c
 *
 * Programme d'exemple de structures
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///AAA

// structure pour stocker une coordonnée 3D
struct coord {
  int x;
  int y;
  int z;
};

struct coord point = {1, 2, 3};
struct coord p;

// structure pour stocker une fraction
struct fraction {
  int numerator;
  int denominator;
};

struct fraction demi = {1, 2};
struct fraction f;

// structure pour représenter un étudiant
struct student {
  int matricule;
  char prenom[20];
  char nom[30];
};

struct student s = {1, "Linus", "Torvalds"};

///BBB

///EEE
struct fraction init(int num, int den)
{
  struct fraction f;
  f.numerator = num;
  f.denominator = den;
  return f;
}

int equal(struct fraction f1, struct fraction f2)
{
  return ((f1.numerator == f2.numerator) 
          && (f1.denominator == f2.denominator));
}

int equalptr(struct fraction *f1, struct fraction *f2)
{
  return ((f1->numerator==f2->numerator)
          && (f1->denominator==f2->denominator));
}

void initptr(struct fraction *f, int num, int den)
{
  f->numerator = num;
  f->denominator = den;
}
///FFF

int main(int argc, char *argv[])
{

  int c[3] = {0, 0, 0};

///CCC

point.x = 1;
point.y = 2;
point.z = 3;

///DDD

///GGG

struct fraction quart;
struct fraction tiers;
quart = init(1, 4);
initptr(&tiers, 1, 3);
printf("equal(tiers,quart)=%d\n", equal(tiers, quart));
printf("equalptr(&tiers,&quart)=%d\n", equalptr(&tiers, &quart));

///HHH

  f.numerator=1;
  f.denominator=4;
  printf("%c\n",s.prenom[2]);
  printf("sizeof int[3]=%ld, sizeof coord=%ld\n",sizeof(c),sizeof(struct coord));
  printf("sizeof student : %ld\n",sizeof(s));

   return(EXIT_SUCCESS);
}
