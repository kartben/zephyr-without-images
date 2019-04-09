/******************************************************************************
*  Filename:       sw_ecrypt-machine.h
*  Revised:        2016-10-05 12:42:03 +0200 (Wed, 05 Oct 2016)
*  Revision:       47308
******************************************************************************/
/* ecrypt-machine.h */

/*
 * This file is included by 'ecrypt-portable.h'. It allows to override
 * the default macros for specific platforms. Please carefully check
 * the machine code generated by your compiler (with optimisations
 * turned on) before deciding to edit this file.
 */

/* ------------------------------------------------------------------------- */

#if (defined(ECRYPT_DEFAULT_ROT) && !defined(ECRYPT_MACHINE_ROT))

#define ECRYPT_MACHINE_ROT

#if (defined(WIN32) && defined(_MSC_VER))

#undef ROTL32
#undef ROTR32
#undef ROTL64
#undef ROTR64

#include <stdlib.h>

#define ROTL32(v, n) _lrotl(v, n)
#define ROTR32(v, n) _lrotr(v, n)
#define ROTL64(v, n) _rotl64(v, n)
#define ROTR64(v, n) _rotr64(v, n)

#endif

#endif

/* ------------------------------------------------------------------------- */

#if (defined(ECRYPT_DEFAULT_SWAP) && !defined(ECRYPT_MACHINE_SWAP))

#define ECRYPT_MACHINE_SWAP

/*
 * If you want to overwrite the default swap macros, put it here. And so on.
 */

#endif

/* ------------------------------------------------------------------------- */
