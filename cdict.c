#include <stdio.h>
#include <string.h>
#include "cdict.h"


int main(void)
{
	unsigned int newHash;
	char userKey[128];
	char *ptr_userKey = 0;

	while(1) {
		printf("enter key value />_ ");
		scanf("%[^\n]%*c", &userKey[0]);
		ptr_userKey = &userKey[0];

		if (strcmp(userKey, "break") == 0)
		{
			break;
		}

		newHash = charKeyHash(ptr_userKey, MAX_DICT);
		printf("%s : %d\n", userKey, newHash);
	}

	return 0;
}
