/**
	Copyright © 2021 Oleh Ihorovych Novosad
*/
#ifndef _LU_DEBUG_H
#define _LU_DEBUG_H

#include <assert.h>

///////////////////////////////////////////////////////////////////////////////
// Debug related macroses


void lu_debug_internal(const char * format, ...);
void lu_debug_message_internal(const char* file, int line, const char * message);

#define lu_debug lu_debug_internal
#define lu_debug_message(message) lu_debug_message_internal(__FILE__, __LINE__, message)
#define lu_debug_message_args(message, ...) lu_debug_message_internal(__FILE__, __LINE__, message, __VA_ARGS__)

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

static void label_gen_set(char* lbl);



#endif // _LU_DEBUG_H