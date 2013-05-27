#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

void f1() // correct
{
  for(a=0;a<c;a++) {
    b=b-c;
  }

}

void f2() // correct
{
  for(a=0;c>a;a=a+1) {
    b=b-c;
  }

}

void f3() // incorrect
{

  for(a=a+1;c>a;a=0) {
    b=b-c;
  }
}

void f4() // incorrect
{
  for(a=0;a<=c;a++) {
    b=b-c;
  }

}

void f5() // incorrect
{
  a=0;
  if(a<c) {
    b=b-c;
    a++;
  }

}

void f6() // incorrect
{
  for(;a<c;a++) {
    a=0;
    b=b-c;
  }


}



int main() {



}


