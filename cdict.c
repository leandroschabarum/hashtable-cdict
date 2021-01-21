#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ckhash.h"


int main() {
	printf("%s\n", "Enter key value: ");
	unsigned char *userKey;
	userKey = (unsigned char *)(malloc(KEY_MAX_SIZE));
	//scanf("%s", userKey);

	unsigned int newHash;
	newHash = charkey_hash(userKey);
	free(userKey);

	printf("%s\n", "Started Second Computation");
	newHash = charkey_hash("djfbajdfnajkfbfbdfgnsfgnsfgns");
	printf("Second New Hash: %u\n", newHash);

	return 0;
};
