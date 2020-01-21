/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/
#ifndef _LU_NEU_PROC_H
#define _LU_NEU_PROC_H

#include "global/lu_types.h"
#include "lib/lists/list.h"

///////////////////////////////////////////////////////////////////////////////
// Types and structs

typedef struct processor* Processor;

// ne zalezhyt vid request, tobto vsi requests mayut odyn processor
// dlia save_wave my identyfikuyemo wave po time (yakyy po suti ye takozh id) 
struct processor {
	List neus;
};

///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

Processor processor_create(lu_size processor_buff_size);
void processor_destroy(Processor*);

///////////////////////////////////////////////////////////////////////////////
// Getters / Setters

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void processor_validate(Processor);

///////////////////////////////////////////////////////////////////////////////
// Other public methods



#endif // _LU_NEU_PROC_H
