#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

int f1(int i) // correct
{
  return i+a;
}

int f2(int i) // correct
{
  int j=a;
  return j+i;

}

void f3(int i) // incorrect
{
  int j=i+a;

}

int f4() // incorrect
{
  int i;
  return i+a;
}

int f5(char c) // incorrect
{
  return c+a;

}

char f6(char c) // incorrect
{
  return c+a;
}



int main() {



}


