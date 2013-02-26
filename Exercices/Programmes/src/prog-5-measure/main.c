#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "compute.h"

int main (int argc, char *const argv[])
{
    char c;
    char *password = NULL;
    int i, decrypt = 0, n = 0;
    char output[17];

    while ((c = getopt (argc, argv, "dn:p:")) != -1) {
         switch (c) {
        case 'd':
            decrypt = 1;
            break;
        case 'n':
            n = strtol(optarg, NULL, 10);
            break;
        case 'p':
            password = optarg;
            break;
        case '?':
            fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        default:
            return 1;
        }
    }

    if (!password) {
        fprintf (stderr, "You must specify a password.\n");
        return 1;
    }

    if (optind == argc) {
        fprintf (stderr, "You must specify at least one argument.\n");
        return 1;
    }

    pwd_init(password);

    for (i = optind; i < argc; ++i) {
        if (decrypt) {
            pwd_decrypt(argv[i], output, n);
            printf("%.*s ", 8, output);
        } else {
            pwd_encrypt(argv[i], output, n);
            printf("%.*s ", 16, output);
        }
    }
    printf("\n");

    return 0;
}
