/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

	#include "../brain.h"

///////////////////////////////////////////////////////////////////////////////
// Fundamental modules

	#include "basic/basic.lu"
	#include "lib/lib.lu"
 
///////////////////////////////////////////////////////////////////////////////
// 
	#include "brain_opts.lu"
 
 	#include "n/n.lu"
	#include "rec/rec.lu"
	#include "story/story.lu"
	#include "w/w.lu" 
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

		Mem app_mem			= (Mem) mem_perm_create(g_mem_temp, opts->size_in_bytes); 
		lu_user_assert(app_mem, "Cannot create app_mem. Not enough memory?");

		Lu_Brain self 		= (Lu_Brain) mem_alloc(app_mem, sizeof(struct lu_brain));
		lu_user_assert(self, "Cannot allocate Lu_Brain. Not enough memory?");
		
		self->id 			= opts->id;
		self->app_mem  		= app_mem; 

		// Recs
		self->recs 			= arr_create(app_mem, opts->rec_opts->count);

		lu_user_assert(self->recs, "Cannot create recs. Not enough memory?");

		arr_each_1p(opts->rec_opts, brain_for_each_rec_opts_create_rec, self);

		lu_user_assert(arr_count(self->recs) > 0, "Lu_Brain recs count is 0");

		self->s_mem 		= s_mem_create(self);
		lu_user_assert(self->s_mem, "Cannot create S_Mem. Not enough memory?");

		self->n_mem 		= n_mem_create(self, &opts->n_mem_opts);
		lu_user_assert(self->n_mem, "Cannot create N_Mem. Not enough memory?");

		n_mem_tables_alloc(self->n_mem, app_mem);

		brain_print_info(self);

		return self;
	}

	void lu_brain_destroy(Lu_Brain self)
	{
		mem_destroy(self->app_mem, g_mem_temp);
	}

	Lu_Rec lu_brain_rec_get(Lu_Brain self, lu_size index)
	{
		lu_user_assert(index < arr_count(self->recs), "index is out of range");

		return arr_get(self->recs, index);
	}

	static void brain_print_info(Lu_Brain self)
	{
		lu_user_assert_void(self, "Lu_Brain is NULL");
		lu_user_assert_void(self->app_mem, "Mem is NULL");
		Mem_Perm app_mem = (Mem_Perm) self->app_mem;

		lu_debug("\n---------> Brain #%lu Info <---------", self->id);
		lu_debug("\nMemory allocated (bytes): %lu", mem_perm_allocated(app_mem));
		lu_debug("\nMemory used (bytes): %lu", mem_perm_used(app_mem));

 		n_mem_print_info(self->n_mem);

		lu_debug("\n-----------------------------------\n");
	}