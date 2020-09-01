/**
	Copyright © 2020 Oleh Ihorovych Novosad
*/
#ifndef _LU_UTIL_H
#define _LU_UTIL_H

#include "types.h"
#include "debug.h"

#define LU_NON_SIGNF 0.0001

/**
	Frees memory, sets pointer to NULL and prevents double freeing.
*/
void lu_free(void **p);

static inline lu_bool lu_value_eq(lu_value a, lu_value b)
{
	return lu_value_abs(a - b) < LU_NON_SIGNF;
}

#endif // _LU_UTIL_Hy