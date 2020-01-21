/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/

#include <stdlib.h>
#include "lib/utils.h"
#include "neto.h"
#include "neto_iters.h"

///////////////////////////////////////////////////////////////////////////////
// Types and structs

///////////////////////////////////////////////////////////////////////////////
// Prototypes
 
///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

Neto neto_create()
{
	Neto self = (Neto) malloc(sizeof(struct neto));

	// Initialize

	return self;
}

void neto_destroy(Neto* self)
{
	lu_free((void**) self);
}

///////////////////////////////////////////////////////////////////////////////
// Main public methods



///////////////////////////////////////////////////////////////////////////////
// Other public methods

static void print_parent_label(Neto child, Neto item)
{
	lu_debug("%s", item->lbl);
}

void neto_debug(Neto self)
{
	#ifdef LU_DEBUG
	lu_debug(" %s", self->lbl);

	if (self->l_p)
	{
		lu_debug("[");
		neto_each_parent_from_first(self, print_parent_label);
		lu_debug("]");
	}

	#endif
}