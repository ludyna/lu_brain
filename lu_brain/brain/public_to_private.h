/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_PUBLIC_TO_PRIVATE_H
#define _LU_PUBLIC_TO_PRIVATE_H

#include "lu_brain.h"

///////////////////////////////////////////////////////////////////////////////
// Nouns

	#define brain lu_brain 
	#define Brain Lu_Brain

	#define neuron lu_neuron
	#define Neto Lu_Neuron

	#define name lu_name
	#define Name Lu_Name

	#define receiver lu_receiver
	#define Receiver Lu_Receiver

	#define story lu_story
	#define Story Lu_Story

	#define block lu_block
	#define Block Lu_Block

	#define wave lu_wave
	#define Wave Lu_Wave

	#define wave_resp lu_wave_resp
	#define Wave_Resp Lu_Wave_Resp

	#define save_resp lu_save_resp
	#define Save_Resp Lu_Save_Resp

	#define find_resp lu_find_resp
	#define Find_Resp Lu_Find_Resp

	#define reception lu_reception
	#define Reception Lu_Reception

	#define restore_resp lu_restore_resp
	#define Restore_Resp Lu_Restore_Resp

	// Options  
	#define brain_opts lu_brain_opts 
	#define Brain_Opts Lu_Brain_Opts

	#define receiver_opts lu_rec_opts
	#define Rec_Opts Lu_Rec_Opts

	#define save_opts lu_save_opts 
	#define Save_Opts Lu_Save_Opts

	#define find_opts lu_find_opts
	#define Find_Opts Lu_Find_Opts

	#define restore_opts lu_restore_opts
	#define Restore_Opts Lu_Restore_Opts

	// Enums 
	#define wave_status lu_wave_status
	#define neuron_type lu_neuron_type

///////////////////////////////////////////////////////////////////////////////
// Brain_Opts API

	#define brain_opts_create lu_brain_opts_create
	#define brain_opts_destroy lu_brain_opts_destroy

///////////////////////////////////////////////////////////////////////////////
// Rec_Opts API

	#define rec_opts_create lu_rec_opts_create
	#define rec_opts_destroy lu_rec_opts_destroy

///////////////////////////////////////////////////////////////////////////////
// Save_Opts API

	#define save_opts_create lu_save_opts_create
	#define save_opts_destroy lu_save_opts_destroy

///////////////////////////////////////////////////////////////////////////////
// Find_Opts API

	#define find_opts_create lu_find_opts_create
	#define find_opts_destroy lu_find_opts_destroy

	#define find_opts_limit lu_find_opts_limit
	#define find_opts_limit_set lu_find_opts_limit_set

///////////////////////////////////////////////////////////////////////////////
// Restore_Opts API

	#define restore_opts_create lu_restore_opts_create
	#define restore_opts_destroy lu_restore_opts_destroy

///////////////////////////////////////////////////////////////////////////////
// Brain API

	#define brain_create lu_brain_create
	#define brain_destroy lu_brain_destroy
	#define brain_rect_get lu_brain_rec_get
	#define brain_neuron_count lu_brain_neuron_count

///////////////////////////////////////////////////////////////////////////////
// Receiver API



///////////////////////////////////////////////////////////////////////////////
// Block API

	#define block_begin lu_block_begin
	#define block_end lu_block_end

	Block block_create(Story story);
	void block_destroy(Block* self);

///////////////////////////////////////////////////////////////////////////////
// Story API

	#define story_create lu_story_create
	#define story_destroy lu_story_destroy

	#define story_push lu_story_push

	#define story_save lu_story_save
	#define story_save_async lu_story_save_async

	#define story_find lu_story_find
	#define story_find_async lu_story_find_async

	#define story_restore lu_story_restore
	#define story_restore_async lu_story_restore_async

///////////////////////////////////////////////////////////////////////////////
// Wave API

	#define wave_is_working lu_wave_is_working
	#define wave_cancel lu_wave_cancel
	#define wave_time lu_wave_time
	#define wave_status lu_wave_status
	#define wave_touched_count lu_wave_touched_count
	#define wave_excited_count lu_wave_excited_count
	#define wave_response lu_wave_response

///////////////////////////////////////////////////////////////////////////////
// Name API
	
	#define name_create lu_name_create
	#define name_destroy lu_name_destroy

	#define name_give lu_name_give
	#define name_unlink lu_name_unlink
	
///////////////////////////////////////////////////////////////////////////////
// Wave_Resp API

	#define wave_resp_time lu_wave_resp_time
	#define wave_resp_status lu_wave_resp_status
	#define wave_resp_neuron_touched lu_wave_resp_neuron_touched
	#define wave_resp_neuron_excited lu_wave_resp_neuron_excited

///////////////////////////////////////////////////////////////////////////////
// Neto API

	#define neuron_type lu_neuron_type
	#define neuron_p lu_neuron_p
	#define neuron_names lu_neuron_names
	#define neuron_parents lu_neuron_parents
	#define neuron_children lu_neuron_children

///////////////////////////////////////////////////////////////////////////////
// Save_Resp API

	#define save_resp_neuron lu_save_resp_neuron

///////////////////////////////////////////////////////////////////////////////
// Find_Resp API

	#define find_resp_neurons lu_find_resp_neurons

///////////////////////////////////////////////////////////////////////////////
// Reception API

	#define reception_rec lu_reception_rec
	#define reception_data lu_reception_data

///////////////////////////////////////////////////////////////////////////////
// Restore_Resp API

	#define restore_resp_layers lu_restore_resp_layers

#endif // _LU_PUBLIC_TO_PRIVATE_H
