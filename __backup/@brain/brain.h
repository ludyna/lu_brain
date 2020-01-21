/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_BRAIN_INTERNAL_H
#define _LU_BRAIN_INTERNAL_H

#include "lu_brain.h"
///////////////////////////////////////////////////////////////////////////////
// Defines

	#define brain lu_brain
	#define Brain LuBrain
	
	#define brain_neu_count lu_brain_neu_count
	#define brain_t_reserve lu_brain_t_reserve

	#define brain_create_default lu_brain_create_default
	#define brain_create lu_brain_create
	#define brain_destroy lu_brain_destroy

	#define brain_create_receiver lu_brain_create_receiver


	#define save_args lu_save_args
	#define SaveRes LuSaveRes	
	#define brain_save lu_brain_save
	
	#define find_args lu_find_args
	#define FindRes LuFindRes	
	#define brain_find lu_brain_find

	#define restore_args lu_restore_args
	#define RestoreRes LuRestoreRes	
	#define brain_restore lu_brain_restore

	#define brain_associate lu_brain_associate

	void brain_validate(Brain);

#endif // _LU_BRAIN_INTERNAL_H

