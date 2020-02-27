/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "../brain.h"

///////////////////////////////////////////////////////////////////////////////
// Fundamental modules

	#include "basic/src/basic.lu"
	#include "system/src/system.lu"
	#include "lib/src/lib.lu"
 
///////////////////////////////////////////////////////////////////////////////
// Modules related to public nouns (with public and private methods)

	#include "public/public.lu"

///////////////////////////////////////////////////////////////////////////////
//  Private modules
	
	#include "n_mem/src/n_mem.lu"

///////////////////////////////////////////////////////////////////////////////
// Brain API

	Brain brain_create(Brain_Opts opts)
	{
		if (opts == NULL) lu_throw(LU_E_BRAIN_OPTS_REQUIRED);

		System sys 		= system_create(opts->size_in_bytes);
		Brain self 		= (Brain) mem_alloc(sys->mem_perm, sizeof(struct brain));
		
		self->id 		= opts->id;
		self->sys 		= sys;

		self->recs 		= arr_create(sys->mem_perm, opts->rec_opts->count);

		return self;
	}

	void brain_destroy(Brain self)
	{
		system_destroy(self->sys);
	}

	Rec lu_brain_rec_get(Brain self, lu_size index)
	{
		return NULL;
	}