/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_SYSTEM_H
#define _LU_SYSTEM_H

#include "mem.h"

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct system* System;

 	struct system {
 		Mem 	mem;
 		Mem 	mem_default;
 	};

///////////////////////////////////////////////////////////////////////////////
// 

	System system_create(lu_size mem_size_in_bytes);
	void system_destroy(System self);

	//
	// Self check memory for potential leaks or bugs.
	//
	void system_mem_check(System self);

#endif // _LU_SYSTEM_H
