#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

void f1()
{
  if(a==b)
    c++;
}

void f2()
{
  if(a>b)
    c++;
}

void f3()
{
  if(a<b)
    c++;
}

void f4()
{
  if(a!=b)
    c++;
}

void f5()
{
  if(a<=b)
    c++;
}

void f6()
{
  if(b>=a)
    c++;
}



int main() {



}


