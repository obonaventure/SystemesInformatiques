#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

void f1() // correct
{
  if(a>=b)
    a++;
  else
    b++;

}

void f2() // correct
{
  if(b<=a)
    a++;
  else
    b++;
}

void f3() // incorrect
{
  if(a>=b)
    b++;
  else
    a++;

}

void f4() // incorrect
{
  if(b<a)
    a++;
  else
    b++;
}

void f5() // incorrect
{
  if(b>a)
    b++;
  else
    a++;

}

void f6() // incorrect
{
   if(a>=b) {
    a++;
   }
   b++;

}



int main() {



}


