/**
	Copyright © 2019 Oleh Ihorovych Novosad
	Ludyna Brain
*/
#ifndef _LU_BRAIN_H
#define _LU_BRAIN_H
 
#include "global/lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// Default args 

	#ifndef LU_SYNAPSE_BUFF_SIZE
	#define LU_SYNAPSE_BUFF_SIZE 1000
	#endif

	#ifndef LU_NEURON_BUFF_SIZE
	#define LU_NEURON_BUFF_SIZE 1000
	#endif

	#ifndef LU_RECEIVERS_SIZE
	#define LU_RECEIVERS_SIZE 10
	#endif

	#ifndef LU_WAVE_BUFF_SIZE
	#define LU_WAVE_BUFF_SIZE 10
	#endif

	#ifndef LU_PROCESSOR_BUFF_SIZE
	#define LU_PROCESSOR_BUFF_SIZE 2000
	#endif

///////////////////////////////////////////////////////////////////////////////
// Main types and structs

	struct lu_brain_args
	{
		lu_size 	neuron_buff_size;
		lu_size 	synapse_buff_size;
		lu_size 	receivers_size;
		lu_size 	wave_buff_size;
		lu_size 	processor_buff_size;
	};  

	extern struct lu_brain_args LU_DEFAULT_BRAIN_ARGS;

	typedef struct lu_brain*	LuBrain; 
	typedef struct lu_neto* 	LuNeto;

///////////////////////////////////////////////////////////////////////////////
// Response



///////////////////////////////////////////////////////////////////////////////
// Create and destroy

	/**
		Create brain.
	*/
	LuBrain lu_brain_create(struct lu_brain_args*);

	/**
		Free brain.
	*/
	void lu_brain_destroy(LuBrain*);

///////////////////////////////////////////////////////////////////////////////
// Getters / Setters

	lu_size lu_brain_neu_count(LuBrain);
	lu_time lu_brain_t_reserve(LuBrain);

///////////////////////////////////////////////////////////////////////////////
// Create receivers

	/**
		
	*/
	lu_size lu_brain_create_receiver(
		LuBrain, 
		lu_size width, lu_size height, 
		lu_value min_val, lu_value max_val, 
		lu_size val_neu_size, lu_value val_ssp
	);

	// struct lu_s_response lu_brain_save(LuBrain, LuSRequest);
	// LuFResponse lu_brain_find(LuBrain, LuFRequest);

	// LuSRequest lu_brain_restore(LuBrain, Neu);
	// Neu lu_brain_associate(LuBrain, Neu, lu_size label);

 
///////////////////////////////////////////////////////////////////////////////
// Save 



	/*
		Yaksho treba shob dva receiver otrymaly v toy samyy chas, my brain.reserve_t() i otrymanyy t
		peredayemo v lu_save_args v obydva (abo bilshe) lu_brain_save() calls.
	*/
	LuSaveRes lu_brain_save(LuBrain, lu_size receiver_id, lu_value* data, struct lu_save_args*);


///////////////////////////////////////////////////////////////////////////////
// Find 

	#define LU_FIND_LIMIT_SIZE 5

	struct lu_find_args {
		lu_size limit;
	};

	typedef struct lu_find_res* LuFindRes;

	struct lu_find_res {
		struct lu_response super;

		//SList list;		// list of top results (default limit is up to LU_FIND_LIMIT_SIZE)
	};

	LuFindRes lu_brain_find(LuBrain, lu_size receiver_id, lu_value* data, struct lu_find_args*);

///////////////////////////////////////////////////////////////////////////////
// Restore

	struct lu_restore_args {

	};

	typedef struct lu_restore_res* LuRestoreRes;

	struct lu_restore_res {
	struct lu_response super;

	};

	LuRestoreRes lu_brain_restore(LuBrain, LuNeto, struct lu_restore_args*);

///////////////////////////////////////////////////////////////////////////////
// Associate

	LuNeto lu_brain_associate(LuBrain, LuNeto, lu_size label);

#endif // _LU_BRAIN_H
