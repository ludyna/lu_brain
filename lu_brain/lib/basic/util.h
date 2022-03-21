/**
	Copyright © 2022 Oleh Ihorovych Novosad
*/
#ifndef _LU_UTIL_H
#define _LU_UTIL_H

#include "types.h"
#include "debug.h"

#define LU__NON_SIGNF 0.0001

////
// Frees memory, sets pointer to NULL and prevents double freeing.
void lu_free(void **p);

static inline lu_bool lu_value__eq_with_signif(lu_value a, lu_value b, lu_value signif)
{
	return lu_value_abs(a - b) < signif;
}

static inline lu_bool lu_value_eq(lu_value a, lu_value b)
{
	return lu_value__eq_with_signif(a, b, LU__NON_SIGNF);
}



#endif // _LU_UTIL_Hy