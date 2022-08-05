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
Lu_N_Link n_link_4 = NULL;

#define CHILDREN_COUNT 3
Lu_W_Cell_P children_1[CHILDREN_COUNT];
struct lu_w_cell_p v_children_1[CHILDREN_COUNT];

struct lu_n_cell_vp n_cell_1;
struct lu_n_cell_vp n_cell_2;
struct lu_n_cell_vp n_cell_3;
struct lu_n_cell_vp n_cell_4;



void setUp(void)
{ 
	link_mem = &v_link_mem;
	lu_n_link_mem__init(link_mem, lu_g_mem, 1024);

	// lu_n_cell_vp__null_init(&v_children_1[0]);
	// lu_n_cell_vp__null_init(&v_children_1[1]);
	// lu_n_cell_vp__null_init(&v_children_1[2]);

	children_1[0] = &v_children_1[0];
	children_1[1] = &v_children_1[1];
	children_1[2] = &v_children_1[2];

	n_cell_1.addr.value = 1;
	n_cell_2.addr.value = 2;
	n_cell_3.addr.value = 3;
	n_cell_4.addr.value = 4;

	children_1[0]->n_cell = &n_cell_1;
	children_1[1]->n_cell = &n_cell_2;
	children_1[2]->n_cell = &n_cell_3;

}

void tearDown(void)
{	
	lu_n_link_mem__deinit(link_mem);
}

void test___lu_n_cell_children__is_vp_eq(void) 
{
	// TEST_ASSERT(lu_n_link_addr__is_vp_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == false);

	// n_link_1 = lu_n_link_mem__link_alloc(link_mem);
	// n_link_1->n_cell_addr = n_cell_1.addr;
	// n_link_1->next.value = 0;

	// TEST_ASSERT(lu_n_link_addr__is_vp_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == false);

	// n_link_2 = lu_n_link_mem__link_alloc(link_mem);
	// n_link_2->n_cell_addr = n_cell_2.addr;
	// n_link_2->next.value = 0;

	// n_link_1->next = lu_n_link_mem__get_addr(link_mem, n_link_2);

	// TEST_ASSERT(lu_n_link_addr__is_vp_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == false);

	// n_link_3 = lu_n_link_mem__link_alloc(link_mem);
	// n_link_3->n_cell_addr = n_cell_3.addr;
	// n_link_3->next.value = 0;

	// n_link_2->next = lu_n_link_mem__get_addr(link_mem, n_link_3);

	// TEST_ASSERT(lu_n_link_addr__is_vp_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == true);

	// n_link_4 = lu_n_link_mem__link_alloc(link_mem);
	// n_link_4->n_cell_addr = n_cell_4.addr;
	// n_link_4->next.value = 0;

	// n_link_3->next = lu_n_link_mem__get_addr(link_mem, n_link_4);

	// TEST_ASSERT(lu_n_link_addr__is_vp_eq(n_link_1, children_1, CHILDREN_COUNT, link_mem) == true);
}


