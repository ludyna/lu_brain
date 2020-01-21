/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_REVEIVER_H
#define _LU_REVEIVER_H

#include "global/lu_types.h"

#include "@brain/net/neto.h"
#include "@brain/net/waves/find_wave.h"
#include "@brain/core/core.h"
#include "@brain/@storage/storage.h"

#include "val_layer.h"



struct receiver {  
	Core core;

	// Dimensions 
	lu_size 	height;
	lu_size 	width;

	// Request buff 
	lu_size 	input_size;
	lu_value*	input;  

	ValLayer 	val_layer;

	lu_size 	neu_count;
	lu_size 	layer_count;
	lu_size* 	layer_neu_count;
	lu_size		max_layer_neu_count;
};

typedef struct receiver *Receiver;

///////////////////////////////////////////////////////////////////////////////
// Create and destroy

Receiver receiver_create(Core core, lu_size width, lu_size height, lu_value min_val, 
					lu_value max_val, lu_size val_neu_size, lu_value val_ssp);

void receiver_destroy(Receiver*);

///////////////////////////////////////////////////////////////////////////////
// Public methods

void receiver_validate(Receiver);

Neto receiver_save(Receiver, lu_value* data);

// Neu receiver_save(Receiver, LuSRequestItem);
// void receiver_find(Receiver, FRequestItem, FindWave);

#endif // _LU_REVEIVER_H
