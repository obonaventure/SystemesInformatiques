#include <stdio.h>

void calc (int *tab, int i, int num)
{
	tab[i] = num / i;
}

void iter (int *tab, int num)
{
	int i;
	printf("Iterating\n");
	for (i = 0; i <= 10; i++) {
		calc(tab, i, num);
	}
}

int main (int argc, char * argv[])
{
	int *tab = NULL;
	int num = 20;
	int i;

	iter(tab, num);

	for (i = 0; i < 10; i++) {
		printf(" %d", tab[i]);
	}
	printf("\n");

	return 0;
}
