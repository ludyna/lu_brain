/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_PYRA_H
#define _LU_PYRA_H

#include "lib/arr2.h"
#include "@brain/net/neu.h"
#include "@brain/core/core.h"
#include "pyra_layer.h"

///////////////////////////////////////////////////////////////////////////////
// Structs and types

struct pyra_args
{
	lu_size 	width;
	lu_size 	height;
	Core 	core;
	lu_value 	step_norm_dist;
};

typedef struct pyra_args* PyraArgs;

struct pyra {
	lu_time t;
	PyraLayer bottom;
	PyraLayer top;
};

typedef struct pyra* Pyra;

///////////////////////////////////////////////////////////////////////////////
// Create and destroy

Pyra pyra_create(PyraArgs);
void pyra_destroy(Pyra*);

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void pyra_cell_init(Pyra, lu_size, lu_size, Neu);
Neu pyra_save(Pyra);

///////////////////////////////////////////////////////////////////////////////
// Other public methods



#endif // _LU_PYRA_H
