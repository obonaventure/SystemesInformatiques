#include <stdio.h>
#include <stdlib.h>

int g;
int g2;
int s;

int main() {

  g=1234;
  g2=5678;
  s=g;
  g=g2;
  g2=s;

}


