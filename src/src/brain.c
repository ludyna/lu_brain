/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "brain.h"

///////////////////////////////////////////////////////////////////////////////
// Fundamental modules

	#include "basic/src/basic.lu"
	#include "lib/src/lib.lu"
 
///////////////////////////////////////////////////////////////////////////////
// Modules related to public nouns (with public and private methods)

	// Options 
	#include "brain_opts.lu"
	#include "rec_opts.lu"
	#include "save_opts.lu"
	#include "find_opts.lu"
	#include "restore_opts.lu"
	
	// Responses
	#include "wave_resp.lu"
	#include "save_resp.lu"
	#include "find_resp.lu"
	#include "restore_resp.lu"

	// Main nouns
	#include "rec.lu"
	#include "block.lu"
	#include "story.lu"
	#include "wave.lu"
	#include "neto.lu"
	#include "name.lu"
	#include "reception.lu"

///////////////////////////////////////////////////////////////////////////////
//  Private modules
	
	#include "n_mem/src/n_mem.lu"

///////////////////////////////////////////////////////////////////////////////
// Brain API

	Brain brain_create(Brain_Opts opts)
	{
		Ph_Mem ph_mem 	= ph_mem_create(opts);

		//Brain self 		= (Brain) ph_mem_alloc(ph_mem, PH_BRAIN);

		// Initialize
		// self->ph_mem 	= ph_mem;
		// self->n_mem		= n_mem_create(self);

		//return self;

		return NULL;
	}

	void brain_destroy(Brain* self)
	{
		ph_mem_destroy(&(*self)->ph_mem);
		*self = NULL;
	}

	Rec lu_brain_rec_get(Brain self, lu_size index)
	{
		return NULL;
	}