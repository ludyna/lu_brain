#include "unity.h"
#include "src/brain.h"

struct neu 
{
    float p;
};

typedef struct neu* Neu;


void setUp(void)
{
}

void tearDown(void)
{
}

void test_list_fast_alloc(void)
{
    Sis_Alloc sis_alloc = sis_alloc_create(10, sizeof(struct neu));

    Neu n1 = (Neu) sis_alloc_item_alloc(sis_alloc);
    Neu n2 = (Neu) sis_alloc_item_alloc(sis_alloc);
    Neu n3 = (Neu) sis_alloc_item_alloc(sis_alloc);
    Neu n4 = (Neu) sis_alloc_item_alloc(sis_alloc);
    Neu n5 = (Neu) sis_alloc_item_alloc(sis_alloc);

    Ln_Alloc_Fast alloc = ln_alloc_fast_create(3);
    List list = list_create((LnAlloc) alloc);

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

    L_Node node5 = list_append(list, n5);

    // TEST_ASSERT(node5 == node2);

    ln_alloc_fast_destroy(&alloc, NULL);
    list_destroy(&list);
    sis_alloc_destroy(&sis_alloc);
}

void test_list_fast_1(void)
{
    char* st        = "Hello";
    lu_p_void value = (lu_p_void) st;

    Ln_Alloc_Fast alloc = ln_alloc_fast_create(3);

    TEST_ASSERT(alloc->sis_alloc->size == 3);
    TEST_ASSERT(alloc->sis_alloc->count == 0);
    TEST_ASSERT(alloc->sis_alloc->free_count == 0);

    alloc->super.node_create((LnAlloc) alloc, value);
    
    TEST_ASSERT(alloc->sis_alloc->count == 1);
    TEST_ASSERT(alloc->sis_alloc->free_count == 0);

    alloc->super.node_create((LnAlloc) alloc, value);

    TEST_ASSERT(alloc->sis_alloc->count == 2);
    TEST_ASSERT(alloc->sis_alloc->free_count == 0);

    alloc->super.node_create((LnAlloc) alloc, value);

    TEST_ASSERT(alloc->sis_alloc->count == 3);
    TEST_ASSERT(alloc->sis_alloc->free_count == 0);

    alloc->super.node_create((LnAlloc) alloc, value);

    TEST_ASSERT(alloc->sis_alloc->size == 6);
    TEST_ASSERT(alloc->sis_alloc->count == 4);
    TEST_ASSERT(alloc->sis_alloc->free_count == 0);

    ln_alloc_fast_destroy(&alloc, NULL);
}
