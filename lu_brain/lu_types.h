/**
	Copyright © 2020 Oleh Ihorovych Novosad
*/
#ifndef _LU_TYPES_PUB_H
#define _LU_TYPES_PUB_H

#include <stddef.h>
#include <stdbool.h>
#include <wchar.h>

#define lu_size size_t
#define LU_SIZE_MAX SIZE_MAX

#define lu_p_size lu_size*
#define lu_value double
#define lu_p_value lu_value*
#define lu_char	wchar_t  
#define lu_string const lu_char*
#define lu_bool bool 


#endif // _LU_TYPES_PUB_H

