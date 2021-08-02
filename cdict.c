#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "hashFunc.h"

#define true 1
#define false 0


typedef struct Dictionary
{
	char key[96];
	void *content;
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

void* addDict(dict *ptr_dict, const char *key, const void *value, size_t n)
{
	ptr_dict += charKeyHash(key, 10);
	
	ptr_dict->content = malloc(n);

	if (ptr_dict->content)
	{
		strcpy(&(ptr_dict->key[0]), key);
		memcpy(ptr_dict->content, value, n);

		return ptr_dict->content;
	}

	return 0;
}

void remDict(dict *ptr_dict, char *key)
{}



int main(void)
{
	//unsigned int newHash;
	//char userKey[128];
	//char *ptr_userKey = 0;

	dict *d = newDict(10, true);
	int test = 27;

	void *p = addDict(d, "test", &test, sizeof(test));
	printf(">>> %p\n", p);

	for (int i = 0; i < 10; i++)
	{
		printf("[%d] %s : ", i, d->key);
		int *p = (int *) d->content;
		printf("[%d] %d\n", i, *p);
		
		d++;
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
