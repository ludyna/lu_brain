/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/

#include <stdlib.h>
#include "lib/utils.h" 
#include "neu_iters.h"
#include "find_wave.h"
 
///////////////////////////////////////////////////////////////////////////////
// Structs and types

///////////////////////////////////////////////////////////////////////////////
// Prototypes
 
///////////////////////////////////////////////////////////////////////////////
// Create and destroy
// static lu_value neu_compare_reverse(lu_p_void p1, lu_p_void p2)
// {
//     Neu x   = (Neu) p1;
//     Neu y   = (Neu) p2;

//     lu_value cmp = y->p - x->p;

//     return lu_value_abs(cmp) < 0.001 ? 0 : cmp;
// }

// FindWave find_wave_create(lu_size size, lu_value signif, lu_time t, lu_size apex_count)
// {
// 	FindWave self = (FindWave) malloc(sizeof(struct find_wave));

// 	// Initialize
// 	self->signif 	= signif;
// 	self->t 		= t;

// 	self->bottom 	= arr_create(size);
// 	self->top		= arr_create(size);
// 	self->apex 		= NULL;

// 	if (apex_count > 0) 
// 		self->apex 	= s_list_create(apex_count, neu_compare_reverse, S_LIST_LAST);

// 	return self;
// }

// void find_wave_destroy(FindWave* self)
// {
// 	if ((*self)->apex)
// 		s_list_destroy(&(*self)->apex);

// 	arr_destroy(&(*self)->top);
// 	arr_destroy(&(*self)->bottom);
// 	lu_free((void**) self);
// }

// ///////////////////////////////////////////////////////////////////////////////
// // Main public methods

// static void each_neu_child(Neu parent, Neu child, lu_p_void p1)
// {
// 	FindWave find_wave = (FindWave) p1;

// 	if (child->p > find_wave->signif) 
// 		// ce prychyna chomu starinnia neu (abo vik neu) vazhlyvyy, 
// 		// my ne hochemo kozhen raz opraciovuvaty dofiha neu
// 		arr_append(((FindWave)p1)->top, child);  
// }

// static void each_neu(lu_p_void item, lu_p_void p1, lu_p_void p2)
// {
// 	Neu neu 				= (Neu) item;
// 	FindWave find_wave 			= (FindWave) p1;
// 	bool* p_move_to_next 	= (bool*) p2;

// 	if (neu_isave_wave_end(neu)) 
// 	{
// 		if (find_wave->apex) s_list_add(find_wave->apex, (lu_p_void) neu);
// 		return;
// 	}

// 	*p_move_to_next = true;

// 	neu_give_p_block_1p(neu, neu_norm_p(neu), find_wave->t, each_neu_child, find_wave);
// }

// Arr find_wave_process(FindWave self)
// {
// 	Arr temp;
// 	bool move_to_next;

// 	do
// 	{
// 		move_to_next = false;

// 		arr_reset(self->top);
// 		arr_each_2p(self->bottom, each_neu, self, &move_to_next);

// 		temp 			= self->top;
// 		self->top 		= self->bottom;
// 		self->bottom 	= temp;

// 	} while (move_to_next);	

// 	return self->bottom;
// }

///////////////////////////////////////////////////////////////////////////////
// Other public methods
