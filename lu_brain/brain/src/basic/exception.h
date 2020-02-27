/**
	Copyright © 2020 Oleh Ihorovych Novosad
*/
#ifndef _LU_EXCEPTION_H
#define _LU_EXCEPTION_H

#include "vendor/CException.h"
#include "debug.h"

#define lu_exception CEXCEPTION_T
#define lu_try Try 
#define lu_catch Catch

// Exceptions list
enum lu_e {
	LU_E_FIRST = 6000, 
	
	// Mem 
	LU_E_MEM_ALLOC_FAIL, 

	// Brain
	LU_E_BRAIN_OPTS_REQUIRED, 
	LU_E_BRAIN_RECS_REQUIRED, 

	LU_E_LAST
};



void lu_throw_internal(enum lu_e e, const char* file, int line);
void lu_throw_with_message_internal(enum lu_e e, const char* file, int line, const char* fmt, ...);

#define lu_throw(e) lu_throw_internal(e, __FILE__, __LINE__);
#define lu_throw_with_message(e, msg, ...) lu_throw_with_message_internal(e, __FILE__, __LINE__, msg, __VA_ARGS__)

#endif // _LU_EXCEPTION_H

