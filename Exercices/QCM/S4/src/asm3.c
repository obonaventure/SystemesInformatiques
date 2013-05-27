#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

void f1()
{
  a=a+b;
  b=b+b;
  c=b-a;
}

void f2()
{
  a=b+a;
  b=b+b;
  c=b-a;
}

void f3()
{
  a=b+a;
  b=b++;
  c=a-b;
}

void f4()
{
  c=b+a;
  b=b++;
  a=a-b;
}

void f5()
{

  b=b+a;
  a=b++;
  c=b-a;

}




int main() {



}


