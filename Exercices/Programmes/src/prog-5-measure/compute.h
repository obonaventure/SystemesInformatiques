#ifndef _COMPUTE_H_
#define _COMPUTE_H_


/* Initialize the password, only the first 8 bytes of key will be considered. */
void pwd_init(const char *key);

/* Encrypt pwd n times and store its output as a hexadecimal string in cipher.
 * Only the first 8 bytes of pwd will be considered. cipher must have at least
 * a size of 17 bytes. */
void pwd_encrypt(const char *pwd, char *cipher, int n);

/* Decrypt n times the cipher represented in hexadecimal and store its output
in pwd. pwd must have a size of at least 8 bytes. */
void pwd_decrypt(const char *cipher, char *pwd, int n);

#endif
