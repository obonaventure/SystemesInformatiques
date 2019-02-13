#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main() {
	char strtab[36] = "Coucou!! Je suis un grand string\n";
	char *str = strtab;
	int i;
	for (i = 0; i < 8; i++) {
		char c = str[i];
		printf("Char %d, located at %p, is %c\n", i, &str[i], c);
	}
	uint32_t *str2 = (uint32_t *) str;
	for (i = 0; i < 8; i++) {
		uint32_t ui = str2[i];
		printf("UInt %d, located at %p, is %u\n", i, &str2[i], ui);
	}
	str2[0] = 1801675080;
	str2[1] = 555836517;
	for (i = 0; i < 8; i++) {
		char c = str[i];
		printf("Char %d, located at %p, is %c\n", i, &str[i], c);
	}
	return 0;
}
