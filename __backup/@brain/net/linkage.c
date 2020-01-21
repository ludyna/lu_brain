#include "linkage.h"

/*
	Parent is one created before c. Child is one created after p.
*/
Lin link_neu(Neu p, Neu c, Core core)
{ 
	lu_assert(p != NULL);
	lu_assert(c != NULL);

	// link_neu_to_child(p, c, core);
	// link_neu_to_parent(c, p, core);

	Lin lin 	= core_lin_alloc(core);
	lin->p 		= p;
	lin->c 		= c;

	// dla lin ce p, dlia p lin do c
	if (p->l_c) p->l_c->p_n = lin;
	lin->p_p = p->l_c;
	p->l_c = lin;

	if (c->l_p) c->l_p->c_n = lin;
	lin->c_p = c->l_p;
	c->l_p = lin;		

	++c->count;

	return lin;
}
