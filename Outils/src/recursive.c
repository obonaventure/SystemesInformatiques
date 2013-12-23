#include <stdlib.h>
#include <stdio.h>

int globalVar = 5;

int factTmp(int acc, int nbr) {
	static int globalTmp =0;
	globalTmp++;

	int tmp =0;
	tmp++;

	if(nbr<=1) return acc;
	else return factTmp(acc*nbr, nbr-1);
}


int factTerminal(int a) {
	int localVar = 3;
	return factTmp(1, a);
}


int main(int argc, char *argv[]){
	
	printf("La factorielle de 6 est : %d\n", factTerminal(6));
	
	return EXIT_SUCCESS;
}
