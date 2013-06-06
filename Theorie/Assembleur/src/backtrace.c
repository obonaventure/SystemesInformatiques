#include <stdio.h>
#include <string.h>

char safechar(char c)
{
  if (c >= 'a' && c <= 'z') return(c);
  if (c >= 'A' && c <= 'Z') return(c);
  if (c >= '0' && c <= '9') return(c);
  if (c == ' ') return(c);
  if (c == '.') return(c);
  if (c == '-') return(c);
  if (c == ',') return(c);
  if (c == '(') return(c);
  if (c == ')') return(c);
  if (c == '[') return(c);
  if (c == ']') return(c);
  if (c == '{') return(c);
  if (c == '}') return(c);
  return '.';
}

void print_backtrace(void *from)
{
    long *s = (long *) &s+1;

    while ((long) s <= (long) from) {
        int i;
        printf("[%p] %20ld 0x%-16lx ", s, *s, *s);
        for (i = 0; i < sizeof(*s); i++)
            printf("%c", safechar(((char *) s)[i]));
        printf("\n");
        s++;
    }

}

long bar(void *p)
{
    print_backtrace(p);
    return 42;
}

long foo(void *p)
{
    long a = 42, b;
    void *cool = p;
    b = a;

    return b + a + bar(cool);
}

int main(int argc, char const *argv[])
{
    const char *args = argv[argc-1];
    return foo((void *)&args[strlen(args)+1]);
}
