#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define DICT_MAX_SIZE UINT_MAX
#define KEY_MAX_SIZE 64
#define SIGNATURE_ID 2
#define CHAR_CHUNK_SIZE 4


unsigned int NEWcharkey_hash(char *strkey, int keyLength)
/* NEWcharkey_hash returns a unique integer identifier for
each different key string that is passed as argument. */
{
	unsigned int chkID (unsigned char *chars, int index)
	/* chkID returns an identifier for each group of size
	CHAR_CHUNK_SIZE characters from the original key string */
	{
		int hashID = 0;

		for(int i = 0; i < CHAR_CHUNK_SIZE; i++) {
			hashID = hashID + (int)(chars[i])*pow(SIGNATURE_ID, i);
		};

		return hashID * (index + 1);
	};

	unsigned int keyLen, keyHash, chunkIndex, chunkHash;
	unsigned char *chunkTemp;
	chunkTemp = (unsigned char *)(malloc(CHAR_CHUNK_SIZE));
	keyLen = (keyLength < KEY_MAX_SIZE) ? keyLength : KEY_MAX_SIZE;
	keyHash = 0;
	chunkIndex = 0;

	for(int i = 0; i < keyLen; i += CHAR_CHUNK_SIZE) {

		for(int j = 0; j < CHAR_CHUNK_SIZE; j++) {
			chunkTemp[j] = strkey[i + j];
		};
		chunkTemp[CHAR_CHUNK_SIZE] = '\0';

		chunkHash = chkID(chunkTemp, chunkIndex);
		keyHash = keyHash + (chunkHash * pow(SIGNATURE_ID, chunkIndex));
		chunkIndex++;

		printf("< %s : %u >\n", chunkTemp, chunkHash);
		free(chunkTemp);
	};
	printf("\nKey String: %s\nKey Length: %d\nKey Hash: %u\n\n", strkey, keyLen, keyHash);

	return keyHash;
}




unsigned int OLDcharkey_hash(char key[KEY_MAX_SIZE])
/* OLDcharkey_hash returns a unique integer identifier for
each different key string that is passed as argument. */
{
	unsigned int chkID (unsigned char *chars, int *index)
	/* chkID returns an identifier for each group of size
	CHAR_CHUNK_SIZE characters from the original key string */
	{
		int hashID = 0;

		for(int i = 0; i < CHAR_CHUNK_SIZE; i++) {
			hashID = hashID + (int)(chars[i])*pow(SIGNATURE_ID, i);
		};

		return hashID * (*index + 1);
	};

	unsigned int keyLength, keyHash, chunkIndex, chunkHash;
	unsigned char *chunkTemp;
	chunkTemp = (unsigned char *)(malloc(CHAR_CHUNK_SIZE));
	keyLength = strlen(key);
	keyLength = (keyLength < KEY_MAX_SIZE) ? keyLength : KEY_MAX_SIZE;
	keyHash = 0;
	chunkIndex = 0;

	for(int i = 0; i < keyLength; i += CHAR_CHUNK_SIZE) {

		for(int j = 0; j < CHAR_CHUNK_SIZE; j++) {
			chunkTemp[j] = key[i + j];
		};

		chunkTemp[CHAR_CHUNK_SIZE] = '\0';
		chunkHash = chkID(chunkTemp, &chunkIndex);
		keyHash = keyHash + chunkHash*pow(SIGNATURE_ID, chunkIndex);
		chunkIndex++;

		printf("< %s : %u >\n", chunkTemp, chunkHash);
		free(chunkTemp);
	};
	printf("\nKey String: %s\nKey Length: %d\nKey Hash: %u\n\n", key, keyLength, keyHash);

	return keyHash;
};
