/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_SYSTEM_H
#define _LU_SYSTEM_H


///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct system* System;

	// Ya ne mozhu vykorystovuvaty system yak global zminnu bo
	// mem_perm specifichna dlia kozhnoho brain. 
	// Faktychno system - ce system (allocated) resourses yaki usaye brain.
 	struct system {
		Mem 			 	mem_perm;
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
