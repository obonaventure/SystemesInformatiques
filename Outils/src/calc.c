#include <stdlib.h>
#include <stdio.h>


void calc(int a, int b) {
	double res;
	int i;

	for(i=0; i<6; i++) {
		res += (a*5 -10) / (b-i);
		printf("(%d * 5 - 17 ) / %d = %f\n", a, (b-i), res);
	}
}

int main(int argc, char *argv[]){
	int n = 165, m = 4;

	calc(n, m);

	return EXIT_SUCCESS;
}
