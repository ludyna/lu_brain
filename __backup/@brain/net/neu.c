/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#include "global/lu_types.h"
#include "global/constants.h"

#include "neu.h"
#include "neu_iters.h"
#include "lin.h"

///////////////////////////////////////////////////////////////////////////////
// Init 
	
void neu_init_default(Neu self)
{
	self->p 		= 0.0;
	self->count 	= 0.0;
	self->t 		= 0;
	self->flags		= 0;

	self->l_p 		= NULL;
	self->l_c		= NULL;

	#ifdef LU_DEBUG
	label_gen_set(self->lbl);
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// Other

void print_parent_label(Neu child, Neu item)
{
	lu_debug("%s", item->lbl);
}

void neu_debug(Neu self)
{
	#ifdef LU_DEBUG
	lu_debug(" %s", self->lbl);

	if (self->l_p)
	{
		lu_debug("[");
		neu_each_parent_from_first(self, print_parent_label);
		lu_debug("]");
	}

	#endif
}

