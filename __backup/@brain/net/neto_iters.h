/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/
#ifndef _LU_NETO_ITERS_H
#define _LU_NETO_ITERS_H

#include "neto.h"
#include "lin.h"
#include "waves/find_wave.h"

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void neto_each_parent(Neto self, void (*block)(Neto child, Neto item));
void neto_each_parent_from_first(Neto self, void (*block)(Neto child, Neto item));
void neto_each_parent_1p(Neto self, void (*block)(Neto child, Neto item, lu_p_void p1), lu_p_void p1);
void neto_each_parent_2p(Neto self, void (*block)(Neto child, Neto item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

void neto_each_child(Neto self, void (*block)(Neto parent, Neto item));
void neto_each_child_1p(Neto self, void (*block)(Neto parent, Neto item, lu_p_void p1), lu_p_void p1);
void neto_each_child_2p(Neto self, void (*block)(Neto parent, Neto item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

///////////////////////////////////////////////////////////////////////////////
// Other public methods



#endif // _LU_NETO_ITERS_H
