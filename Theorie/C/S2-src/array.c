/***********************************************
 * array.c
 *
 * Programme d'exemple d'utilisation de tableaux
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA

#define N 10
int vecteur[N];
float matriceC[N][N];
float matriceR[N][2*N];

///BBB

// calcule la somme des éléments d'un tableau
int sum(int v[])
{
  ///CCC
  
  int i;
  int sum = 0;
  for (i = 0; i < N; i++) {
    sum += v[i];
  }
  
  ///DDD
  
  return sum;
}

// calcule la somme des éléments d'un tableau
int sum2(int size, int v[size])
{
  int i;
  int sum = 0;
  for (i = 0; i < size; i++) {
    sum += v[i];
  }
  return sum;
}

#include <float.h>

// retourne le maximum d'un matrice
// carrée de NxN élément
float max()
{
  ///EEE
  #define L 2
  #define C 3
  float matriceR[L][C] = { {1.0,2.0,3.0},
                           {4.0,5.0,6.0} };
  int i, j;
  float min = FLT_MAX;
  for (i = 0; i < L; i++)
    for (j = 0; j < C; j++)
      if (matriceR[i][j] < min)
        min=matriceR[i][j];
    
  ///FFF
  return min;
}

// retourne le maximum d'un matrice
// carrée de NxN élément
float max2(int size, float mat[size][size]) {
  int i,j;
  float m=0.0; // corrige MINFLOAT
  for(i=0;i<size;i++)
    for(j=0;j<size;j++){
      if(mat[i][j]>m)
	m=mat[i][j];
    }
  return m;
}


int main(int argc, char *argv[]) {

  ///CCC
  int vecteur[N]={0,1,2,3,4,5,6,7,8,9};
  int i;
  int sum=0;
  for(i=0;i<N; i++) {
    sum+=vecteur[i];
  }
  ///DDD


  return(EXIT_SUCCESS);
}

