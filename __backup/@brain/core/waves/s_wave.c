/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/

#include <stdlib.h>
#include "lib/utils.h"
#include "s_wave.h"
 
///////////////////////////////////////////////////////////////////////////////
// Types and structs

///////////////////////////////////////////////////////////////////////////////
// Prototypes
 
///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

static void s_wave_excite(Wave _self, Neu neu)
{  
	SWave self = (SWave) _self;

	if (self->top == NULL || neu_norm_p(neu) > neu_norm_p(self->top))
		self->top = neu;
}

SWave s_wave_init(SWave self, lu_time t, lu_value signif)
{
	wave_init((Wave) self, t, signif);

	self->super.excite = s_wave_excite;

	return self;
}

SWave s_wave_create()
{
	SWave self = (SWave) malloc(sizeof(struct s_wave));

	// Initialize

	return self;
}

void s_wave_destroy(SWave* self)
{
	lu_free((void**) self);
}

///////////////////////////////////////////////////////////////////////////////
// Main public methods



///////////////////////////////////////////////////////////////////////////////
// Other public methods
