#include <stdio.h>
#include <stdlib.h>

int g=1;
int h=2;
int j,j2,l,l,m,k;
int r;

void a()
{
  j=j+1;
   k=g-h;
}

void cmp()
{
  r=(h>1);
  r=(j==0);
  r=g<h;
  r=(j==h);
}

void jump()
{
  if(j==0)
    r=1;

  if(j>g)
    r=2;
  else
    r=3;

  if (j>=g)
    r=4;

}

void while_loop()
{
  while(j>0)
  {
    j=j-3;
 }

}

void for_loop()
{
  for(j=0;j<10;j++)
     g=g+h;

  for(j=9;j>0;j=j-1)
     g=g-h;
}

void increase()
{
 g=g+h;
}

void init_g()
{
 g=1252;
}

void init(int a) {
g=a;
}

void sumg(int a, int b) {
 g= a+b;
}

int sum(int a, int b) {
 return a+b;
}

void b()
{
   l=g^j;
   j=j|k;
  g=l<<6;
}

int test()
{
  h=~h;
   j++;
   j=j+1;
   j=g/h;
 j2=g*h;
   k=g-h;
  l=g>>4;
  g=l<<6;
 m= h&&g;
 return m;

}

int add()
{
 int l=1252;
 l=g+h;
 return l;
}

int factorial(int X) {
  if (X == 0) return 1;
  return X*factorial(X-1);
}

int main(int argc, char **argv) {
  init_g();
  increase();
  init(1252);
  sumg(6,7);
  printf("%d\n", factorial(atoi(argv[1])));
}
