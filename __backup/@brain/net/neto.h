/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/
#ifndef _LU_NETO_H
#define _LU_NETO_H

#include "global/lu_types.h"
#include "@brain/core/waves/wave.h"
#include "layer.h"

///////////////////////////////////////////////////////////////////////////////
// Types and structs
typedef struct neto* Neto;

struct neto {
	// my mozhemo lookup wave by t
	lu_time 			t; 
	
	// yak consume pracuye zakladeno v implementaciyi neto
	// save ZAVZHDY specyfichnyy do layer, takyh yak val_layer chy space_layer
 	// todi yak find - mozhe opraciovuvatys cherez processor
 	// tobto ne budemo namahatysia process save cherez processor
	void 	(*consume)(Neto self, Neto src, lu_value p);
	void	(*bconsume)(Neto self, Neto src, lu_value p);
	void	(*debug)(Neto self);

	#ifdef LU_DEBUG
	char 				lbl[20];
	#endif 
};



///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

static inline void neto_consume(Neto src, Neto dst, lu_value p)
{
	lu_debug("\nneto_consume() call");
}

static inline void neto_excite(Neto neu)
{
	lu_debug("\nneto_excite() call");
}


static inline Neto neto_init(Neto self)
{
	// self->t 		= 0;

	// self->l_p 		= NULL;
	// self->l_c		= NULL;
	// self->wave 		= NULL;

	// // self->consume 	= neto_consume;

	// #ifdef LU_DEBUG
	// label_gen_set(self->lbl);
	// #endif

	return self;
}

Neto neto_create();
void neto_destroy(Neto*);

///////////////////////////////////////////////////////////////////////////////
// Getters / Setters

///////////////////////////////////////////////////////////////////////////////
// Main public methods

/*
**	Raises exception or returns false if invalid.
*/
bool neto_validate(Neto);

///////////////////////////////////////////////////////////////////////////////
// Other public methods

void neto_debug(Neto self);

#endif // _LU_NETO_H
