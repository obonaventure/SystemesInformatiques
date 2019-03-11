#include <stdlib.h>

int cours = 1252;

int f(int *a, int b) {
	int c = 97850**a + b;
	int x = 2052;
	*a = x * c;
	return c;
}

int main(int argc, char *argv[]) {
	int d = 42;
	char *tab = malloc(20 * sizeof(char));
	int *res = (int *) tab;
	*res = f(&cours, d);
	return 0;
}
