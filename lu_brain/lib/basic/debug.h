/**
	Copyright © 2022 Oleh Ihorovych Novosad
*/
#ifndef _LU_DEBUG_H
#define _LU_DEBUG_H

#include <assert.h>

///////////////////////////////////////////////////////////////////////////////
// Debug related macroses


void lu__debug_internal(const char * format, ...);
void lu__debug_message_internal(const char* file, int line, const char * message);

#define lu__debug lu__debug_internal
#define lu__debug_message(message) lu__debug_message_internal(__FILE__, __LINE__, message)
#define lu__debug_message_args(message, ...) lu__debug_message_internal(__FILE__, __LINE__, message, __VA_ARGS__)

#define lu__save_debug printf

#define LU_DEBUG 1

#define lu__assert assert

///////////////////////////////////////////////////////////////////////////////
// Label gen

#define LU__ASCII_UPCASE_START 65
#define LU__ASCII_UPCASE_END 90

struct lu_laber_gen 
{
	char l_char;
	unsigned int l_num;
};

typedef struct lu_laber_gen* LabelGen;

struct lu_laber_gen g_label_gen;

static void lu_label_gen__set(char* lbl);



#endif // _LU_DEBUG_H