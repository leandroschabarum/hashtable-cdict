#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "hashFunc.h"

#define KEY_MAX_SIZE 64


typedef struct DictElement
{
	char *key;
	unsigned int size;
	void *data;
	void *next;
} entry;

typedef struct Dictionary
{
	unsigned int length;
	void *entries;
} dict;


/**
 * Function for creating new dictionary structure.
 *
 * @param unsigned int dict_size
 * @return dict*
 */
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
	// *if memSafe is set to true then raises
	// an error and resume program execution
	if (memSafe)
	{
		fprintf(stderr, "unable to allocate memory for new dictionary <%lu bytes>\n", (sizeof(void) * dict_size));
		exit(EXIT_FAILURE);
	}

	return 0;
}


/**
 * Function for displaying given dictionary entry.
 *
 * @param entry *ptr_entry
 */
void showEntry(entry *ptr_entry)
{
	if (ptr_entry && ptr_entry->key)
	{
		printf("# %s => mem(%p) : %d bytes\n", ptr_entry->key, ptr_entry->data, ptr_entry->size);
	}
	else
	{
		printf("# NULL\n");
	}
}


/**
 * Function for displaying all dictionary entries.
 *
 * @param dict *ptr_dict
 */
void showDict(dict *ptr_dict)
{
	if (ptr_dict)
	{
		int i = 0;
		entry *linked_entry = 0;

		if (ptr_dict->entries)
		{
			printf("\n>>> BEGIN");
			entry *ptr_entry = ptr_dict->entries;

			for (i = 0; i < ptr_dict->length; i++)
			{
				linked_entry = ptr_entry;
				printf("\n@ %d\n", i); 

				while (linked_entry)
				{
					showEntry(linked_entry);
					linked_entry = linked_entry->next;
				}
	
				ptr_entry++;
			}

			printf("<<< END\n");
		}
	}
}


/**
 * Function for setting given key to specified value.
 *
 * @param dict *ptr_dict
 * @param const char *key
 * @param const void *data
 * @param unsigned int data_size
 * @return void
 */
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

	entry *ptr_entry = ptr_dict->entries;
	
	if (key_size > 0)
	{
		// increments dictionary pointer
		// to key hashed index in array
		ptr_entry += charKeyHash(local_key_copy, ptr_dict->length);

		if (ptr_entry && ptr_entry->key)
		{
			// when entry is already in use
			// loop through linked list until
			// empty pointer is found
			while (ptr_entry->next)
			{
				ptr_entry = ptr_entry->next;
			}
			
			ptr_entry->next = (entry *) malloc(sizeof(entry));
			ptr_entry = ptr_entry->next;
		
			if (! ptr_entry)
			{
				fprintf(stderr, "[unsufficient memory] unable to allocate <%lu bytes> for new dictionary entry\n", sizeof(entry));
				exit(EXIT_FAILURE);
			}
			
			memset(ptr_entry, 0, sizeof(entry));
		}

		ptr_entry->key = (char *) malloc(key_size + 1);
		
		if (! ptr_entry->key)
		{
			fprintf(stderr, "[unsufficient memory] unable to allocate <%u bytes> for key <%s>\n", (key_size + 1), local_key_copy);
			exit(EXIT_FAILURE);
		}

		// using strcpy() because local_key_copy
		// is always null terminated and within
		// expected maximum size for dictionary key
		strcpy(ptr_entry->key, local_key_copy);
		ptr_entry->data = (void *) malloc(data_size);
		
		if (! ptr_entry->data)
		{
			fprintf(stderr, "[unsufficient memory] unable to allocate <%u bytes> for data at <%p>\n", data_size, data);
			exit(EXIT_FAILURE);
		}

		// sets the data_size argument
		// as an attribute of dict entry 
		ptr_entry->size = data_size;
		memcpy(ptr_entry->data, data, data_size);
	}
}


/**
 * Function to delete given key from dictionary.
 *
 * @param dict *ptr_dict
 * @param char *key
 * @return void
 */
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

	entry *ptr_entry = ptr_dict->entries;
	
	if (key_size > 0)
	{
		entry *tmp_entry = 0;

		// increments dictionary pointer
		// to key hashed index in array
		ptr_entry += charKeyHash(local_key_copy, ptr_dict->length);

		// when entry is not the given key to delete,
		// loop through linked list until key is
		// found or empty pointer is reached
		while (strcmp(local_key_copy, ptr_entry->key) != 0)
		{
			tmp_entry = ptr_entry;

			if (ptr_entry->next)
			{
				ptr_entry = ptr_entry->next;
				continue;
			}

			break;
		}

		showEntry(ptr_entry); // DEBUG
		
		// clears stored data and sets
		// the address to a null pointer
		// after freeing allocated memory
		if (tmp_entry)
		{
			// case when there is a previous entry to the
			// mapped key, then tmp_entry points to it
			tmp_entry->next = ptr_entry->next;
			ptr_entry->next = 0;

			memset(ptr_entry->key, 0, key_size);
			free(ptr_entry->key);
			ptr_entry->key = 0;

			memset(ptr_entry->data, 0, ptr_entry->size);
			free(ptr_entry->data);
			ptr_entry->data = 0;
			ptr_entry->size = 0;

			free(ptr_entry);
			ptr_entry = 0;
		}
		else
		{
			// case when there is no previous entry to the mapped
			// key, then tmp_entry points to the next one
			tmp_entry = ptr_entry->next;
			ptr_entry->next = 0;

			memset(ptr_entry->key, 0, key_size);
			free(ptr_entry->key);
			ptr_entry->key = 0;

			memset(ptr_entry->data, 0, ptr_entry->size);
			free(ptr_entry->data);
			ptr_entry->data = 0;
			ptr_entry->size = 0;

			// checks if next entry exists and if so,
			// copies next entry data over to current one
			if (tmp_entry)
			{
				ptr_entry->key = (char *) malloc(strlen(tmp_entry->key) + 1);

				if (! ptr_entry->key)
				{
					fprintf(stderr, "[unsufficient memory] unable to allocate <%lu bytes> for key <%s>\n", (strlen(tmp_entry->key) + 1), tmp_entry->key);
					exit(EXIT_FAILURE);
				}

				strcpy(ptr_entry->key, tmp_entry->key);
				memset(tmp_entry->key, 0, strlen(ptr_entry->key));
				free(tmp_entry->key);
				tmp_entry->key = 0;
				
				ptr_entry->data = (void *) malloc(tmp_entry->size);

				if (! ptr_entry->data)
				{
					fprintf(stderr, "[unsufficient memory] unable to allocate <%u bytes> for data at <%p>\n", tmp_entry->size, tmp_entry->data);
					exit(EXIT_FAILURE);
				}

				memcpy(ptr_entry->data, tmp_entry->data, tmp_entry->size);
				ptr_entry->size = tmp_entry->size;
				memset(tmp_entry->data, 0, ptr_entry->size);
				free(tmp_entry->data);
				tmp_entry->data = 0;
				tmp_entry->size = 0;
				
				ptr_entry->next = tmp_entry->next;
				tmp_entry->next = 0;
			
				free(tmp_entry);
				tmp_entry = 0;
			}
		}
	}
}


/**
 * Function to retrieve memory address of value stored at given key.
 *
 * @param dict *ptr_dict
 * @param const char *key
 * @return void*
 */
void* getKey(dict *ptr_dict, const char *key)
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

	entry *ptr_entry = ptr_dict->entries;

	if (key_size > 0)
	{
		ptr_entry += charKeyHash(local_key_copy, ptr_dict->length);

		// when entry is not the given key, loop
		// through linked list until key is
		// found or empty pointer is reached
		while (strcmp(local_key_copy, ptr_entry->key) != 0)
		{
			if (ptr_entry->next)
			{
				ptr_entry = ptr_entry->next;
				continue;
			}

			break;
		}

		showEntry(ptr_entry); // DEBUG

		return (ptr_entry ? ptr_entry->data : 0);
	}

	return 0;
}


int main(void)
{
	dict *d = newDict(5, 1);

	int test_int = 123;
	float test_float = 12.345;
	char test_char[8] = "testing";

	printf("adding keys...\n");
	setKey(d, "int", &test_int, sizeof(test_int));
	setKey(d, "char", &test_char[0], strlen(test_char));
	setKey(d, "int2del", &test_int, sizeof(test_int));
	setKey(d, "float", &test_float, sizeof(test_float));
	showDict(d);

	printf("\ndeleting keys...\n");
	delKey(d, "int2del");
	showDict(d);
	
	printf("\nReturning stored values...\n");
	char *string = getKey(d, "char");
	printf(">>> %s\n", string);

	int *integer = getKey(d, "int");
	printf(">>> %d\n", *integer);

	float *decimal = getKey(d, "float");
	printf(">>> %f\n", *decimal);

	return 0;
}
