/**
	Copyright © 2020 Oleh Ihorovych Novosad
	Ludyna Brain configs 
	You can redefine these constants in your app. Just make sure to define them before #include "lu_brain.h".
*/
#ifndef _LU_CONFIGS_PUB_H
#define _LU_CONFIGS_PUB_H
 
#include "lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// Gate 

#ifndef LU_SAVE_WAVES_SIZE
#define LU_SAVE_WAVES_SIZE 1
#endif

#ifndef LU_FIND_WAVES_SIZE
#define LU_FIND_WAVES_SIZE 1
#endif

#ifndef LU_RESTORE_WAVES_SIZE
#define LU_RESTORE_WAVES_SIZE 1
#endif

///////////////////////////////////////////////////////////////////////////////
// N_Mem

#ifndef LU_NAMES_SIZE
#define LU_NAMES_SIZE 64
#endif


#endif // _LU_CONFIGS_PUB_H