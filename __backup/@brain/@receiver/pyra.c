/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/

#include <stdlib.h>
#include "lib/utils.h"
#include "pyra_layer.h"
#include "pyra.h"

 
///////////////////////////////////////////////////////////////////////////////
// Structs and types

///////////////////////////////////////////////////////////////////////////////
// Prototypes
 
///////////////////////////////////////////////////////////////////////////////
// Create and destroy

Pyra pyra_create(PyraArgs args)
{
	Pyra self = (Pyra) malloc(sizeof(struct pyra));

	struct pyra_layer_args bargs = {
		.width 				= args->width,
		.height 			= args->height, 
		.core 				= args->core,
		.step_norm_dist 	= args->step_norm_dist 
	};

	// Initialize
	self->bottom 	= pyra_layer_create(&bargs);

	if (args->width - 1 < 1 && args->height - 1 < 1)
	{
		self->top = NULL;
	}
	else 
	{
		struct pyra_layer_args targs = {
			.width 				= args->width - 1,
			.height 			= args->height - 1, 
			.core 				= args->core,
			.step_norm_dist 	= args->step_norm_dist 
		};

		self->top = pyra_layer_create(&targs);		
	}

	return self;
}

void pyra_destroy(Pyra* self)
{
	if ((*self)->top)
	{
		pyra_layer_destroy(&(*self)->top);
	}
	pyra_layer_destroy(&(*self)->bottom);

	lu_free((void**) self);
}

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void pyra_cell_init(Pyra self, lu_size x, lu_size y, Neu neu)
{
	//lu_debug("\npyra_cell_init %lu, %lu, NEU == NULL: %d", x, y, neu == NULL);
	pyra_layer_set(self->bottom, x, y, neu);
}

Neu pyra_save(Pyra self)
{
	PyraLayer temp;

	#ifdef LU_DEBUG
	lu_save_debug("\nBEFORE PYRA ITER count: %ld\n", core_neu_count(self->bottom->core));
	#endif
	while (self->top != NULL && !pyra_layer_is_apex_reached(self->bottom))
	{
		pyra_layer_save(self->bottom, self->top);

		#ifdef LU_DEBUG
		lu_debug("\n*** bottom(%lux%lu):\n", self->bottom->width, self->bottom->height);
		pyra_layer_debug(self->bottom);
		lu_debug("\n*** top(%lux%lu):\n", self->top->width, self->top->height);
		pyra_layer_debug(self->top);
		lu_save_debug("\nPYRA ITER END count: %ld\n", core_neu_count(self->bottom->core));
		#endif

		temp = self->top;
		                              
		pyra_layer_size_set(self->bottom, self->top->width - 1, self->top->height - 1);

		self->top 		= self->bottom;
		self->bottom 	= temp;
	}

	Neu apex = pyra_layer_apex(self->bottom);
  
  	neu_flag(apex, NEU_WAVE_END);

	return apex;
}

///////////////////////////////////////////////////////////////////////////////
// Other public methods

