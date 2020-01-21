/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_NEU_H
#define _LU_NEU_H

#include "neto.h"
#include "lin.h"
#include "@brain/core/waves/wave.h"

///////////////////////////////////////////////////////////////////////////////
// Structs and types

typedef enum   
{
	NEU_WAVE_END = 1,
	NEU_SOMETHING1 = 2, 
	NEU_SOMETHING2 = 4
} lu_neu_flags;

typedef struct neu* Neu;

struct neu
{
	struct neto  	super;
	lu_value 		p;
	lu_value 		count;
	lu_time 		s_t;

	lu_time 		t; // TODO: delete

	lu_neu_flags	flags; // TODO: delete

	Lin 			l_p; // TODO: delete
	Lin 			l_c; // TODO: delete

	#ifdef LU_DEBUG// TODO: delete
	char 			lbl[20]; // TODO: delete
	#endif // TODO: delete
};

#define neu_create lu_neuron_create
#define neu_destroy lu_neuron_destroy

///////////////////////////////////////////////////////////////////////////////
// Init 

void neu_init_default(Neu self);

///////////////////////////////////////////////////////////////////////////////
// Receive 

static inline void neu_receive(Neu self, lu_value p)
{ 
	self->p += p;
}   

static inline void neu_p_clear(Neu self);
static inline void neu_receive_with_t(Neu self, lu_value p, lu_time t)
{
	if (t != 0 && t != self->t)
	{
		neu_p_clear(self);
		self->t = t;
	}

	neu_receive(self, p);
}

///////////////////////////////////////////////////////////////////////////////
// Getters / setters

static inline lu_value neu_norm_p(Neu self)
{
	return self->count < 1.0 ? 0 : self->p / self->count;
}

static inline void neu_inc_count(Neu self)
{
	++self->count;
}

static inline void neu_p_clear(Neu self)
{
	self->p = 0;
}

// IMPORTANT! 
static inline void neu_p_set(Neu self, lu_value val)
{
	// IMPORTANT! 
	self->p = val * (self->count == 0 ? 1.0 : self->count);
}

static inline void neu_flag(Neu self, lu_neu_flags flag)
{
	self->flags |= flag;
}

static inline void neu_unflag(Neu self, lu_neu_flags flag)
{
	self->flags &= ~flag;
}

static inline bool neu_has_flag(Neu self, lu_neu_flags flag)
{
	return self->flags & flag;
}

///////////////////////////////////////////////////////////////////////////////
// Flags

static inline bool neu_isave_wave_end(Neu self)
{
	return neu_has_flag(self, NEU_WAVE_END);
}

///////////////////////////////////////////////////////////////////////////////
// Other

void neu_debug(Neu self);




#endif // _LU_NEU_H
