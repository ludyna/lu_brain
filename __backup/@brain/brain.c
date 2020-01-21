/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#include <stdio.h>
#include <stdlib.h>

#include "lib/utils.h"
#include "lib/arr.h"
#include "lib/lists/list.h"
#include "core/core.h"
#include "net/linkage.h"
#include "net/waves/find_wave.h"

#include "@receiver/receiver.h"
#include "@sequence/sequence.h"
#include "brain.h"

 
///////////////////////////////////////////////////////////////////////////////
// Structs and types

	struct lu_brain {

		// Internal timer
		lu_time t;

		Core core;

		// Components
		Arr 		receivers;
		Sequence 	sequence;

		// Responses
		List resps;
	};

	struct lu_brain_args LU_DEFAULT_BRAIN_ARGS = {
		.neuron_buff_size 		= LU_NEURON_BUFF_SIZE, 
		.synapse_buff_size 		= LU_SYNAPSE_BUFF_SIZE,
		.receivers_size 		= LU_RECEIVERS_SIZE,
		.wave_buff_size			= LU_WAVE_BUFF_SIZE, 
		.processor_buff_size 	= LU_PROCESSOR_BUFF_SIZE
	};

///////////////////////////////////////////////////////////////////////////////
// Responses

	enum lu_status brain_exception_to_status(lu_exception e)
	{
		switch (e)
		{
			case LU_E_ALLOC_FAILED:
				return LU_S_OUT_OF_MEM;
			default:
				return LU_S_INTERNAL_ERROR;
		}

		return LU_S_INTERNAL_ERROR;
	}

	void lu_brain_response_destroy(LuBrain self, LuResponse* res_p)
	{
		LuResponse res = *res_p;
		list_remove(self->resps, (LNode) res->node);
		lu_free((void**) res_p);
	}

	static void brain_resps_delete_each(List list, LNode node, lu_p_void p1)
	{
		LuBrain self 	= (LuBrain) p1;
		LuResponse res 	= (LuResponse) node->value;
		lu_brain_response_destroy(self, &res);
	}

	static void brain_resps_delete_all(LuBrain self)
	{
		list_each(self->resps, brain_resps_delete_each, self);
	}


///////////////////////////////////////////////////////////////////////////////
// Create and destroy

	Brain brain_create(struct lu_brain_args* args)
	{
		Brain self = (Brain) malloc(sizeof(struct lu_brain));
		lu_assert(self != NULL);

		if (args == NULL) args = &LU_DEFAULT_BRAIN_ARGS;

		// Time
		self->t = 1;

		// Allocator
		self->core = core_create(
			args->neuron_buff_size, 
			args->synapse_buff_size, 
			args->wave_buff_size, 
			args->processor_buff_size
		);

		// Components
		self->receivers = arr_create(args->receivers_size);

		// Responses
		self->resps 	= list_create(NULL);

		return self;
	}

	static void destroy_each_receiver(lu_p_void item)
	{
		Receiver rec = (Receiver) item;
		receiver_destroy(&rec);
	}

	void brain_destroy(Brain* self)
	{
		// Responses
		brain_resps_delete_all(*self);
		list_destroy(&(*self)->resps);

		// Receivers
		arr_each((*self)->receivers, destroy_each_receiver);
		arr_destroy(&(*self)->receivers);
		lu_assert((*self)->receivers == NULL);

		// Allocator
		core_destroy(&(*self)->core);
		lu_assert((*self)->core == NULL);

		// Brain
		lu_free((void **) self);
		lu_assert(*self == NULL);
	}



///////////////////////////////////////////////////////////////////////////////
// Getters / Setters

	lu_size brain_neu_count(Brain self)
	{

	}

	lu_time brain_t_reserve(Brain self)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Getters / Setters

	void brain_validate(Brain self)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Create receivers

	/**
		
	*/
	lu_size brain_create_receiver(
		Brain self, 
		lu_size width, lu_size height, 
		lu_value min_val, lu_value max_val, 
		lu_size val_neu_size, lu_value val_ssp
	)
	{
		Receiver receiver = receiver_create(self->core, width, height, min_val, max_val, val_neu_size, val_ssp);

		return arr_append(self->receivers, receiver);
	}



///////////////////////////////////////////////////////////////////////////////
// Save 

	static void save_input_validate(lu_size receiver_id, lu_value* data, struct lu_save_args* args)
	{
		//lu_throw(5);
	}	

	static LuSaveRes brain_save_res_create(Brain self)
	{
		LuResponse res 	= malloc(sizeof(struct lu_save_res));
		if (res == NULL) lu_throw(LU_E_ALLOC_FAILED);

		LNode node	 	= list_append(self->resps, res);
		res->node 		= (lu_p_void) node;

		return (LuSaveRes) res;
	}

	/*
		Yaksho treba shob dva receiver otrymaly v toy samyy chas, my brain.reserve_t() i otrymanyy t
		peredayemo v lu_save_args v obydva (abo bilshe) lu_brain_save() calls.

		Sequences operates on higher level, and send results to "tracking" netos.
		This method cares only about returning data from receiver level.
	*/
	SaveRes brain_save(Brain self, lu_size receiver_id, lu_value* data, struct save_args* args)
	{
		lu_exception e;

		LuSaveRes save_res = NULL;

		lu_try 
		{ 
			save_res = brain_save_res_create(self);

			brain_validate(self);
			save_input_validate(receiver_id, data, args);

			Receiver rec = arr_get(self->receivers, receiver_id);
			lu_assert(rec != NULL);

			Neto neto = receiver_save(rec, data);
			//lu_assert(neto != NULL);
		}
		lu_catch(e)
		{
			if (save_res)
			{
				LuResponse res 	= (LuResponse) save_res;
				res->status 	= brain_exception_to_status(e);
			}
		}

		return save_res;
	}

///////////////////////////////////////////////////////////////////////////////
// Find 

	FindRes brain_find(Brain self, lu_size receiver_id, lu_value* data, struct find_args* args)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Restore

	RestoreRes brain_restore(Brain self, LuNeto neto, struct restore_args* args)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Associate

	LuNeto brain_associate(Brain self, LuNeto neto, lu_size label)
	{

	}





// static void save_to_each_receiver(lu_p_void item, lu_p_void brain, lu_p_void p)
// {
// 	SRequestItem rec_req 	= (SRequestItem) item;
// 	Brain self 				= (Brain) brain;
// 	Arr receivers 			= self->receivers; 
// 	Neu recs_neu 			= (Neu) p;

// 	Receiver rec = arr_get(receivers, rec_req->receiver_id);
// 	lu_assert(rec != NULL);

// 	Neu rec_neu = receiver_save(rec, rec_req);

// 	if (!rec_neu) return;

// 	link_neu(rec_neu, recs_neu, self->core);
// }

// struct s_response brain_save(Brain self, SRequest s_request)
// {
// 	brain_validate(self);
// 	s_request_validate(s_request);

// 	//Neu seq_neu = sequence_save(self->sequence, self->t);
// 	Neu recs_neu = core_neu_alloc(self->core);

// 	arr_each_2p(s_request->items, save_to_each_receiver, self, recs_neu); 

// 	//link_neu(recs_neu, seq_neu, self->core);

// 	struct s_response resp;

// 	resp.neuron = recs_neu;

// 	return resp;
// }

// static void f_request_each_receiver(lu_p_void item, lu_p_void p1, lu_p_void p2)
// {
// 	FRequestItem req_item 	= (FRequestItem) item;
// 	Brain self 				= (Brain) p1;
// 	FindWave recs_wave 		= (FindWave) p2;

// 	Receiver rec = arr_get(self->receivers, req_item->receiver_id);
// 	lu_assert(rec != NULL);

// 	FindWave rec_wave = find_wave_create(rec->input_size, recs_wave->signif, core_t_inc(self->core), 0);

// 	receiver_find(rec, req_item, rec_wave);

// 	find_wave_merge(recs_wave, rec_wave); //?!!!! BAD
// 	find_wave_destroy(&rec_wave);
// }

// LuFResponse brain_find(Brain self, FRequest f_request)
// {
// 	brain_validate(self);
// 	f_request_validate(f_request);

// 	FindWave recs_wave = find_wave_create(f_request->items->size, f_request->signif, core_t_inc(self->core), f_request->limit);
	
// 	arr_each_2p(f_request->items, f_request_each_receiver, self, recs_wave);

// 	find_wave_process(recs_wave); 

// 	return f_response_create(recs_wave);
// } 

// lu_size brain_neu_count(Brain self)
// {
// 	return core_neu_count(self->core);
// }	

// SRequest lu_brain_restore(Brain self, Neu neu)
// {

// }

// Neu lu_brain_associate(Brain self, Neu neu, lu_size label)
// {

// }

