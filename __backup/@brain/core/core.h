/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_CORE_H
#define _LU_CORE_H

#include "lib/utils.h"
#include "lib/sis_alloc.h"

#include "@brain/net/neu.h"
#include "@brain/net/lin.h"

#include "neu_time.h"
#include "processor.h"
#include "waves/wave.h"

///////////////////////////////////////////////////////////////////////////////
// Types and structs

struct core {
	SisAlloc 	neus;
	SisAlloc 	lins;

	struct 		neu_time t;

	SisAlloc 	waves;
	Processor 	proc;
};

typedef struct core* Core;

///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

Core core_create(lu_size synapse_buff_size, lu_size neuron_buff_size, lu_size wave_buff_size, lu_size processor_buff_size);

static inline Core core_create_for_test() 
{
	return core_create(30, 30, 30, 30);
}

void core_destroy(Core* luram);

///////////////////////////////////////////////////////////////////////////////
// Allocators

Neu core_neu_alloc(Core);

static inline void core_neu_free(Core self, Neu neu)
{
	sis_alloc_item_free(self->neus, (lu_p_byte) neu);
}

Lin core_lin_alloc(Core);

static inline void core_lin_free(Core self, Lin lin)
{	
	sis_alloc_item_free(self->lins, (lu_p_byte) lin);
}

static inline lu_size core_neu_count(Core self)
{
	return self->neus->count;
}

static inline lu_time core_t_get(Core self)
{
	return neu_time_get(&self->t);
}

static inline lu_time core_t_inc(Core self)
{
	return neu_time_inc(&self->t);
}

#endif // _LU_CORE_H
