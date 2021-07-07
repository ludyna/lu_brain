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

void test_lim_list(void)
{
    Mem_Debugger md = mem_debugger_create(lu_g_mem);

    Lu_Mem mem     = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 2048);

    Neu n1 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));
    Neu n2 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));
    Neu n3 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));
    Neu n4 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));
    Neu n5 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));

    Lu_Lim_List list = lu_lim_list_create(mem, 10);

    TEST_ASSERT(list != NULL);

    Lu_L_Node node1 = lu_lim_list_append(list, n1);
    
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n1);
    TEST_ASSERT(lu_lim_list_count(list) == 1);

    Lu_L_Node node2 = lu_lim_list_append(list, n2);

    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n2);
    TEST_ASSERT(lu_lim_list_count(list) == 2);


    Lu_L_Node node5 = lu_lim_list_append(list, n5);

    TEST_ASSERT(lu_lim_list_count(list) == 3);
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n5);
    TEST_ASSERT(list->super.last->prev->value == n2);

    lu_lim_list_node_remove(list, node2);

    TEST_ASSERT(lu_lim_list_count(list) == 2);
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n5);
    TEST_ASSERT(list->super.last->prev->value == n1);
 

    lu_lim_list_node_remove(list, node1);

    TEST_ASSERT(lu_lim_list_count(list) == 1);
    TEST_ASSERT(list->super.first->value == n5);
    TEST_ASSERT(list->super.last->value == n5);
    TEST_ASSERT(list->super.last->prev == NULL);

    lu_lim_list_node_remove(list, node5);

    TEST_ASSERT(lu_lim_list_count(list) == 0);
    TEST_ASSERT(list->super.first == NULL);
    TEST_ASSERT(list->super.last == NULL);

    lu_lim_list_destroy(list);
    lu_mem_destroy(mem, lu_g_mem);

    //mem_debugger_print(md);

    TEST_ASSERT(mem_debugger_is_all_clear(md));
    mem_debugger_destroy(md, true);
}

void test_lim_list_max_size(void)
{
    Mem_Debugger md = mem_debugger_create(lu_g_mem);
    Lu_Mem mem     = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 2048);

    Neu n1 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));
    Neu n2 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));
    Neu n3 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));
    Neu n4 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));
    Neu n5 = (Neu) lu_mem_alloc(mem, sizeof(struct neu));

    Lu_Lim_List list = lu_lim_list_create(mem, 3);

    Lu_L_Node node1 = lu_lim_list_append(list, n1);
    Lu_L_Node node2 = lu_lim_list_append(list, n2);
    Lu_L_Node node3 = lu_lim_list_append(list, n3);

    TEST_ASSERT(lu_lim_list_count(list) == 3);
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n3);
    TEST_ASSERT(list->super.first->next->value == n2);

    Lu_L_Node node4 = lu_lim_list_append(list, n4);
    TEST_ASSERT(lu_lim_list_count(list) == 3);
    TEST_ASSERT(list->super.first->value == n2);

    lu_lim_list_destroy(list);
    lu_mem_destroy(mem, lu_g_mem);

    TEST_ASSERT(mem_debugger_is_all_clear(md));
    mem_debugger_destroy(md, true);
}

void node_before_destroy(Lu_Lim_List self, Lu_L_Node node)
{
    Neu neu = (Neu) lu_l_node_value(node);
    lu_mem_free(self->super.mem, (lu_p_byte) neu);
}

void test_lim_list_clear(void)
{
    Mem_Debugger md = mem_debugger_create(lu_g_mem);

    Neu n1 = (Neu) lu_mem_alloc(lu_g_mem, sizeof(struct neu));
    Neu n2 = (Neu) lu_mem_alloc(lu_g_mem, sizeof(struct neu));
    Neu n3 = (Neu) lu_mem_alloc(lu_g_mem, sizeof(struct neu));
    Neu n4 = (Neu) lu_mem_alloc(lu_g_mem, sizeof(struct neu));
    Neu n5 = (Neu) lu_mem_alloc(lu_g_mem, sizeof(struct neu));

    Lu_Lim_List list = lu_lim_list_create(lu_g_mem, 3);

    list->node_before_destroy = node_before_destroy;

    Lu_L_Node node1 = lu_lim_list_append(list, n1);
    Lu_L_Node node2 = lu_lim_list_append(list, n2);
    Lu_L_Node node3 = lu_lim_list_append(list, n3);

    TEST_ASSERT(lu_lim_list_count(list) == 3);
    TEST_ASSERT(list->super.first->value == n1);
    TEST_ASSERT(list->super.last->value == n3);
    TEST_ASSERT(list->super.first->next->value == n2);

    Lu_L_Node node4 = lu_lim_list_append(list, n4);
    TEST_ASSERT(lu_lim_list_count(list) == 3);
    TEST_ASSERT(list->super.first->value == n2); 

    lu_lim_list_clear(list);

    lu_lim_list_destroy(list);

    TEST_ASSERT(mem_debugger_is_all_clear(md));
    mem_debugger_destroy(md, true);
}