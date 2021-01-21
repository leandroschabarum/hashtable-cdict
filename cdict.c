#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ckhash.h"


int main() {
	unsigned int newHash;
	char *userKey;
	userKey = (char *)(malloc(KEY_MAX_SIZE));

	while(1) {
		printf("%s\n", "Enter key value: ");
		scanf("%s", userKey);

		if (strcmp(userKey, "break") == 0) {
			break;
		} else {
			newHash = charkey_hash(userKey);
		};
	};

	free(userKey);
	return 0;
};
