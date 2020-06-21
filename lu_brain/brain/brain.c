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
 
 	#include "n/n.lu"
	#include "net/net.lu"
	#include "rec/rec.lu"
	#include "story/story.lu"
	#include "w/w.lu" 

///////////////////////////////////////////////////////////////////////////////
//  Private modules
	#include "gate/gate.lu"
	#include "s/s.lu"

///////////////////////////////////////////////////////////////////////////////
// Brain API

	static void brain_for_each_rec_opts_create_rec(void* item, void* p1)
	{
		Lu_Rec_Opts rec_opts 	= (Lu_Rec_Opts) item;
		Lu_Brain brain 		= (Lu_Brain) p1;

		Lu_Rec rec = rec_create(brain, rec_opts);

		lu_user_assert_void(rec, "Cannot create Lu_Rec");

		arr_append(brain->recs, rec);

		lu_user_assert_void(arr_count(brain->recs) > 0, "Cannot append Lu_Rec");

		rec->id = arr_count(brain->recs) - 1;
	}

	Lu_Brain lu_brain_create(Lu_Brain_Opts opts)
	{
		if (opts == NULL) 
			return lu_user_debug("lu_brain options should not be NULL");

		if (opts->rec_opts == NULL || opts->rec_opts->count < 1) 
			return lu_user_debug("lu_brain options should include information about recs (rec_opts)");

		Mem mem_perm		= (Mem) mem_perm_create(g_mem_temp, opts->size_in_bytes);

		Lu_Brain self 		= (Lu_Brain) mem_alloc(mem_perm, sizeof(struct lu_brain));
		
		self->id 		= opts->id;
		self->mem_perm  = mem_perm;

		// Recs
		self->recs 		= arr_create(mem_perm, opts->rec_opts->count);

		lu_user_assert(self->recs, "Cannot create recs. Not enough memory?");

		arr_each_1p(opts->rec_opts, brain_for_each_rec_opts_create_rec, self);

		lu_user_assert(arr_count(self->recs) > 0, "Lu_Brain recs count is 0");

		// S_Mem
		self->s_mem 	= s_mem_create(self);
		lu_user_assert(self->s_mem, "Cannot create S_Mem");

		self->n_mem 	= n_mem_create(self);
		lu_user_assert(self->n_mem, "Cannot create N_Mem");

		// Gate 
		self->gate 		= gate_create(self, &opts->gate_opts);
		lu_user_assert(self->gate, "Cannot create Gate");

		return self;
	}

	void lu_brain_destroy(Lu_Brain self)
	{
		mem_destroy(self->mem_perm, g_mem_temp);
	}

	Lu_Rec lu_brain_rec_get(Lu_Brain self, lu_size index)
	{
		lu_user_assert(index < arr_count(self->recs), "index is out of range");

		return arr_get(self->recs, index);
	}