/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "../brain.h"

///////////////////////////////////////////////////////////////////////////////
// Fundamental modules

	#include "basic/basic.lu"
	#include "system/system.lu"
	#include "lib/lib.lu"
 
///////////////////////////////////////////////////////////////////////////////
// Modules related to public nouns (with public and private methods)

	#include "brain_opts.lu"

	#include "net/net.lu"
	#include "recs/recs.lu"
	#include "stories/stories.lu"
	#include "waves/waves.lu" 

///////////////////////////////////////////////////////////////////////////////
//  Private modules
	#include "gate/gate.lu"
	#include "n_mem/n_mem.lu"

///////////////////////////////////////////////////////////////////////////////
// Brain API

	static void brain_for_each_rec_opts_create_rec(void* item, void* p1)
	{
		Rec_Opts rec_opts 	= (Rec_Opts) item;
		Brain brain 		= (Brain) p1;

		Rec rec = rec_create(brain, rec_opts);
		arr_append(brain->recs, rec);
		rec->id = arr_count(brain->recs) - 1;
	}

	Brain brain_create(Brain_Opts opts)
	{
		if (opts == NULL) 
			return lu_user_throw("brain options should not be NULL");

		if (opts->rec_opts == NULL || opts->rec_opts->count < 1) 
			return lu_user_throw("brain options should include information about recs (rec_opts)");

		System sys 		= system_create(opts->size_in_bytes);
		Brain self 		= (Brain) mem_alloc(sys->mem_perm, sizeof(struct brain));
		
		self->id 		= opts->id;
		self->sys 		= sys;

		// Recs
		self->recs 		= arr_create(sys->mem_perm, opts->rec_opts->count);

		arr_each_1p(opts->rec_opts, brain_for_each_rec_opts_create_rec, self);

		// Gate 
		self->gate 		= gate_create(sys->mem_perm, &opts->gate_opts);

		return self;
	}

	void brain_destroy(Brain self)
	{
		system_destroy(self->sys);
	}

	Rec lu_brain_rec_get(Brain self, lu_size index)
	{
		if (index >= arr_count(self->recs)) 
			return lu_user_throw("index is out of range");

		return arr_get(self->recs, index);
	}