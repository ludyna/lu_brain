/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/
#ifndef _LU_WAVE_H
#define _LU_WAVE_H

#include "global/lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// Types and structs

typedef struct wave* Wave;
typedef struct neu* Neu;
typedef struct core* Core;
typedef void (*lu_fp_excite)(Wave, Neu);

struct wave {
	Core 			core;
	lu_time 		t;
	lu_value		signif;
	lu_fp_excite 	excite;
	bool 			active;

	lu_size 		neu_excited_count;
};

///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

static inline Wave wave_init(Wave self, lu_time t, lu_value signif)
{
	self->t 					= t;
	self->signif 				= signif;
	self->excite 				= NULL;
	self->active 				= true;
	self->neu_excited_count 	= 0;

	return self;
}

Wave wave_create(lu_time t, lu_value signif);
void wave_destroy(Wave*);
///////////////////////////////////////////////////////////////////////////////
// Getters / Setters

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void wave_validate(Wave);

///////////////////////////////////////////////////////////////////////////////
// Other public methods



#endif // _LU_WAVE_H
