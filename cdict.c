#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "hashFunc.h"

#define true 1
#define false 0

union content
{
	char c;
	int i;
	float f;
};

typedef struct Dictionary
{
	char key[128];
	union content element;
} dict;


dict* newDict(unsigned int dict_size, ...)
{
	if (dict_size < 1)
	{
		fprintf(stderr, "[%u] bad dictionary size\n", dict_size);
		exit(EXIT_FAILURE);
	}

	va_list args;
	va_start(args, dict_size);

	int memSafe = va_arg(args, int);
	va_end(args);
	
	static dict *localDict = 0;
	localDict = (dict *) malloc(sizeof(dict) * dict_size);

	// in case no memory was allocated returns null pointer
	// if memSafe is true than raises an error
	if (! localDict)
	{
		if (memSafe)
		{
			fprintf(stderr, "[%u] unable to allocate memory for new dictionary\n", dict_size);
			exit(EXIT_FAILURE);
		}

		return 0;
	}

	memset(localDict, 0, sizeof(*localDict));
	return localDict;
}

void addDict(dict *ptr_dict)
{}

void remDict(dict *ptr_dict)
{}



int main(void)
{
	//unsigned int newHash;
	//char userKey[128];
	//char *ptr_userKey = 0;

	dict *d = newDict(10, true);

	for (int i = 0; i < 10; i++)
	{
		printf("[%d] %s : ", i, d[i].key);
		printf("[%d] %d\n", i, d[i].element.i);
	}

	/*
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
	*/

	return 0;
}
