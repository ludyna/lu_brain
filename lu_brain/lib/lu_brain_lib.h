/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_SRC_BRAIN_H
#define _LU_SRC_BRAIN_H

// Public interface

#include "../lu_brain.h" 

// Vendor

#include "vendor/CException.h"

// Basics

#include "basic/basic.h"
#include "lib/lib.h"

// App

#include "typedefs.h"
#include "data/data.h"
#include "n/n.h"
#include "lu_rec/lu_rec.h"
#include "w/w.h"
#include "lu_story/lu_story.h"
#include "s/s.h"


///////////////////////////////////////////////////////////////////////////////
// Lu_Brain_Config
	
	struct lu_brain_config {
		lu_size 		size_in_bytes;		// brain size in bytes (not includes recs, stories or waves)
											// optimal size depends on number of recs, rec sizes, 
											// story sizes and amount of data to remember

		lu_size 		recs_size;			// initial maximum number of recs 

		lu_size 		names_size; 		// initial maximum number of names

		lu_size 		id;					// optional, to identify brain by unique id
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain_Config predefined 

	enum lu_bc_predefined_type {
		LU_BC_DEFAULT = 0,
		LU_BC_END 				
	};

	extern struct lu_brain_config lu_g_bc_predefined[LU_BC_END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	struct lu_brain {
		Mem 					brain_mem;

		struct lu_brain_config 	config;

		Arr						recs;		// receivers

		S_Mem 					s_mem;
		N_Mem 					n_mem;		
	};	



#endif // _LU_SRC_BRAIN_H
