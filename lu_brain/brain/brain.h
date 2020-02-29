/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_SRC_BRAIN_H
#define _LU_SRC_BRAIN_H

#include "basic/basic.h"
#include "lib/lib.h"
#include "system/system.h"

#include "brain/public_to_private.h"

#include "src/n_mem/n_mem.h"



///////////////////////////////////////////////////////////////////////////////
// Save_Opts API


///////////////////////////////////////////////////////////////////////////////
// Find_Opts API



///////////////////////////////////////////////////////////////////////////////
// Restore_Opts API



///////////////////////////////////////////////////////////////////////////////
// Brain API

	struct brain_opts {
		lu_size			id;
		lu_size 		size_in_bytes;			// brain size in bytes including 
												// everything related

		lu_size 		save_waves_size;		// max number of save waves that could 
												// run in parallel
		lu_size			find_waves_size;		
		lu_size			restore_waves_size;

		Arr				rec_opts;				// recs options

		Mem 			mem;
	};


	struct brain {
		lu_size			id;  		// useful for logs and debugging 
									// in multi-brain env

		System			sys;		// global state/devices/memory possibly
									// shared between objects of the brain 

		Arr				recs;		// receivers

		N_Mem 			n_mem;
	};	

///////////////////////////////////////////////////////////////////////////////
// Rec API

	struct rec_opts {
		Brain_Opts  	brain_opts;

		lu_size 		width;
		lu_size 		height;
		lu_value 		min_value;
		lu_value 		max_value;
		lu_size			val_neu_size;
		lu_value		val_ssp;  // val significant similarity percent
	};

	struct rec {
		Brain 			brain;

		lu_size 		width;
		lu_size 		height;
		lu_value 		min_value;
		lu_value 		max_value;
		lu_size			val_neu_size;
		lu_value		val_ssp;  // val significant similarity percent
	};

///////////////////////////////////////////////////////////////////////////////
// Block API
 
 	struct block {
 		Story 			story;
 	};

///////////////////////////////////////////////////////////////////////////////
// Story API

	struct story {
		Brain 			brain;
	};

///////////////////////////////////////////////////////////////////////////////
// Wave API

	struct wave {
		Story 			story;
	};


///////////////////////////////////////////////////////////////////////////////
// Neto API

	struct neuron {
		Brain 			brain;
	};

///////////////////////////////////////////////////////////////////////////////
// Name API
	
	struct name {
		Brain 			brain;
	};
	
///////////////////////////////////////////////////////////////////////////////
// Wave_Resp API

	struct wave_resp {

	};

///////////////////////////////////////////////////////////////////////////////
// Save API

	struct save_opts {

	};


	struct save_resp {

	};

//////////////////////////7/////////////////////////////////////////////////////
// Find_Resp API

	struct find_opts {

	};

	struct find_resp {

	};

///////////////////////////////////////////////////////////////////////////////
// Reception API

	struct reception {

	};

///////////////////////////////////////////////////////////////////////////////
// Restore API

	struct restore_opts {

	};

	struct restore_resp {

	};

#endif // _LU_SRC_BRAIN_H
