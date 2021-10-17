/*------------------ HEADERFILE ------------------*/
/*CREATOR: Leandro Schabarum                      */
/*DESCRIPTION: Hash table data structure          */
/*------------------------------------------------*/

#ifndef CKHASH_H  // once only header guard (wrapper)
#define CKHASH_H

#define MAX_DICT ((1L << (sizeof(unsigned int) * 8)) - 1)

#ifdef _cplusplus
extern "C" {
#endif


// Hashing function prototype
// file: charKeyHash.c
unsigned int charKeyHash(const char *key, unsigned int dict_max_size);


#ifdef _cplusplus
}
#endif
#endif // once only header guard (wrapper)

