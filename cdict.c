#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "hashFunc.h"

#define KEY_MAX_SIZE 64


typedef struct Dictionary
{
	void *key;
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
	// if memSafe is true then raises an error
	if (! localDict)
	{
		if (memSafe)
		{
			fprintf(stderr, "[%u] unable to allocate memory for new dictionary\n", dict_size);
			exit(EXIT_FAILURE);
		}

		return 0;
	}

	return &localDict[0];
}

void addDict(dict *ptr_dict, const char *key, void *value)
{
	int key_size = 0;
	char local_key_copy[KEY_MAX_SIZE];

	while (*key != '\0' && key_size < (KEY_MAX_SIZE - 1))
	{
		local_key_copy[key_size] = *key;
		key_size++;
		key++;
	}
	// enforces key to always be null terminated
	local_key_copy[key_size] = '\0';
	
	if (key_size > 0)
	{
		// increments dictionary pointer
		// to key hashed index in array
		ptr_dict += charKeyHash(local_key_copy, 10);
		ptr_dict->key = (char *) malloc(key_size + 1);
		
		if (! ptr_dict->key)
		{
			fprintf(stderr, "[unsuficient memory] unable to allocate <%d bytes> for <%s>\n", key_size, local_key_copy);
			exit(EXIT_FAILURE);
		}
		// using strcpy() because local_key_copy
		// is always null terminated and within
		// expected maximum size for dictionary key
		strcpy(ptr_dict->key, local_key_copy);
		ptr_dict->content = value;
	}
}

void remDict(dict *ptr_dict, char *key)
{
	int key_size = 0;
	char local_key_copy[KEY_MAX_SIZE];

	while (*key != '\0' && key_size < (KEY_MAX_SIZE - 1))
	{
		local_key_copy[key_size] = *key;
		key_size++;
		key++;
	}
	// enforces key to always be null terminated
	local_key_copy[key_size] = '\0';
	
	if (key_size > 0)
	{
		// increments dictionary pointer
		// to key hashed index in array
		ptr_dict += charKeyHash(local_key_copy, 10);
		ptr_dict->key = 0;
		free(ptr_dict->key);
		free(ptr_dict->content);
	}
}



int main(void)
{
	//unsigned int newHash;
	//char userKey[128];
	//char *ptr_userKey = 0;

	dict *d = newDict(10, 1);
	printf(">>> dict : %lu bytes\n", 10*sizeof(*d));
	int test = 27;

	addDict(d, "0123456789abcdef", &test);
	// remDict(d, "0123456789abcdef");

	for (int i = 0; i < 10; i++)
	{
		printf("[%d] %s : %p\n", i, (char *) d->key, d->content);
		printf("\t>>> %d\n", (d->content) ? *((int *) d->content) : 0);
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
