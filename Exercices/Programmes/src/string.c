#include <stdlib.h>
#include <stdio.h>

/**
 * Returns the number of characters in s
 */
size_t strlen(const char *s)
{
	int i = 0;
	while(s[i] != '\0')
	{
		i++;
	}
	return i;
}

/**
 * Appends the src string to the dest string, overwriting
 * the null byte ('\0') at the end of dest, and then adds
 * a terminating null byte. The strings may not overlap,
 * and the dest string must have enough space for the result.
 */
char * strcat(char *s1, const char *s2)
{
	int i;
	for(i = 0; i < strlen(s2); i++)
	{
		*(s1 + strlen(s1) + i) = *(s2 + i);
	}
	*(s1 + strlen(s1) + i) = '\0';
	return s1;
}

int main(int argc, char *argv[]) {
	/* Test function */
  char *text_1 = "Hello";
  char *text_2 = " World!";
  char *text_3 = NULL;
  char concat_1[100];
  char concat_2[100];
  int i;

  printf("Length of %s: %lu\n", text_1, strlen(text_1));
  printf("Length of %s: %lu\n", text_2, strlen(text_2));
  printf("Length of %s: %lu\n", text_3, strlen(text_3));

  for (i = 0; i < strlen(text_1); i++)
    concat_1[i] = *(text_1 + i);
  printf("Putting %s and %s together gives %s\n", text_1, text_2, strcat(concat_1, text_2));

  /* Taking arguments, if any */
  printf("Length of %s: %lu\n", argv[1], strlen(argv[1]));
  printf("Length of %s: %lu\n", argv[2], strlen(argv[2]));

  for (i = 0; i < strlen(argv[1]); i++)
    concat_1[i] = *(argv[1] + i);
  printf("Putting %s and %s together gives %s\n", argv[1], argv[2], strcat(concat_2, argv[2]));

  return 0;
}
