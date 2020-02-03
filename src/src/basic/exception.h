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
	LU_E_PH_MEM_ALLOC_FAILED,
	LU_E_PH_MEM_OUT_OF_MEMORY, 
	LU_E_PH_MEM_OUT_OF_BLOCK_MEMORY,

	LU_E_LAST
};

void lu_throw(enum lu_e e, lu_cstring fmt, ...);

#endif // _LU_EXCEPTION_H

