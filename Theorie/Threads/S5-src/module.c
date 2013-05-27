/**************************************
 * module.c
 *
 **************************************/

#include "module.h"

static float min(float, float);

int num1=0;  // accessible hors de module.c
extern int num2; // définie dans un autre module
static int num3=1252; // accessible uniquement dans ce module

float vmin(int n, float *ptr) {
  float *p=ptr;
  float m=*ptr;
  for(int i=1;i<n;i++) {
    m=min(m,*p);
    p++;
  }
  return m;
}

static float min(float a, float b) {
  if(a<b)
    return a;
  else
    return b;
}


