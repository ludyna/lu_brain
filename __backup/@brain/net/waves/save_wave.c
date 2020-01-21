/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/

#include <stdlib.h>
#include "lib/utils.h"
#include "neu_iters.h"
#include "save_wave.h"
 
///////////////////////////////////////////////////////////////////////////////
// Structs and types

///////////////////////////////////////////////////////////////////////////////
// Prototypes
 
///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

// void save_wave_init(SaveWave self, lu_time t)
// {
// 	self->top 	= NULL;
// 	self->t 	= t;
// }

// SaveWave save_wave_create()
// {
// 	SaveWave self = (SaveWave) malloc(sizeof(struct save_wave));

// 	save_wave_init(self, 0);

// 	return self;
// }

// void save_wave_destroy(SaveWave* self)
// {
// 	lu_free((void**) self);
// }

// ///////////////////////////////////////////////////////////////////////////////
// // Main public methods

// static void each_child_receive(Neu parent, Neu item, lu_p_void p1)
// { 
// 	SaveWave find_wave = (SaveWave) p1; 

// 	lu_debug("\nTWAVE CHILD p: %f p_norm: %f COUNT: %f TOP: %f", item->p, neu_norm_p(item), item->count, find_wave->top == NULL ? 0 : neu_norm_p(find_wave->top));

// 	if (find_wave->top == NULL || neu_norm_p(item) > neu_norm_p(find_wave->top))
// 	{
// 		find_wave->top = item;
// 	}
// }

// void save_wave_process(SaveWave self, Neu parent, lu_value p)
// {
// 	//neu_p_set(parent, p);
// 	neu_give_p_block_1p(parent, p, self->t, each_child_receive, self);
// }

// Neu save_wave_top(SaveWave self)
// {
// 	return self->top;
// }

///////////////////////////////////////////////////////////////////////////////
// Other methods

