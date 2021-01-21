#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ckhash.h"


int main() {
	unsigned int newHash;
	char *userKey;
	userKey = (char *)(malloc(KEY_MAX_SIZE));

	printf("%s\n", "Enter first key value: ");
	scanf("%s", userKey);
	newHash = charkey_hash(userKey, strlen(userKey));

	printf("%s\n", "Enter second key value: ");
	scanf("%s", userKey);
	newHash = charkey_hash(userKey, strlen(userKey));

	free(userKey);

	return 0;
};
