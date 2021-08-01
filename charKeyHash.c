#include <math.h>
#include <string.h>

#define SIGNATURE_ID 2
#define CHAR_CHUNK_SIZE 4
#define MAX_HASH sizeof(unsigned int)


/**
 * Function for hashing string key into integer identifier.
 * Based on the polynomial rolling hash function.
 *
 * @param char *key
 * @return unsigned int
*/
unsigned int charKeyHash(const char *key)
{
	unsigned int hashSum, chunkSum, ps;
	int breakFlag, oi, ii;
	
	oi = 1;
	hashSum = 0;

	do
	{
		chunkSum = 0;

		for (ii = 0; ii < CHAR_CHUNK_SIZE; ii++)
		{
			// for each char in key chunk the partial sum is
			// calculated accordingly to ---> ascii*(sig)^n
			ps = (unsigned char)(*key) * pow(SIGNATURE_ID, ii);

			if ((ps > 0 && hashSum > MAX_HASH - (chunkSum + ps) * oi) || *key == '\0')
			{
				// reached maximum key hash
				// or end of the string
				breakFlag = 0;
				break;
			}
			// updates the chunk sum and advances
			// to the next memory address of key char
			chunkSum += ps;
			key++;
			// remains true therefore
			// maintains while loop
			breakFlag = 1;
		}
		// updates hash sum and increments outer
		// loop counter for the next key chunk
		hashSum += chunkSum * oi;
		oi++;
	}
	while (breakFlag);

	// key hash for given string
	return hashSum;
}
