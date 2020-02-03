#include "unity.h"
#include "src/brain.h"

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
    Mem mem     = mem_create(2048);

    Neu n1 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n2 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n3 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n4 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n5 = (Neu) mem_alloc(mem, sizeof(struct neu));

    List list = list_create(mem, 10);

    TEST_ASSERT(list != NULL);
    TEST_ASSERT(list->mem_arr != NULL);

    L_Node node1 = list_append(list, n1);
    
    TEST_ASSERT(list->first->value == n1);
    TEST_ASSERT(list->last->value == n1);
    TEST_ASSERT(list_count(list) == 1);

    L_Node node2 = list_append(list, n2);

    TEST_ASSERT(list->first->value == n1);
    TEST_ASSERT(list->last->value == n2);
    TEST_ASSERT(list_count(list) == 2);

    L_Node node3 = list_prepend(list, n3);

    TEST_ASSERT(list_count(list) == 3);
    TEST_ASSERT(list->first->value == n3);
    TEST_ASSERT(list->last->value == n2);
    TEST_ASSERT(list->first->next->value == n1);

    L_Node node5 = list_append(list, n5);

    TEST_ASSERT(list_count(list) == 4);
    TEST_ASSERT(list->first->value == n3);
    TEST_ASSERT(list->last->value == n5);
    TEST_ASSERT(list->last->prev->value == n2);

    list_remove(list, node2);

    TEST_ASSERT(list_count(list) == 3);
    TEST_ASSERT(list->first->value == n3);
    TEST_ASSERT(list->last->value == n5);
    TEST_ASSERT(list->last->prev->value == n1);

    list_remove(list, node3);

    TEST_ASSERT(list_count(list) == 2);
    TEST_ASSERT(list->first->value == n1);
    TEST_ASSERT(list->last->value == n5);
    TEST_ASSERT(list->last->prev->value == n1);

    list_remove(list, node1);

    TEST_ASSERT(list_count(list) == 1);
    TEST_ASSERT(list->first->value == n5);
    TEST_ASSERT(list->last->value == n5);
    TEST_ASSERT(list->last->prev == NULL);

    list_remove(list, node5);

    TEST_ASSERT(list_count(list) == 0);
    TEST_ASSERT(list->first == NULL);
    TEST_ASSERT(list->last == NULL);

    mem_destroy(mem);
}

void test_list_fast_ma(void)
{
    Mem mem     = mem_create(2048);

    Neu n1 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n2 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n3 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n4 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n5 = (Neu) mem_alloc(mem, sizeof(struct neu));

    List list = list_create(mem, 10);

    L_Node node1 = list_append(list, n1);
    L_Node node2 = list_append(list, n2);
    L_Node node3 = list_append(list, n3);

    TEST_ASSERT(list_count(list) == 3);
    TEST_ASSERT(list->first->value == n1);
    TEST_ASSERT(list->last->value == n3);
    TEST_ASSERT(list->first->next->value == n2);

    L_Node node4 = list_prepend(list, n4);
    TEST_ASSERT(list_count(list) == 4);
    TEST_ASSERT(list->first->value == n4);

    list_remove(list, node2);

    TEST_ASSERT(list->count == 3);

    mem_destroy(mem);
}