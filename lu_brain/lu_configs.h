/**
	Copyright © 2020 Oleh Ihorovych Novosad
	Ludyna Brain configs 
	You can redefine these constants in your app. Just make sure to define them before #include "lu_brain.h".
*/
#ifndef _LU_CONFIGS_PUB_H
#define _LU_CONFIGS_PUB_H
 
#include "lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// N_Mem

#ifndef LU_NAMES_SIZE
#define LU_NAMES_SIZE 256
#endif

#ifndef LU_MAX_BLOCKS_SIZE 
#define LU_MAX_BLOCKS_SIZE 16
#endif

///////////////////////////////////////////////////////////////////////////////
// N_Mem

	enum lu_roc_predefinde_type {
		LU_ROC_MONOCHROME1_IMAGE = 0,
		LU_ROC_MONOCHROME8_IMAGE,
		LU_ROC_RBG8_IMAGE,
		LU_ROC_RBG16_IMAGE, 
		LU_ROC_RBG32_IMAGE,
		LU_ROC_END 				// this one should be always last, put your custom settings above it
	};

	struct lu_rec_opts_config {
		lu_size 		depth;

		lu_size 		max_blocks_size;

		lu_value 		v_min;
		lu_value 		v_max;
		lu_size			v_neu_size;
		lu_size 		v_nsc;

		lu_size 		p_neu_size;
		lu_size 		p_nsc;  	// nei sim count	

	};

	struct lu_rec_opts_config lu_g_roc_predefinitions[LU_ROC_END] = {
		{
			// LU_ROC_MONOCHROME1_IMAGE
			.depth 				= 1,
			.max_blocks_size 	= LU_MAX_BLOCKS_SIZE,
			
			.v_min 				= 0,
			.v_max 				= 1,
			.v_neu_size			= 2,
			.v_nsc				= 0,

			.p_neu_size			= 2,
			.p_nsc				= 0
		},

	};

#endif // _LU_CONFIGS_PUB_H