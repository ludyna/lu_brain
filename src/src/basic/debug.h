/**
	Copyright © 2020 Oleh Ihorovych Novosad
*/
#ifndef _LU_DEBUG_H
#define _LU_DEBUG_H

#include <assert.h>

// for debug porposes
#define lu_debug printf

#define lu_save_debug printf

#define LU_DEBUG 1

#define lu_assert assert

///////////////////////////////////////////////////////////////////////////////
// Label gen

#define LU_ASCII_UPCASE_START 65
#define LU_ASCII_UPCASE_END 90

struct label_gen 
{
	char l_char;
	unsigned int l_num;
};

typedef struct label_gen* LabelGen;

///////////////////////////////////////////////////////////////////////////////
// Global 
struct label_gen g_label_gen;

void label_gen_set(char* lbl);

#endif // _LU_DEBUG_H