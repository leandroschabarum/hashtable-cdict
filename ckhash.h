#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define DICT_MAX_SIZE UINT_MAX
#define KEY_MAX_SIZE 64
#define SIGNATURE_ID 2
#define CHAR_CHUNK_SIZE 4


unsigned int charkey_hash(char *strkey)
/* charkey_hash() returns a unique integer identifier for
each different key string that is passed as argument.
Based on the polynomial rolling hash function */
{
	unsigned int chkID (unsigned char *chars, int index)
	/* chkID() returns an identifier for each group of size
	CHAR_CHUNK_SIZE characters from the original key string */
	{
		int hashID = 0;

		for(int i = 0; i < CHAR_CHUNK_SIZE; i++) {
			hashID = hashID + (int)(chars[i])*pow(SIGNATURE_ID, i);
		};

		return hashID * (index + 1);
	};

	unsigned int keyLength, keyHash, chunkIndex, chunkHash;
	unsigned char *chunkTemp;
	chunkTemp = (unsigned char *)(malloc(CHAR_CHUNK_SIZE));
	keyHash = 0;
	chunkIndex = 0;

	keyLength = (strlen(strkey) < KEY_MAX_SIZE) ? strlen(strkey) : KEY_MAX_SIZE;
	strkey[keyLength] = '\0';
	/* Ternary operator ensures keyLength to be less or equal to KEY_MAX_SIZE.
	Because of that strkey will be cut down to that control length and ensure
	that the keyHash won't overflow UINT_MAX (unsigned int limit) */

	for(int i = 0; i < keyLength; i += CHAR_CHUNK_SIZE) {
		sprintf(chunkTemp, "%*c", CHAR_CHUNK_SIZE, '\0');
		/* sprintf() here makes sure garbage collection from
		memory won't interfere with the chunkHash generated */

		for(int j = 0; j < CHAR_CHUNK_SIZE; j++) {
			/* This inner loop goes over the skipped indexes from the
			outside loop. It does so to fill the chunkTemp variable.
			From a time complexity standpoint, combined both loops
			still take together O(n) time to complete */

			if(strkey[i + j] != '\0') {
				chunkTemp[j] = strkey[i + j];
			} else {
				break;
			};
		};

		chunkHash = chkID(chunkTemp, chunkIndex);
		keyHash = keyHash + (chunkHash * pow(SIGNATURE_ID, chunkIndex));
		chunkIndex++;
	};

	printf("\nKey String: %s\nKey Length: %d\nKey Hash: %u\n\n", strkey, keyLength, keyHash);
	free(chunkTemp);
	return keyHash;
}
