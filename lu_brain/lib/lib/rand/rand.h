/**
	Copyright © 2020 Oleh Ihorovych Novosad (Novossaad)
*/

#define LU_RAND_BITS_SIZE 2048

extern lu_size g_rand_bits_indx;
extern lu_bool g_rand_bits[LU_RAND_BITS_SIZE];

static inline lu_bool toss_coin()
{
	if (g_rand_bits_indx >= LU_RAND_BITS_SIZE) g_rand_bits_indx = 0;
	return g_rand_bits[g_rand_bits_indx++]; // rand()%2; 
}	


