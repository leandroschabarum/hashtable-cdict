#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "hashFunc.h"

#define KEY_MAX_SIZE 64

typedef struct DictElement
{
	int size;
	void *value;
} content;

typedef struct Dictionary
{
	char *key;
	content *data;
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
	// if memSafe is true then raises an error and resume
	if (! localDict)
	{
		if (memSafe)
		{
			fprintf(stderr, "unable to allocate memory for new dictionary <%lu bytes>\n", (sizeof(dict) * dict_size));
			exit(EXIT_FAILURE);
		}

		return 0;
	}

	return &localDict[0];
}

void setKey(dict *ptr_dict, const char *key, const void *data, unsigned int data_size)
{
	unsigned int key_size = 0;
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
			fprintf(stderr, "[unsufficient memory] unable to allocate <%u bytes> for <%s>\n", (key_size + 1), local_key_copy);
			exit(EXIT_FAILURE);
		}
		// using strcpy() because local_key_copy
		// is always null terminated and within
		// expected maximum size for dictionary key
		strcpy(ptr_dict->key, local_key_copy);
		
		// allocates memory for struct
		// that will hold key entry data
		ptr_dict->data = (content *) malloc(sizeof(content));

		if (ptr_dict->data)
		{
			// clears allocated memory garbage
			// and sets the data_size argument
			// as an attribute of that struct
			memset(ptr_dict->data, 0, sizeof(content));
			ptr_dict->data->size = data_size;
			// allocates memory to hold given data
			// and copy it over to received address
			ptr_dict->data->value = (void *) malloc(data_size);

			if (! ptr_dict->data)
			{
				fprintf(stderr, "[unsufficient memory] unable to allocate <%u bytes> for given data <%p>\n", data_size, data);
				exit(EXIT_FAILURE);
			}

			memcpy(ptr_dict->data->value, data, data_size);
		}
	}
}

void delKey(dict *ptr_dict, char *key)
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
		// clears stored data and sets
		// the address to a null pointer
		// after freeing allocated memory
		memset(ptr_dict->key, 0, key_size);
		free(ptr_dict->key);
		ptr_dict->key = 0;
		
		memset(ptr_dict->data->value, 0, ptr_dict->data->size);
		free(ptr_dict->data->value);
		ptr_dict->data->size = 0;
		free(ptr_dict->data);
		ptr_dict->data = 0;
	}
}



int main(void)
{
	//unsigned int newHash;
	//char userKey[128];
	//char *ptr_userKey = 0;

	dict *d = newDict(10, 1);
	printf(">>> dict : %lu bytes\n\n", 10*sizeof(*d));

	int test = 27;

	setKey(d, "test", &test, sizeof(test));
	setKey(d, "abc", &test, sizeof(test));
	delKey(d, "test");

	for (int i = 0; i < 10; i++)
	{
		printf("%d: (%s) [%p]\n", i, (char *) d->key, d->data);
		printf("\t%d bytes -> %p", ((d->data) ? d->data->size : 0), ((d->data) ? d->data->value : 0));
		printf(" -> %d\n", (d->data) ? *((int *) d->data->value) : 0);
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
