/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"


struct lu_n_link_mem v_link_mem;

Lu_N_Link_Mem link_mem;
Lu_N_Link n_link_1 = NULL;
Lu_N_Link n_link_2 = NULL;
Lu_N_Link n_link_3 = NULL;

#define CHILDREN_COUNT 3
Lu_N_Cell_VP children_1[CHILDREN_COUNT];
struct lu_n_cell_vp v_children_1[CHILDREN_COUNT];


void setUp(void)
{ 
	link_mem = &v_link_mem;
	lu_n_link_mem__init(link_mem, lu_g_mem, 1024);

	lu_n_cell_vp__null_init(&v_children_1[0]);
	lu_n_cell_vp__null_init(&v_children_1[1]);
	lu_n_cell_vp__null_init(&v_children_1[2]);

	children_1[0] = &v_children_1[0];
	children_1[1] = &v_children_1[1];
	children_1[2] = &v_children_1[2];

	children_1[0]->addr.value = 1;
	children_1[1]->addr.value = 2;
	children_1[2]->addr.value = 3;
}

void tearDown(void)
{	
	lu_n_link_mem__deinit(link_mem);
}

void test___lu_n_link__is_vp_children_eq(void) 
{
	union lu_n_addr a1[] = {{.value = 1}, {.value = 1}, {.value = 1}};
	union lu_n_addr a2[] = {{.value = 2}, {.value = 2}, {.value = 2}};
	union lu_n_addr a3[] = {{.value = 3}, {.value = 3}, {.value = 3}};
	union lu_n_addr a4[] = {{.value = 0}, {.value = 0}, {.value = 0}};

	TEST_ASSERT(lu_n_link__is_vp_children_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == false);

	n_link_1 = lu_n_link_mem__link_alloc(link_mem);
	n_link_1->cell_addr.value = 1;
	n_link_1->next.value = 0;

	TEST_ASSERT(lu_n_link__is_vp_children_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == false);

	n_link_2 = lu_n_link_mem__link_alloc(link_mem);
	n_link_2->cell_addr.value = 2;
	n_link_2->next.value = 0;

	n_link_1->next = lu_n_link_mem__get_addr(link_mem, n_link_2);

	TEST_ASSERT(lu_n_link__is_vp_children_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == false);

	n_link_3 = lu_n_link_mem__link_alloc(link_mem);
	n_link_3->cell_addr.value = 3;
	n_link_3->next.value = 0;

	n_link_2->next = lu_n_link_mem__get_addr(link_mem, n_link_3);

	TEST_ASSERT(lu_n_link__is_vp_children_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == true);

}


