/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

	#include "lu_brain_lib.h"

	// Vendor

	#include "vendor/CException.c"

	// Basics

	#include "basic/basic.lu"
	#include "lib/lib.lu"
 
	// App

	#include "lu_brain_config.lu" 
 	#include "n/n.lu"
	#include "lu_rec/lu_rec.lu"
	#include "lu_story/lu_story.lu"
	#include "w/w.lu" 
	#include "s/s.lu"

///////////////////////////////////////////////////////////////////////////////
// Brain API

	Lu_Brain lu_brain_create_from_predefined(lu_size size_in_bytes, lu_size predefined_config_id)
	{
		Lu_Brain_Config config = lu_brain_config_predefined_get(predefined_config_id);
		lu_user_assert(config, "Cannot get Lu_Brain_Config");

		config->size_in_bytes = size_in_bytes;

		return lu_brain_create(*config);
	}

	static void lu_brain_for_each_rec_opts_create_rec(void* item, void* p1)
	{
		Lu_Rec_Opts rec_opts 	= (Lu_Rec_Opts) item;
		Lu_Brain brain 		= (Lu_Brain) p1;

		Lu_Rec rec = rec_create(brain, rec_opts);

		lu_user_assert_void(rec, "Cannot create Lu_Rec");

		arr_append(brain->recs, rec);

		lu_user_assert_void(arr_count(brain->recs) > 0, "Cannot append Lu_Rec");

		rec->id = arr_count(brain->recs) - 1;
	}

	Lu_Brain lu_brain_create(struct lu_brain_config config)
	{
		if (config == NULL) 
			return lu_user_debug("lu_brain options should not be NULL");

		if (config->rec_opts == NULL || config->rec_opts->count < 1) 
			return lu_user_debug("lu_brain options should include information about recs (rec_opts)");

		Mem brain_mem			= (Mem) mem_perm_create(g_mem_temp, config->size_in_bytes); 
		lu_user_assert(brain_mem, "Cannot create brain_mem. Not enough memory?");

		Lu_Brain self 		= (Lu_Brain) mem_alloc(brain_mem, sizeof(struct lu_brain));
		lu_user_assert(self, "Cannot allocate Lu_Brain. Not enough memory?");
		
		self->id 			= config->id;
		self->brain_mem  	= brain_mem; 

		// Recs
		self->recs 			= arr_create(brain_mem, config->rec_opts->count);

		lu_user_assert(self->recs, "Cannot create recs. Not enough memory?");

		arr_each_1p(config->rec_opts, lu_brain_for_each_rec_opts_create_rec, self);

		lu_user_assert(arr_count(self->recs) > 0, "Lu_Brain recs count is 0");

		self->s_mem 		= s_mem_create(self);
		lu_user_assert(self->s_mem, "Cannot create S_Mem. Not enough memory?");

		self->n_mem 		= n_mem_create(self, &config->n_mem_opts);
		lu_user_assert(self->n_mem, "Cannot create N_Mem. Not enough memory?");

		n_mem_tables_create(self->n_mem, brain_mem);

		lu_brain_print_info(self);

		return self;
	}

	void lu_brain_destroy(Lu_Brain self)
	{
		mem_destroy(self->brain_mem, g_mem_temp);
	}

	void lu_brain_print_info(Lu_Brain self)
	{
		lu_user_assert_void(self, "Lu_Brain is NULL");
		lu_user_assert_void(self->brain_mem, "Mem is NULL");
		Mem_Perm brain_mem = (Mem_Perm) self->brain_mem;

		lu_debug("\n\n---------> Brain #%lu Info <---------", self->id);
		lu_debug("\nMemory allocated (bytes): %lu", mem_perm_allocated(brain_mem));
		lu_debug("\nMemory used (bytes): %lu", mem_perm_used(brain_mem));

 		n_mem_print_info(self->n_mem);

 		s_mem_print_info(self->s_mem);

		lu_debug("\n-----------------------------------\n");
	}