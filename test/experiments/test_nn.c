/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger md;

#define T_LINKS_SIZE 10

typedef struct t_cell* T_Cell;
typedef struct t_link* T_Link;

struct t_link {
	T_Cell links[T_LINKS_SIZE];
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
	lu__assert(self->links_count + 1 < T_LINKS_SIZE);

	self->links[self->links_count] = cell;
	++self->links_count;
}

struct t_cell {

	struct t_link tl;
	struct t_link tr;
	struct t_link bl;
	struct t_link br;

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

	self->sig = 0;
	self->wave_id = LU_SIZE__MAX;

	return self;
}

static inline void t_cell__fire(T_Cell self, lu_value sig)
{

}


// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);
	TEST_ASSERT(md);
}

void tearDown(void)
{	

	lu_mem_debugger__print(md);

	TEST_ASSERT(mem_debugger_is_all_clear(md));
    lu_mem_debugger__destroy(md, true);
}

void test_nn_simple(void)
{

}