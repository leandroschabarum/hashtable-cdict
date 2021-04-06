/*------------------ HEADERFILE ------------------*/
/*CREATOR: Leandro Schabarum                      */
/*DESCRIPTION: Hashing function                   */
/*------------------------------------------------*/

#ifndef CKHASH_H  // once only header guard (wrapper)
#define CKHASH_H

#ifdef _cplusplus
extern "C" {
#endif
// start declarations

#define KEY_MAX_SIZE 64

unsigned int charkey_hash(const char *strkey);
/*
 * Function for returning unique unsigned integer identifier for
 * each different character string passed as argument.
 * Based on the polynomial rolling hash function.
 * strkey (required) ---> pointer to char | string to be hashed
*/

// end declarations
#ifdef _cplusplus
}
#endif
#endif // once only header guard (wrapper)

