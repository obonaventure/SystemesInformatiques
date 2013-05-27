#include <stdio.h>
#include <stdlib.h>

int a=1;
int * ptr;
int b=2;
int c=3;

void f1() // correct
{
  ptr=&a;

}

void f3() // incorrect
{
  *ptr=a;

}

void f4() // incorrect
{
  ptr=(int) a;
}

void f5() // incorrect
{
  int b=a;
  ptr=&(b);

}

void f6() // incorrect
{
  ptr=&a+1;
}



int main() {



}


