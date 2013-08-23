#include <stdlib.h>

int main(int argc, char * argv[])
{
	char *ptrChars = (char *)malloc(6 * sizeof(char));
	ptrChars[0]= 'H';
	free(ptrChars);
	free(ptrChars);

	return 0;
}
