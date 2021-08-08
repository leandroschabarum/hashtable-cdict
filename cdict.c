#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "hashFunc.h"

#define KEY_MAX_SIZE 64


typedef struct DictContent
{
	int size;
	void *value;
} content;

typedef struct DictElement
{
	char *key;
	content *data;
} entry;

typedef struct Dictionary
{
	int length;
	entry *entries;
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
	
	static dict *local_dict = 0;
	local_dict = (dict *) malloc(sizeof(dict));

	if (local_dict)
	{
		local_dict->length = dict_size;
		local_dict->entries = (entry *) malloc(sizeof(entry) * dict_size);
		
		if (local_dict->entries)
		{
			memset(local_dict->entries, 0, (sizeof(entry) * dict_size));
			return local_dict;
		}
	}

	// in case no memory was allocated for
	// new dictionary returns null pointer
	// if memSafe is set to true then raises
	// an error and resume program execution
	if (memSafe)
	{
		fprintf(stderr, "unable to allocate memory for new dictionary <%lu bytes>\n", (sizeof(entry) * dict_size));
		exit(EXIT_FAILURE);
	}

	return 0;
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

	entry *ptr_entry = &ptr_dict->entries[0];
	
	if (key_size > 0)
	{
		// increments dictionary pointer
		// to key hashed index in array
		ptr_entry += charKeyHash(local_key_copy, ptr_dict->length);
		ptr_entry->key = (char *) malloc(key_size + 1);
		
		if (! ptr_entry->key)
		{
			fprintf(stderr, "[unsufficient memory] unable to allocate <%u bytes> for <%s>\n", (key_size + 1), local_key_copy);
			exit(EXIT_FAILURE);
		}
		// using strcpy() because local_key_copy
		// is always null terminated and within
		// expected maximum size for dictionary key
		strcpy(ptr_entry->key, local_key_copy);
		
		// allocates memory for struct
		// that will hold key entry data
		ptr_entry->data = (content *) malloc(sizeof(content));

		if (ptr_entry->data)
		{
			// clears allocated memory garbage
			// and sets the data_size argument
			// as an attribute of that struct
			memset(ptr_entry->data, 0, sizeof(content));
			ptr_entry->data->size = data_size;
			// allocates memory to hold given data
			// and copy it over to received address
			ptr_entry->data->value = (void *) malloc(data_size);

			if (! ptr_entry->data)
			{
				fprintf(stderr, "[unsufficient memory] unable to allocate <%u bytes> for given data <%p>\n", data_size, data);
				exit(EXIT_FAILURE);
			}

			memcpy(ptr_entry->data->value, data, data_size);
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

	entry *ptr_entry = &ptr_dict->entries[0];
	
	if (key_size > 0)
	{
		// increments dictionary pointer
		// to key hashed index in array
		ptr_entry += charKeyHash(local_key_copy, ptr_dict->length);
		// clears stored data and sets
		// the address to a null pointer
		// after freeing allocated memory
		memset(ptr_entry->key, 0, key_size);
		free(ptr_entry->key);
		ptr_entry->key = 0;
		
		memset(ptr_entry->data->value, 0, ptr_entry->data->size);
		free(ptr_entry->data->value);
		ptr_entry->data->size = 0;
		free(ptr_entry->data);
		ptr_entry->data = 0;
	}
}

void showDict(dict *ptr_dict)
{
	if (ptr_dict)
	{
		int i = 0;

		if (ptr_dict->entries)
		{
			printf("\n>>> BEGIN");
			entry *ptr_entry = ptr_dict->entries;

			for (i = 0; i < ptr_dict->length; i++)
			{
				printf("\n#%d: %s => mem(%p)\n", i, ptr_entry->key, ptr_entry->data);
	
				if (ptr_entry->data)
				{
					printf("|- <%d bytes> mem(%p)", ptr_entry->data->size, ptr_entry->data->value);
					printf("\t%d\n", *((int *) ptr_entry->data->value));
				}
	
				ptr_entry++;
			}

			printf("<<< END\n");
		}
	}
}



int main(void)
{
	//unsigned int newHash;
	//char userKey[128];
	//char *ptr_userKey = 0;

	dict *d = newDict(10, 1);

	int test = 27;

	setKey(d, "test", &test, sizeof(test));
	setKey(d, "abc", &test, sizeof(test));
	showDict(d);

	setKey(d, "def", &test, sizeof(test));
	delKey(d, "test");
	showDict(d);

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
