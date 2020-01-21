/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_NEU_TIME_H
#define _LU_NEU_TIME_H

#include "global/lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// Structs and types

struct neu_time
{
	lu_time t;
};

typedef struct neu_time* NeuTime;

///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

static inline void neu_time_init(NeuTime self)
{
	self->t = 1;
}

///////////////////////////////////////////////////////////////////////////////
// Main public methods

static inline lu_time neu_time_inc(NeuTime self)
{
	 if (self->t + 1 == LU_TIME_MAX)
	 {
	 	self->t = 1;
	 }

	 return ++self->t;
}

static inline lu_time neu_time_get(NeuTime self)
{
	return self->t;
}

#endif  // _LU_NEU_TIME_H