/**************************************
 * vector.c
 *
 * Programme de manipulation de vecteurs
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
///AAA
struct vector_t {
  int size;
  float *v;
};
// initialise le vecteur à la valeur du réel
struct vector_t * init(int, float) ;
// récupère le nième élément
float get(struct vector_t *, int) ;
// fixe la valeur du nième élément
void set(struct vector_t *, int , float);
// supprime un vecteur
void destroy(struct vector_t *);

///BBB
struct vector_t * init(int size, float val)
{
  struct vector_t *v=(struct vector_t *)malloc(sizeof(struct vector_t));
  v->v=(float *)malloc(size*sizeof(float));
  v->size=size;
  for(int i=0;i<size;i++) {
    *(v->v+i)=val;
  }
  return v;
}

float get(struct vector_t *v, int i) {
  return *(v->v+i);
}

void set(struct vector_t *v, int i, float val) {
  if(i<v->size)
    *(v->v+i)=val;
}

void destroy(struct vector_t *v) {
  free(v->v);
  free(v);
}

int main(int argc, char *argv[]) {

  struct vector_t *v1=init(10,2.0);
  printf("v1[%d]=%f\n",3,get(v1,3));
  set(v1,3,17.0);
  printf("v1[%d]=%f\n",3,get(v1,3));
  destroy(v1);

   return(EXIT_SUCCESS);
}
