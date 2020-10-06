#include "unity.h"
#include "lib/_module.h"

void setUp(void)
{
    
}

void tearDown(void)
{
}

struct neu 
{
    float p;
};

typedef struct neu* Neu;

void test_table_list(void)
{
    Mem_Debugger md = mem_debugger_create(g_mem_temp);

    Mem mem     = (Mem) mem_perm_create(g_mem_temp, 2048);

    Neu n1 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n2 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n3 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n4 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n5 = (Neu) mem_alloc(mem, sizeof(struct neu));

    Lu_Table_List list = lu_table_list_create(mem, 10);

    TEST_ASSERT(list != NULL);

    Lu_L_Node node1 = lu_table_list_append(list, n1);
    
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n1);
    TEST_ASSERT(lu_table_list_count(list) == 1);

    Lu_L_Node node2 = lu_table_list_append(list, n2);

    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n2);
    TEST_ASSERT(lu_table_list_count(list) == 2);


    Lu_L_Node node5 = lu_table_list_append(list, n5);

    TEST_ASSERT(lu_table_list_count(list) == 3);
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n5);
    TEST_ASSERT(list->super.last->prev->value == n2);

    lu_table_list_node_remove(list, node2);

    TEST_ASSERT(lu_table_list_count(list) == 2);
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n5);
    TEST_ASSERT(list->super.last->prev->value == n1);
 

    lu_table_list_node_remove(list, node1);

    TEST_ASSERT(lu_table_list_count(list) == 1);
    TEST_ASSERT(list->super.first->value == n5);
    TEST_ASSERT(list->super.last->value == n5);
    TEST_ASSERT(list->super.last->prev == NULL);

    lu_table_list_node_remove(list, node5);

    TEST_ASSERT(lu_table_list_count(list) == 0);
    TEST_ASSERT(list->super.first == NULL);
    TEST_ASSERT(list->super.last == NULL);

    mem_debugger_print(md);

    lu_table_list_destroy(list);
    mem_destroy(mem, g_mem_temp);


    TEST_ASSERT(mem_debugger_is_all_clear(md));
    mem_debugger_destroy(md);
}

void test_table_list_max_size(void)
{
    Mem mem     = (Mem) mem_perm_create(g_mem_temp, 2048);

    Neu n1 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n2 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n3 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n4 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n5 = (Neu) mem_alloc(mem, sizeof(struct neu));

    Lu_Table_List list = lu_table_list_create(mem, 3);

    Lu_L_Node node1 = lu_table_list_append(list, n1);
    Lu_L_Node node2 = lu_table_list_append(list, n2);
    Lu_L_Node node3 = lu_table_list_append(list, n3);

    TEST_ASSERT(lu_table_list_count(list) == 3);
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n3);
    TEST_ASSERT(list->super.first->next->value == n2);

    Lu_L_Node node4 = lu_table_list_append(list, n4);
    TEST_ASSERT(lu_table_list_count(list) == 3);
    TEST_ASSERT(list->super.first->value == n2);

    lu_table_list_destroy(list);
    mem_destroy(mem, g_mem_temp);
}