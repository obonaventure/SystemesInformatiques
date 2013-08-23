#include <stdio.h>
#include <stdlib.h>

int a=1;
int b=2;
int c=3;

int max(int i, int j) { //correct
  if (i>j)
    return i;
  else
    return j;
}

int max2(int i, int j) { //correct
  if (i<j)
    return j;
  else
    return i;
}

int max3(int i) { //incorrect
  if (i<i)
    return i;
  else
    return i;
}

int max4(int i, int j) { //incorrect
  if (i<j)
    return j;
  else
    return j;
}


int max5(int i, int j) { //incorrect
  if (i<j)
    return i;
  else
    return j;
}



int main() {



}


