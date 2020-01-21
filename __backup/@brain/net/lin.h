/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_LIN_H
#define _LU_LIN_H

#include "global/lu_types.h"
 
typedef struct lin* Lin;

struct lin
{
	lu_p_void 		p;
	lu_p_void		c;

	lu_value 		w;
	// lu_time age; ne treba, dostatnio v neu
	// yaksho neu staryy, to treba vydaliaty neuron i linky,
	// i todi zhodytsia p i n

	struct lu_link* p_p;
	struct lu_link* p_n;
	struct lu_link* c_p;
	struct lu_link* c_n;
};

// ===
// struct a
// {
// 	//	lu_value weight;
// 	// 	lu_size age;
// 	lu_p_void parent;
// 	lu_p_void child;
// 	struct a* p_p;
// 	struct a* c_p;
// }

// // ===

// struct b
// {
// 	// weight
// 	lu_p_void parent;
// 	lu_p_void child;
// }

// struct bn 
// {
// 	struct b*  lin; 
// 	struct bn* prev;
// 	struct bn* next;
// }

static inline void lin_init_default(Lin self)
{
	self->p 	= NULL;
	self->c 	= NULL;

	self->w 	= 1.0;

	self->p_p 	= NULL;
	self->p_n 	= NULL;
	self->c_p 	= NULL;
	self->c_n 	= NULL;
}

#endif // _LU_LIN_H

