#include <stdio.h>
#include <string.h>
#include "ckhash.h"


int main(void)
{
	unsigned int newHash;
	char userKey[KEY_MAX_SIZE];
	char *ptr_userKey = 0;

	while(1) {
		printf("enter key value />_ ");
		scanf("%s", &userKey[0]);
		ptr_userKey = &userKey[0];

		if (strcmp(userKey, "break") == 0)
		{
			break;
		}
		else
		{
			newHash = charkey_hash(ptr_userKey);
			printf("%s : %d\n", userKey, newHash);
		}
	}

	return 0;
}
