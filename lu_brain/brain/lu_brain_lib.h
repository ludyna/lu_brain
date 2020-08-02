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
#include "rec/rec.h"
#include "w/w.h"
#include "story/story.h"
#include "s/s.h"

///////////////////////////////////////////////////////////////////////////////
// Nouns



///////////////////////////////////////////////////////////////////////////////
// Brain API

	struct lu_brain_opts {
		lu_size					id;
		lu_size 				size_in_bytes;			// lu_brain size in bytes including 
														// everything related

		////////////////////////////////////
		// Recs
		Arr						rec_opts;				// recs options

		////////////////////////////////////
		// N_Mem
		struct n_mem_opts 		n_mem_opts;
		
	};

	struct lu_brain {
		lu_size					id;  		// useful for logs and debugging 
											// in multi-lu_brain env

		Mem 					app_mem;

		Arr						recs;		// receivers

		S_Mem 					s_mem;
		N_Mem 					n_mem;		
	};	

	static void brain_print_info(Lu_Brain self);


#endif // _LU_SRC_BRAIN_H
