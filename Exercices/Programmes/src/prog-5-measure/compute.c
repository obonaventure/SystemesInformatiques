#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "compute.h"

#define MIN(a,b)    (a < b ? a : b)
#define SIZE        8
#define SIZE_BITS   (SIZE * 8)
#define SIZE_HEX    (SIZE * 2)

static void str2hex(const char *input, size_t len, char *output)
{
    int i;

    memset(output, 0, SIZE_HEX);
    for (i = 0; i < SIZE_HEX; i += 2)
        sprintf(output + i, "%02hhX", input[i / 2]);
}

static void hex2str(const char *input, size_t len, char *output)
{
    int i;

    memset(output, 0, len / 2);
    for (i = 0; i < len; i += 2)
        sscanf(input + i, "%02hhX", &output[i / 2]);
}

static void str2bits(const char *input, size_t len, char *output)
{
    int i;

    memset(output, 0, 64);
    for(i = 0; i < MIN(len * 8, 64); ++i)
        output[i] = (input[i / 8] >> (i % 8)) & 1;
}

static void bits2str(const char *input, char *output)
{
    int i;

    memset(output, 0, SIZE);
    for (i = 0; i < SIZE_BITS; ++i)
        output[i / 8] |= input[i] << (i % 8);
}


static void __encrypt(char work[SIZE_BITS], int n, int decrypt)
{
    while (n--)
        encrypt(work, decrypt);
}

void pwd_init(const char *key)
{
    char work[SIZE_BITS];

    str2bits(key, MIN(strlen(key), 8), work);
    setkey(work);
}

void pwd_encrypt(const char *pwd, char *cipher, int n)
{
    char work[SIZE_BITS], output[SIZE];

    str2bits(pwd, strlen(pwd), work);
    __encrypt(work, n, 0);
    bits2str(work, output);
    str2hex(output, SIZE, cipher);
}

void pwd_decrypt(const char *hex, char *pwd, int n)
{
    char work[SIZE_BITS], input[SIZE];

    hex2str(hex, strlen(hex), input);
    str2bits(input, SIZE, work);
    __encrypt(work, n, 1);
    bits2str(work, pwd);
}

