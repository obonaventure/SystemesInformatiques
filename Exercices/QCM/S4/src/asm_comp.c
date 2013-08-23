#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

void f1() // correct
{
  if(b<4)
    a++;

}

void f2() // correct
{
  if((b>=4))
    {}
  else
    a++;
}

void f3() // incorrect
{
  if(b<=4)
    a++;

}

void f4() // incorrect
{
  if(b!=4)
    a++;

}

void f5() // incorrect
{
  if(!(b<4))
    a++;

}

void f6() // incorrect
{
  if(b>=4)
    a++;
}



int main() {



}


