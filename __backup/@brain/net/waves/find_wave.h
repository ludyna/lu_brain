/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_FIND_WAVE_H
#define _LU_FIND_WAVE_H

#include "lib/arr.h"
#include "lib/lists/s_list/s_list.h"
#include "neu.h"

// ///////////////////////////////////////////////////////////////////////////////
// // Structs and types

// // Bahato optymizaciy tut mozhlyvo:
// // Ihnoruvany stari zviazky abo zviazok stariye i vidnovluyetsia tilky 
// // koly jde zvorotniy sygnal.

// typedef struct find_wave* FindWave;

// struct find_wave {
// 	lu_value 	signif;
// 	lu_time 	t;

// 	Arr 		bottom;
// 	Arr 		top;

// 	SList 		apex;
// };

// ///////////////////////////////////////////////////////////////////////////////
// // Create and destroy

// FindWave find_wave_create(lu_size size, lu_value signif, lu_time t, lu_size);
// void find_wave_destroy(FindWave*);

// ///////////////////////////////////////////////////////////////////////////////
// // Setters/getters

// static inline void find_wave_bottom_append(FindWave self, Neu neu) { arr_append(self->bottom, neu); }
// static inline SList find_wave_apex(FindWave self) { return self->apex; }

// ///////////////////////////////////////////////////////////////////////////////
// // Main public methods

// Arr find_wave_process(FindWave);

// static inline void find_wave_merge(FindWave self, FindWave src) { arr_merge(self->bottom, src->bottom); }

// ///////////////////////////////////////////////////////////////////////////////
// // Other public methods




#endif // _LU_FIND_WAVE_H
