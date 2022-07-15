/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/
#ifndef _LU_TYPES_H
#define _LU_TYPES_H

#define lu_p_void void*

#define lu_byte uint8_t
#define lu_p_byte uint8_t*

#define lu_time unsigned long
#define LU_TIME__MAX ULONG_MAX

#define lu_round round 
#define lu_floor floor
#define lu_value_abs fabs
#define LU_VALUE__MIN DBL_MIN
#define LU_VALUE__MAX DBL_MAX

struct lu_size_range {
	lu_size begin;
	lu_size end;
};

typedef lu_value (*lu_fp_compare)(lu_p_void x, lu_p_void y);
typedef lu_bool (*lu_fp_is_value)(lu_p_void value);
typedef lu_value(*lu_fp_get_value)(lu_p_void);

#endif // _LU_TYPES_H
