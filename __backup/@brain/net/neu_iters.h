/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/
#ifndef _LU_NEU_ITERS_H
#define _LU_NEU_ITERS_H

#include "neu.h"
#include "lin.h"
#include "waves/find_wave.h"

///////////////////////////////////////////////////////////////////////////////
// Give 

void neu_give_p_block_1p(Neu self, lu_value p, lu_time t, void(*block)(Neu, Neu, lu_p_void), lu_p_void p1);

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void neu_each_parent(Neu self, void (*block)(Neu child, Neu item));
void neu_each_parent_from_first(Neu self, void (*block)(Neu child, Neu item));
void neu_each_parent_1p(Neu self, void (*block)(Neu child, Neu item, lu_p_void p1), lu_p_void p1);
void neu_each_parent_2p(Neu self, void (*block)(Neu child, Neu item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

void neu_each_child(Neu self, void (*block)(Neu parent, Neu item));
void neu_each_child_1p(Neu self, void (*block)(Neu parent, Neu item, lu_p_void p1), lu_p_void p1);
void neu_each_child_2p(Neu self, void (*block)(Neu parent, Neu item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

///////////////////////////////////////////////////////////////////////////////
// Other public methods



#endif // _LU_NEU_ITERS_H
