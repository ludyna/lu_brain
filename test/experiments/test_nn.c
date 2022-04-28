/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger md;

#define T_F_LINKS__SIZE 10

typedef struct t_cell* T_Cell;
typedef struct t_link* T_Link;

struct t_link {
	T_Cell links[T_F_LINKS__SIZE];
	lu_size links_count;
};

static inline T_Link t_link__init(T_Link self)
{
	lu__assert(self);

	self->links_count = 0;

	return self;
}

static inline void t_link__add(T_Link self, T_Cell cell)
{
	lu__assert(self->links_count + 1 < T_F_LINKS__SIZE);

	self->links[self->links_count] = cell;
	++self->links_count;
}

struct t_cell {

	lu_size label;

	struct t_link tl;
	struct t_link tr;
	struct t_link bl;
	struct t_link br;

	struct t_link children;

	lu_value sig;
	lu_size wave_id;
};

static inline T_Cell t_cell__init(T_Cell self)
{
	lu__assert(self);

	t_link__init(&self->tl);
	t_link__init(&self->tr);
	t_link__init(&self->bl);
	t_link__init(&self->br);

	t_link__init(&self->children);

	self->sig = 0;
	self->wave_id = LU_SIZE__MAX;

	return self;
}

static inline void t_cell__sig_add(T_Cell self, lu_value sig, lu_size wave_id)
{
	lu__assert(self);

	if (self->wave_id != wave_id)
	{
		self->sig = 0;
	}

	self->wave_id = wave_id;
	self->sig += sig;
}

static inline void t_cell__sig_fire_4(T_Cell c1, T_Cell c2, T_Cell c3, T_Cell c4)
{
	lu__assert(c1);


}

static inline void t_cell__connect_4_to_1(T_Cell c1, T_Cell c2, T_Cell c3, T_Cell c4, T_Cell p)
{
	lu__assert(c1);
	lu__assert(c2);
	lu__assert(c3);
	lu__assert(c4);
	lu__assert(p);

	t_link__add(&p->children, c1);
	t_link__add(&p->children, c2);
	t_link__add(&p->children, c3);
	t_link__add(&p->children, c4);


}

///////////////////////////////////////////////////////////////////////////////
// Data

struct t_cell tl_1_a;
struct t_cell tr_1_a;
struct t_cell bl_1_a;
struct t_cell br_1_a;

struct t_cell tl_1_b;
struct t_cell tr_1_b;
struct t_cell bl_1_b;
struct t_cell br_1_b;

struct t_cell tl_1_c;
struct t_cell tr_1_c;
struct t_cell bl_1_c;
struct t_cell br_1_c;

struct t_cell a;
struct t_cell b;
struct t_cell c;
struct t_cell d;

///////////////////////////////////////////////////////////////////////////////
// Setup

// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);
	TEST_ASSERT(md);

	t_cell__init(&tl_1_a);
	t_cell__init(&tr_1_a);
	t_cell__init(&bl_1_a);
	t_cell__init(&br_1_a);
 
 	t_cell__init(&tl_1_b);
	t_cell__init(&tr_1_b);
	t_cell__init(&bl_1_b);
	t_cell__init(&br_1_b);

	t_cell__init(&tl_1_c);
	t_cell__init(&tr_1_c);
	t_cell__init(&bl_1_c);
	t_cell__init(&br_1_c);

	t_cell__init(&a);
	t_cell__init(&b);
	t_cell__init(&c);
	t_cell__init(&d);
}

void tearDown(void)
{	

	lu_mem_debugger__print(md);

	TEST_ASSERT(mem_debugger_is_all_clear(md));
    lu_mem_debugger__destroy(md, true);
}

///////////////////////////////////////////////////////////////////////////////
// Tests

void test_nn_simple(void)
{
	t_cell__connect_4_to_1(&tl_1_a, &tr_1_a, &bl_1_a, &br_1_a, &a);


}