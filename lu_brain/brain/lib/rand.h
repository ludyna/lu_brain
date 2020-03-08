/**
	Copyright © 2020 Oleh Ihorovych Novosad (Novossaad)
*/
#ifndef _LU_RAND_H
#define _LU_RAND_H

#include "basic/basic.h"

#define LU_RAND_BITS_SIZE 2048

extern lu_size g_rand_bits_indx;
extern lu_bool g_rand_bits[LU_RAND_BITS_SIZE];

static inline lu_bool toss_coin()
{
	if (g_rand_bits_indx >= LU_RAND_BITS_SIZE) g_rand_bits_indx = 0;
	return g_rand_bits[g_rand_bits_indx++]; // rand()%2; 
}	

#endif // _LU_RAND_H