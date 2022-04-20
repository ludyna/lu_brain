/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger md;
struct lu_label_map m;
Lu_Label_Map map;

// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);
	TEST_ASSERT(md);
	map = &m;

	map = lu_label_map__init(map, lu_g_mem, 10, 100, 3);
	TEST_ASSERT(map);
}

void tearDown(void)
{	
	lu_label_map__deinit(map);

	lu_mem_debugger__print(md);

	TEST_ASSERT(mem_debugger_is_all_clear(md));
    lu_mem_debugger__destroy(md, true);
}

void test_label_map(void)
{
	union lu_n_addr a_1;
	union lu_n_addr a_2;
	union lu_n_addr a_3;


	lu_n_addr__init(&a_1, 33, 33, 33, 33);
	lu_n_addr__init(&a_2, 1, 0, 0, 7); 
	lu_n_addr__init(&a_3, 33, 33, 33, 33);

	Lu_Label label;
	label = lu_label_map__add_label(map, a_1, 5);

	TEST_ASSERT(label->label == 5);
	TEST_ASSERT(label->count == 1);

	label = lu_label_map__add_label(map, a_1, 5);

	TEST_ASSERT(label->label == 5);
	TEST_ASSERT(label->count == 2);

	label = lu_label_map__add_label(map, a_1, 7);

	TEST_ASSERT(label->label == 7);
	TEST_ASSERT(label->count == 1);

	label = lu_label_map__add_label(map, a_3, 5);

	TEST_ASSERT(label->label == 5);
	TEST_ASSERT(label->count == 3);

	Lu_Label_Unit unit;

	unit = lu_label_map__get_labels(map, a_3);
	TEST_ASSERT(unit);

	TEST_ASSERT(lu_label_unit__is_blank(unit) == false);
	TEST_ASSERT(lu_label_unit__is_match(unit, a_3) == true);

	label = lu_label_unit__get_label(unit, 5);

	TEST_ASSERT(label->label == 5);
	TEST_ASSERT(label->count == 3);

	label = lu_label_map__add_label(map, a_2, 5);

	Lu_List list = lu_label_map__get_units(map, 5);

	TEST_ASSERT(list);

	unit = (Lu_Label_Unit) lu_list__first_value(list);

	TEST_ASSERT(lu_n_addr__is_eq(&unit->addr, &a_1));

	unit = (Lu_Label_Unit) lu_list__last_value(list);

	TEST_ASSERT(lu_n_addr__is_eq(&unit->addr, &a_2));
}