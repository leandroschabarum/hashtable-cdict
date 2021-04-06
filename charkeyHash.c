#include <math.h>

#define SIGNATURE_ID 2
#define CHAR_CHUNK_SIZE 4

unsigned int charkey_hash(const char *strkey)
/*
 * Function for returning unique unsigned integer identifier for
 * each different character string passed as argument.
 * Based on the polynomial rolling hash function.
 * strkey (required) ---> pointer to char | string to be hashed
*/
{
	int breakFlag, oi, ii, gsum, lsum;
	breakFlag = 0;
	oi = 1;
	gsum = 0; // string hash sum

	while (breakFlag == 0)
	{
		ii = 0;
		lsum = 0; // string chunk hash sum

		while (ii < CHAR_CHUNK_SIZE)
		{
			lsum += (unsigned char)(*strkey) * pow(SIGNATURE_ID, ii);

			if (*strkey == '\0')
			{
				/* reached end of the string*/
				breakFlag = 1; // changes control variable for ending outside loop
				break;
			}
			else
			{
				strkey++; // increments memory address to next position
				ii++; // increments chunk loop counter
			}
		}

		gsum += lsum * oi;
		oi++;
	}

	return gsum; // key hash for given string
}
