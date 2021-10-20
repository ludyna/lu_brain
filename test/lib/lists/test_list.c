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

void test_list1(void)
{
    Lu_Mem mem     = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 2048);

    Neu n1 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n2 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n3 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n4 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n5 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));

    Lu_List list = lu_list__create(mem);

    TEST_ASSERT(list != NULL);

    Lu_L_Node node1 = lu_list__append(list, n1);
    
    TEST_ASSERT(list->first->value == n1);
    TEST_ASSERT(list->last->value == n1);
    TEST_ASSERT(lu_list__count(list) == 1);

    Lu_L_Node node2 = lu_list__append(list, n2);

    TEST_ASSERT(list->first->value == n1);
    TEST_ASSERT(list->last->value == n2);
    TEST_ASSERT(lu_list__count(list) == 2);

    Lu_L_Node node3 = lu_list__prepend(list, n3);

    TEST_ASSERT(lu_list__count(list) == 3);
    TEST_ASSERT(list->first->value == n3);
    TEST_ASSERT(list->last->value == n2);
    TEST_ASSERT(list->first->next->value == n1);

    Lu_L_Node node5 = lu_list__append(list, n5);

    TEST_ASSERT(lu_list__count(list) == 4);
    TEST_ASSERT(list->first->value == n3);
    TEST_ASSERT(list->last->value == n5);
    TEST_ASSERT(list->last->prev->value == n2);

    lu_list__node_remove(list, node2);

    TEST_ASSERT(lu_list__count(list) == 3);
    TEST_ASSERT(list->first->value == n3);
    TEST_ASSERT(list->last->value == n5);
    TEST_ASSERT(list->last->prev->value == n1);

    lu_list__node_remove(list, node3);

    TEST_ASSERT(lu_list__count(list) == 2);
    TEST_ASSERT(list->first->value == n1);
    TEST_ASSERT(list->last->value == n5);
    TEST_ASSERT(list->last->prev->value == n1);

    lu_list__node_remove(list, node1);

    TEST_ASSERT(lu_list__count(list) == 1);
    TEST_ASSERT(list->first->value == n5);
    TEST_ASSERT(list->last->value == n5);
    TEST_ASSERT(list->last->prev == NULL);

    lu_list__node_remove(list, node5);

    TEST_ASSERT(lu_list__count(list) == 0);
    TEST_ASSERT(list->first == NULL);
    TEST_ASSERT(list->last == NULL);

    lu_list__destroy(list);
    lu_mem_destroy(mem, lu_g_mem);
}

void test_list_fast_ma(void)
{
    Lu_Mem mem     = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 2048);

    Neu n1 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n2 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n3 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n4 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n5 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));

    Lu_List list = lu_list__create(mem);

    Lu_L_Node node1 = lu_list__append(list, n1);
    Lu_L_Node node2 = lu_list__append(list, n2);
    Lu_L_Node node3 = lu_list__append(list, n3);

    TEST_ASSERT(lu_list__count(list) == 3);
    TEST_ASSERT(list->first->value == n1);
    TEST_ASSERT(list->last->value == n3);
    TEST_ASSERT(list->first->next->value == n2);

    Lu_L_Node node4 = lu_list__prepend(list, n4);
    TEST_ASSERT(lu_list__count(list) == 4);
    TEST_ASSERT(list->first->value == n4);

    lu_list__node_remove(list, node2);

    TEST_ASSERT(list->count == 3);

    lu_list__destroy(list);
    lu_mem_destroy(mem, lu_g_mem);
}