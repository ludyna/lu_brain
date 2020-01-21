/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/

#include <stdlib.h>
#include "lib/utils.h"
#include "neto_iters.h"


///////////////////////////////////////////////////////////////////////////////
// Iterators

void neto_each_parent_from_first(Neto self, void (*block)(Neto child, Neto item))
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
void neto_each_parent(Neto self, void (*block)(Neto child, Neto item))
{
	Lin item = self->l_p;
	while (item)
	{
		block(self, item->p);
		item = item->c_p;
	}
}
void neto_each_parent_1p(Neto self, void (*block)(Neto child, Neto item, lu_p_void p1), lu_p_void p1)
{
	Lin item = self->l_p;
	while (item)
	{
		block(self, item->p, p1);
		item = item->c_p;
	}
}
void neto_each_parent_2p(Neto self, void (*block)(Neto child, Neto item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2)
{ 
	Lin item = self->l_p;
	while (item)
	{
		block(self, item->p, p1, p2);
		item = item->c_p;
	}
}

void neto_each_child(Neto self, void (*block)(Neto parent, Neto item))
{
	Lin item = self->l_c;
	while (item)
	{
		block(self, item->c);
		item = item->p_p;
	}
}
void neto_each_child_1p(Neto self, void (*block)(Neto parent, Neto item, lu_p_void p1), lu_p_void p1) 
{
	Lin item = self->l_c;
	while (item)
	{
		block(self, item->c, p1);
		item = item->p_p;
	}
}
void neto_each_child_2p(Neto self, void (*block)(Neto parent, Neto item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2)
{ 
	Lin item = self->l_c;
	while (item)
	{
		block(self, item->c, p1, p2);
		item = item->p_p;
	}
}