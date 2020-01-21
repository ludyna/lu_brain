/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/
#ifndef _LU_LAYER_H
#define _LU_LAYER_H

#include "global/lu_types.h"
#include "neto.h"

///////////////////////////////////////////////////////////////////////////////
// Types and structs

	typedef struct layer* Layer;
 
 	// Layer chy component? Bo brain i receiver mayut ti sami methods
	struct layer {
		
		Neto (*save)(Layer, lu_p_void input, lu_time t);
		Neto (*find)(Layer, lu_p_void input, lu_time t);
		lu_p_void (*restore)(Layer, Neto, lu_time t);

	};

///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

	static inline Layer layer_init(Layer self)
	{
		// ...
		return self;
	}

	Layer layer_create();
	void layer_destroy(Layer*);

///////////////////////////////////////////////////////////////////////////////
// Getters / Setters

///////////////////////////////////////////////////////////////////////////////
// Main public methods

	/*
	**	Raises exception if invalid.
	*/
	void layer_validate(Layer);

///////////////////////////////////////////////////////////////////////////////
// Other public methods



#endif // _LU_LAYER_H
