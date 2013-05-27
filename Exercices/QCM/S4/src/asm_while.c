#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

void f1() // correct
{
  while(a!=c)
  {
    a++;
    b=b+c;
  }

}

void f2() // correct
{
  while(c!=a)
  {
    a++;
    b=b+c;
  }

}

void f3() // incorrect
{
  while(c>a)
  {
    a++;
    b=b+c;
  }
}

void f4() // incorrect
{
  do
  {
    a++;
    b=b+c;
  }
  while(c!=a);

}

void f5() // incorrect
{

  while(c==a)
  {
    a++;
    b=b+c;
  }

}




int main() {



}


