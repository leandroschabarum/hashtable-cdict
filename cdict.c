#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ckhash.h"


int main() {
	printf("%s\n", "Enter key value: ");
	char *userKey;
	userKey = (char *)(malloc(KEY_MAX_SIZE));
	scanf("%s", userKey);

	unsigned int newHash;
	newHash = NEWcharkey_hash(userKey, strlen(userKey));
	free(userKey);

	userKey = "djfbajdfnajkfbfbdfgnsfgnsfgns";
	newHash = NEWcharkey_hash(userKey, strlen(userKey));
	printf("Second New Hash: %u\n", newHash);

	return 0;
};
