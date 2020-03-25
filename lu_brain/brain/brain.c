/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "../brain.h"

///////////////////////////////////////////////////////////////////////////////
// Fundamental modules

	#include "basic/basic.lu"
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

		lu_user_assert_void(rec, "Cannot create rec!. Not enough memory?");

		arr_append(brain->recs, rec);

		lu_user_assert_void(arr_count(brain->recs) > 0, "Cannot append rec. Something went wrong.");

		rec->id = arr_count(brain->recs) - 1;
	}

	Brain lu_brain_create(Brain_Opts opts)
	{
		if (opts == NULL) 
			return lu_user_throw("brain options should not be NULL");

		if (opts->rec_opts == NULL || opts->rec_opts->count < 1) 
			return lu_user_throw("brain options should include information about recs (rec_opts)");

		Mem mem_perm		= (Mem) mem_perm_create(g_mem_temp, opts->size_in_bytes);

		Brain self 		= (Brain) mem_alloc(mem_perm, sizeof(struct brain));
		
		self->id 		= opts->id;
		self->mem_perm  = mem_perm;

		// Recs
		self->recs 		= arr_create(mem_perm, opts->rec_opts->count);

		lu_user_assert(self->recs, "Cannot create recs. Not enough memory?");

		arr_each_1p(opts->rec_opts, brain_for_each_rec_opts_create_rec, self);

		lu_user_assert(arr_count(self->recs) > 0, "Brain recs count is 0");

		// Gate 
		self->gate 		= gate_create(self, &opts->gate_opts);

		return self;
	}

	void lu_brain_destroy(Brain self)
	{
		mem_destroy(self->mem_perm, g_mem_temp);
	}

	Rec lu_brain_rec_get(Brain self, lu_size index)
	{
		lu_user_assert(index < arr_count(self->recs), "index is out of range");

		return arr_get(self->recs, index);
	}