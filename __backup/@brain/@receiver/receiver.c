/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lib/utils.h"

#include "receiver.h"
#include "pyra.h"

///////////////////////////////////////////////////////////////////////////////
// Create and destroy

	Receiver receiver_create(
		Core 		core, 
		lu_size 	width, 
		lu_size 	height, 
		lu_value 	min_val, 
		lu_value 	max_val, 
		lu_size 	val_neu_size, 
		lu_value 	val_ssp
	)
	{ 
		lu_assert(width > 0);
		lu_assert(height > 0);

		Receiver self = (Receiver) malloc(sizeof(struct receiver));
		lu_assert(self != NULL);

		// Initialize
		self->core			= core;
		self->width			= width;
		self->height		= height;
		self->input_size  	= width * height;

		// Request buff 
		self->input = (lu_value*) malloc(sizeof(lu_value) * self->input_size);
		lu_assert(self->input != NULL);

		// Value layer
		self->val_layer = val_layer_create(self->core, min_val, max_val, val_neu_size, val_ssp);

		return self; 
	}

	void receiver_destroy(Receiver *self)
	{  
		val_layer_destroy(&(*self)->val_layer);
		lu_free((void **) &((*self)->input));
		lu_free((void **) self);
	}

///////////////////////////////////////////////////////////////////////////////
// Main public methods

	void receiver_validate(Receiver self)
	{

	}

	Neto receiver_save(Receiver self, lu_value* data)
	{
		return NULL;
	}

// static void data_each
// (
// 	Receiver self, 
// 	const lu_value* data, 
// 	void (*block)(Receiver self, lu_size x, lu_size y, lu_value val, lu_p_void p1), 
// 	lu_p_void p1
// )
// { 
// 	lu_size h = 0;
// 	lu_size x;
// 	for (lu_size y = 0; y < self->height; y++)
// 	{
// 		for (x = 0; x < self->width; x++)
// 		{
// 			block(self, x, y, data[h], p1);
// 			h++;
// 		}
// 	}
// }

// static void receiver_pyra_init(Receiver self, lu_size x, lu_size y, lu_value val, lu_p_void p1)
// {
// 	Pyra py = (Pyra) p1;
// 	Neu neu = val_layer_save(self->val_layer, val, py->t);
	
// 	lu_assert(neu != NULL);

// 	pyra_cell_init(py, x, y, neu);
// }

// Neu receiver_save(Receiver self, LuSRequestItem request)
// { 
// 	receiver_validate(self);
// 	s_request_item_validate(request);

// 	struct pyra_args pargs = 
// 	{
// 		.width 			= self->width,
// 		.height 		= self->height,
// 		.core 			= self->core,
// 		.step_norm_dist = val_layer_step_norm_dist(self->val_layer)
// 	};

// 	Pyra py = pyra_create(&pargs);
// 	data_each(self, request->data, receiver_pyra_init, (void*) py);

// 	Neu neu = pyra_save(py);
// 	pyra_destroy(&py);

// 	return neu;
// }

// static void receiver_find_wave_init(Receiver self, lu_size x, lu_size y, lu_value val, lu_p_void p1)
// {
// 	FindWave find_wave = (FindWave) p1;
// 	val_layer_find(self->val_layer, val, find_wave);
// }

// void receiver_find(Receiver self, FRequestItem request, FindWave find_wave)
// {
// 	receiver_validate(self);
// 	f_request_item_validate(request);

// 	data_each(self, request->data, receiver_find_wave_init, (void*) find_wave);

// 	find_wave_process(find_wave);
// }


