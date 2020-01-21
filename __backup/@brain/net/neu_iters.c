/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/

#include <stdlib.h>
#include "lib/utils.h"
#include "neu_iters.h"

///////////////////////////////////////////////////////////////////////////////
// Give 

/*
** Give children p ignoring state of parent. Useful for val neurons.
*/
void neu_give_p_block_1p(Neu self, lu_value p, lu_time t, void(*block)(Neu, Neu, lu_p_void), lu_p_void p1)
{
	Lin item 		= self->l_c;
	Neu child;   

	while (item)
	{
		child = item->c;
		neu_receive_with_t(child, p, t);
		block(self, child, p1); 
		item = item->p_p;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Iterators

void neu_each_parent_from_first(Neu self, void (*block)(Neu child, Neu item))
{
	Lin item = self->l_p;
	Lin first = NULL;
	while (item)
	{
		first = item;
		item = item->c_p;
	}

	while (first)
	{
		block(self, first->p);
		first = first->c_n;
	}
}
void neu_each_parent(Neu self, void (*block)(Neu child, Neu item))
{
	Lin item = self->l_p;
	while (item)
	{
		block(self, item->p);
		item = item->c_p;
	}
}
void neu_each_parent_1p(Neu self, void (*block)(Neu child, Neu item, lu_p_void p1), lu_p_void p1)
{
	Lin item = self->l_p;
	while (item)
	{
		block(self, item->p, p1);
		item = item->c_p;
	}
}
void neu_each_parent_2p(Neu self, void (*block)(Neu child, Neu item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2)
{ 
	Lin item = self->l_p;
	while (item)
	{
		block(self, item->p, p1, p2);
		item = item->c_p;
	}
}

void neu_each_child(Neu self, void (*block)(Neu parent, Neu item))
{
	Lin item = self->l_c;
	while (item)
	{
		block(self, item->c);
		item = item->p_p;
	}
}
void neu_each_child_1p(Neu self, void (*block)(Neu parent, Neu item, lu_p_void p1), lu_p_void p1) 
{
	Lin item = self->l_c;
	while (item)
	{
		block(self, item->c, p1);
		item = item->p_p;
	}
}
void neu_each_child_2p(Neu self, void (*block)(Neu parent, Neu item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2)
{ 
	Lin item = self->l_c;
	while (item)
	{
		block(self, item->c, p1, p2);
		item = item->p_p;
	}
}