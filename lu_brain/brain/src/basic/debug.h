/**
	Copyright © 2020 Oleh Ihorovych Novosad
*/
#ifndef _LU_DEBUG_H
#define _LU_DEBUG_H

#include <assert.h>

///////////////////////////////////////////////////////////////////////////////
// Debug related macroses

void lu_printf(const char* file, int line, const char * format, ...);

#define lu_debug_message(format) lu_printf(__FILE__, __LINE__, format)
#define lu_debug(format, ...) lu_printf(__FILE__, __LINE__, format, __VA_ARGS__)

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

struct label_gen g_label_gen;

void label_gen_set(char* lbl);



#endif // _LU_DEBUG_H