/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
	Value Layer
*/
#ifndef _LU_VALUE_LAYER_H
#define _LU_VALUE_LAYER_H

#include "global/lu_types.h"
#include "lib/arr.h"

#include "@brain/net/layer.h"
#include "@brain/core/core.h"
#include "@brain/net/waves/find_wave.h"

/*
	Val layer is optimized for CPU in a hash-like way but it is easy to build it 
	as a pure NN for NN hardware implementations.
*/
struct val_layer {
	struct layer super;

	Core core; // TODO: delete

	lu_value 		orig_min_val, orig_max_val;
	lu_value 		max_val;
	lu_value 		val_step;

	lu_size 		val_neu_size;
	Neu*			val_neus;
	lu_value*		val_steps; 
	lu_size 		ssp_i; // significant similarity percent
};

typedef struct val_layer* ValLayer;

///////////////////////////////////////////////////////////////////////////////
// Create and destroy

ValLayer val_layer_create(Core core, lu_value min_val, lu_value max_val, lu_size val_neu_size, lu_value val_ssp);
void val_layer_destroy(ValLayer*);

///////////////////////////////////////////////////////////////////////////////
// Main public methods

Neu val_layer_save(ValLayer self, lu_value input_val, lu_time);
//void val_layer_find(ValLayer self, lu_value input_val, FindWave);

///////////////////////////////////////////////////////////////////////////////
// Other public methods

lu_value val_layer_norm(ValLayer self, lu_value request); 
struct lu_size_range val_layer_indx_range(ValLayer self, lu_value val);
lu_value val_layer_calc_potent(ValLayer self, lu_size val_step_i, lu_value val);
lu_value val_layer_step_norm_dist(ValLayer self);

#endif // _LU_VALUE_LAYER_H

