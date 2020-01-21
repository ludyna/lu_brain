/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/

#include <stdlib.h>

#include "lib/utils.h"
#include "@brain/core/core.h"
#include "@brain/core/waves/s_wave.h"
#include "@brain/net/waves/save_wave.h"
#include "@brain/net/linkage.h"
#include "pyra_layer.h"
 
///////////////////////////////////////////////////////////////////////////////
// Structs and types

///////////////////////////////////////////////////////////////////////////////
// Prototypes
 
///////////////////////////////////////////////////////////////////////////////
// Create and destroy

PyraLayer pyra_layer_create(PyraLayerArgs args)
{
	PyraLayer self 	= (PyraLayer) malloc(sizeof(struct pyra_layer));

	// Initialize
	pyra_layer_size_set(self, args->width, args->height); 

	self->core 				= args->core;
	self->step_norm_dist 	= args->step_norm_dist;
	self->items 			= arr2_create(self->width, self->height);

	return self;
}

void pyra_layer_destroy(PyraLayer* self)
{
	arr2_destroy(&(*self)->items);
	lu_free((void**) self);
}

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void pyra_layer_set(PyraLayer self, lu_size x, lu_size y, Neu neu)
{
	arr2_set(self->items, x, y, (lu_p_void) neu);
}

bool pyra_layer_is_apex_reached(PyraLayer self)
{
	return self->width == 1 && self->height == 1;
}

struct block4 {
	lu_size x;
	lu_size y;
	Neu tl;
	Neu tr;
	Neu bl;
	Neu br;
};

static void block4_save(PyraLayer self, struct block4 b, PyraLayer dst)
{
	// struct save_wave w;
	// SaveWave save_wave = &w;

	// save_wave_init(save_wave, core_t_inc(self->core));
	// lu_debug("\nWave t: %lu", save_wave->t);

	// save_wave_process(save_wave, b.tl, 1.0);
	// save_wave_process(save_wave, b.tr, 1.0);
	// save_wave_process(save_wave, b.bl, 1.0);
	// save_wave_process(save_wave, b.br, 1.0);

	// // struct s_wave w;
	// // SWave s_wave = &w;

	// // s_wave_init(s_wave, core_t_inc(self->core)

	// Neu top = save_wave_top(save_wave);

	// if (top)
	// 	lu_debug("\n\nTop %s p: %f norm_p: %f\n\n", top->lbl, top->p, neu_norm_p(top));


	// if (top == NULL)
	// {
	// 	top = core_neu_alloc(self->core);
	// 	link_neu(b.tl, top, self->core);
	// 	link_neu(b.tr, top, self->core);
	// 	link_neu(b.bl, top, self->core); 
	// 	link_neu(b.br, top, self->core);
	// 	pyra_layer_set(dst, b.x, b.y, top);
	// }
	// else if (neu_norm_p(top) > 0.9)
	// {
	// 	pyra_layer_set(dst, b.x, b.y, top);
	// }
	// else
	// {
	// 	top = core_neu_alloc(self->core);
	// 	link_neu(b.tl, top, self->core);
	// 	link_neu(b.tr, top, self->core);
	// 	link_neu(b.bl, top, self->core); 
	// 	link_neu(b.br, top, self->core);
	// 	pyra_layer_set(dst, b.x, b.y, top);
	// } 

	// neu_p_clear(top);
}

static void block4_each
(
	PyraLayer self, 
	void (*block)(PyraLayer, struct block4, PyraLayer), 
	PyraLayer dst
)
{ 
	lu_size x;
	for (lu_size y = 0; y < self->height - 1; y++)
	{
		for (x = 0; x < self->width - 1; x++)
		{
			struct block4 b = {
				.x 	= x,
				.y  = y, 
				.tl = (Neu) arr2_get(self->items, x, y),
				.tr = (Neu) arr2_get(self->items, x + 1, y),
				.bl = (Neu) arr2_get(self->items, x, y + 1),
				.br = (Neu) arr2_get(self->items, x + 1, y + 1)
			};

			lu_assert(b.tl != NULL);
			lu_assert(b.tr != NULL);
			lu_assert(b.bl != NULL);
			lu_assert(b.br != NULL);

			block(self, b, dst);
		}         
	}
}

void pyra_layer_save(PyraLayer bottom, PyraLayer top)
{
	//block4_each(bottom, block4_save, top);
}

Neu pyra_layer_apex(PyraLayer self)
{
	return (Neu) arr2_get(self->items, 0, 0);
} 

void pyra_layer_debug(PyraLayer self)
{ 
	lu_size x;
	for (lu_size y = 0; y < self->height; y++)
	{
		for (x = 0; x < self->width; x++)
		{
			Neu neu = (Neu) arr2_get(self->items, x, y);
			if (neu)
			{
				//neu_debug(neu);
			}
		}

		lu_debug("\n");
	}
}

///////////////////////////////////////////////////////////////////////////////
// Other public methods
