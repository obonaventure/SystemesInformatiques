#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

int f1(int i) // correct
{
  return a+f1(i-1);
}

int f2(int i) // correct
{
  int j=f2(i-1);
  return j+a;

}

int f3(int i) // incorrect
{
  return a+f3(i);

}

int f4(int i) // incorrect
{
  return f4(i+a);
}

int f5(int i) // incorrect
{
  int j=f5(i-1);
  return a;
}

char f6(char c) // incorrect
{
  return a+f6(c-1);

}



int main() {



}


