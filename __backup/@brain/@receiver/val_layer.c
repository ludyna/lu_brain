/**
	Copyright © 2019 Oleh Ihorovych Novosad
	Value Layer
*/

#include <stdlib.h>

#include "@brain/@receiver/val_layer.h"
#include "@brain/net/neu_iters.h"

///////////////////////////////////////////////////////////////////////////////
// Create and destroy

ValLayer val_layer_create
(	
	Core core, 
	lu_value min_val, lu_value max_val, 
	lu_size val_neu_size, lu_value val_ssp
)
{
	lu_assert(max_val - min_val > 0);
	lu_assert(val_ssp > 0 && val_ssp <= 0.5);

	ValLayer self = (ValLayer) malloc(sizeof(struct val_layer));
	lu_assert(self != NULL);

	// Initialize
	self->core			= core;
	self->orig_min_val 	= min_val;
	self->orig_max_val 	= max_val;
	self->val_neu_size 	= val_neu_size;
	self->max_val 		= self->orig_max_val - self->orig_min_val;
	self->val_step 		= self->max_val / (lu_value) self->val_neu_size;
	self->ssp_i 		= (lu_size) lu_value_round(self->max_val * val_ssp / self->val_step); // ssp in indexes
 
 	// Val neus 
	self->val_neus = (Neu*) calloc(self->val_neu_size, sizeof(Neu));
	lu_assert(self->val_neus != NULL);
 
 	// Steps precalculated 
	self->val_steps = (lu_value*) malloc(sizeof(lu_value) * self->val_neu_size);
	lu_assert(self->val_steps != NULL);
	for (int i = 0; i < self->val_neu_size; i++) 
	{
		self->val_steps[i] = (lu_value)i * self->val_step;
	}

	return self;
}

void val_layer_destroy(ValLayer* self)
{
	lu_free((void **) &(*self)->val_neus); 
	lu_free((void **) &(*self)->val_steps);  
	lu_free((void **) self);
}

///////////////////////////////////////////////////////////////////////////////
// Public methods

lu_value val_layer_norm(ValLayer self, lu_value request)
{
	lu_value val = request - self->orig_min_val;
	if (val < 0) val = 0;
	if (val > self->max_val) val = self->max_val;

	return val;
}

static lu_size val_layer_indx(ValLayer self, lu_value val)
{
	return (lu_size) lu_value_round(val / self->val_step);
}

struct lu_size_range val_layer_indx_range(ValLayer self, lu_value val)
{
	lu_size orig_i = val_layer_indx(self, val);

	long begin, end;

	begin = orig_i - self->ssp_i;
	if (begin < 0) begin = 0;

	end = orig_i + self->ssp_i;
	if (end > (self->val_neu_size - 1)) end = self->val_neu_size - 1; 

	struct lu_size_range r;
	r.begin = (lu_size) begin;
	r.end = (lu_size) end;
	return r;
}

lu_value val_layer_calc_potent(ValLayer self, lu_size val_step_i, lu_value val) 
{ 
	return 1.0 - lu_value_abs(self->val_steps[val_step_i] - val) / self->max_val;
}

lu_value val_layer_step_norm_dist(ValLayer self)
{
	return 1.0 / self->val_neu_size;
}

static Neu get_val_neu(ValLayer self, lu_size indx)
{
	Neu neu = self->val_neus[indx];
	if (!neu)
	{
		neu = core_neu_alloc(self->core);
		lu_assert(neu != NULL);
		
		neu_inc_count(neu);

		self->val_neus[indx] = neu;
	}

	return neu;
}

Neu val_layer_save(ValLayer self, lu_value input_val, lu_time t)
{
	lu_value val 	= val_layer_norm(self, input_val);
	lu_size indx 	= val_layer_indx(self, val);

	return get_val_neu(self, indx);
}


// static void each_val_neu_find(Neu parent, Neu child, lu_p_void find_wave)
// { 
// 	// pochatk layer ce dity val neu 
// 	find_wave_bottom_append((FindWave)find_wave, child);
// }

// void val_layer_find(ValLayer self, lu_value input_val, FindWave find_wave)
// { 
// 	lu_value val 			= val_layer_norm(self, input_val);
// 	struct lu_size_range r 	= val_layer_indx_range(self, val);

// 	Neu neu;
// 	for (lu_size v = r.begin; v <= r.end; v++)
// 	{
// 		lu_value p 	= val_layer_calc_potent(self, v, val);
// 		neu 		= get_val_neu(self, v); 
 
//  		neu_give_p_block_1p(neu, p, find_wave->t, each_val_neu_find, find_wave);
// 	}	
// }

