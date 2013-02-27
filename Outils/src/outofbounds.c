#include <stdlib.h>

int main(int argc, char * argv[])
{
	char *ptrChars = (char *)malloc(6 * sizeof(char));
	ptrChars[0]= 'H';
	ptrChars[12]= 'W';
	free(ptrChars);

	return 0;
}