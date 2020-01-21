/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_PYRA_LAYER_H
#define _LU_PYRA_LAYER_H

#include "lib/arr2.h"
#include "@brain/net/neu.h"
#include "@brain/core/core.h"

///////////////////////////////////////////////////////////////////////////////
// Structs and types

struct pyra_layer_args
{
	lu_size 	width;
	lu_size 	height;
	Core 	core;
	lu_value 	step_norm_dist;
};

typedef struct pyra_layer_args* PyraLayerArgs;

struct pyra_layer { 
	lu_size 	width;
	lu_size 	height;
	Core 	core;
	lu_value 	step_norm_dist;
	
	Arr2 items; 
};

typedef struct pyra_layer* PyraLayer;

///////////////////////////////////////////////////////////////////////////////
// Create and destroy

PyraLayer pyra_layer_create(PyraLayerArgs);
void pyra_layer_destroy(PyraLayer*);

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void pyra_layer_set(PyraLayer, lu_size, lu_size, Neu);
bool pyra_layer_is_apex_reached(PyraLayer);
void pyra_layer_save(PyraLayer, PyraLayer);
Neu pyra_layer_apex(PyraLayer);

static inline void pyra_layer_size_set(PyraLayer self, lu_size w, lu_size h)
{
	self->width = w;
	self->height = h;

	if (self->width < 1) self->width = 1;
	if (self->height < 1) self->height = 1;
}

///////////////////////////////////////////////////////////////////////////////
// Other public methods

void pyra_layer_debug(PyraLayer self);

#endif // _LU_PYRA_LAYER_H
