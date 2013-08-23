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
} ;

struct coord origin={1,2,3};
struct coord p;

// structure pour stocker une fraction
struct fraction {
  double numerator;
  double denominator;
};

struct fraction demi={1.0,2.0};
struct fraction f;

// structure pour représenter un étudiant
struct student {
  int matricule;
  char prenom[20];
  char nom[30];
};

struct student s={1,"Linux","Torvalds"};

///BBB

///EEE

int equal(struct fraction f1, struct fraction f2) {
  return ( (f1.numerator==f2.numerator) &&
	   (f1.denominator==f2.denominator) );
}

///FFF

int main(int argc, char *argv[]) {
  int c[3]={0,0,0};

  ///CCC
  origin.x=1;
  origin.y=2;
  origin.z=3;
  ///DDD

  f.numerator=1;
  f.denominator=4;
  printf("%c\n",s.prenom[2]);
  printf("sizeof int[3]=%ld, sizeof coord=%ld\n",sizeof(c),sizeof(struct coord));
  printf("sizeof student : %ld\n",sizeof(s));

   return(EXIT_SUCCESS);
}
