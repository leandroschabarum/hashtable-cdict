#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ckhash.h"

#define MAX_DICT_LENGTH 2147483648

int main() {
	printf("%s\n", "Enter key value: ");
	unsigned char userKey[0];
	scanf("%s", userKey);

	unsigned int newHash = charkey_hash(userKey);
	printf("\nKey hash: %d\nMax dict size: %u\n", newHash, (unsigned int)(DICT_MAX_SIZE));

	return 0;
}
