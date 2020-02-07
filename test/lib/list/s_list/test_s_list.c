#include "unity.h"
#include "src/brain.h"

struct neu 
{
    float p;
};

typedef struct neu* Neu;

void neu_p_set(Neu neu, float v)
{
    neu->p = v;
}

void setUp(void)
{
}

void tearDown(void)
{
}

static lu_value neu_compare(lu_p_void p1, lu_p_void p2)
{
    Neu x   = (Neu) p1;
    Neu y   = (Neu) p2;

    return  x->p - y->p;
}

static lu_value neu_compare_reverse(lu_p_void p1, lu_p_void p2)
{
    Neu x   = (Neu) p1;
    Neu y   = (Neu) p2;

    return y->p - x->p; 
}

void test_s_list1(void)
{
    Mem mem = (Mem) preallocated_mem_create(4096);

    Neu n1  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n2  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n3  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n35 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n4  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n45 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n5  = (Neu) mem_alloc(mem, sizeof(struct neu));

    neu_p_set(n1, 1.0);
    neu_p_set(n2, 2.0);
    neu_p_set(n3, 3.0);
    neu_p_set(n35, 3.5);
    neu_p_set(n4, 4.0);
    neu_p_set(n45, 4.5);
    neu_p_set(n5, 5.0);

    srand(time(NULL));
    S_List list = s_list_create(mem, 10, neu_compare, S_LIST_FIRST);

    s_list_add(list, n4);
    TEST_ASSERT(((Neu)(list->first->value))->p == 4);
    TEST_ASSERT(list->last != NULL);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    s_list_add(list, n3);
    TEST_ASSERT(((Neu)(list->first->value))->p == 3);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    s_list_add(list, n1);
    s_list_add(list, n5);
    s_list_add(list, n35);
    s_list_add(list, n2);
    s_list_add(list, n45);
    TEST_ASSERT(((Neu)(list->first->value))->p == 1);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);
    TEST_ASSERT(list->count == 7);
    TEST_ASSERT(list->limit_size == 10);

    TEST_ASSERT(((Neu)(list->last->prev->value))->p == 4.5);
    TEST_ASSERT(((Neu)(list->last->prev->prev->value))->p == 4.0);
    TEST_ASSERT(((Neu)(list->last->prev->prev->prev->value))->p == 3.5);

    s_list_debug(list);

    TEST_ASSERT(list->level_size == 3);

    preallocated_mem_destroy(mem);
}

void test_s_list_limited(void)
{
    Mem mem = (Mem) preallocated_mem_create(4096);

    Neu n1  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n2  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n3  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n35 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n4  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n45 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n5  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n6  = (Neu) mem_alloc(mem, sizeof(struct neu));

    neu_p_set(n1, 1.0);
    neu_p_set(n2, 2.0);
    neu_p_set(n3, 3.0);
    neu_p_set(n35, 3.5);
    neu_p_set(n4, 4.0);
    neu_p_set(n45, 4.5);
    neu_p_set(n5, 5.0);
    neu_p_set(n6, 6);

    srand(time(NULL));
    S_List list = s_list_create(mem, 2, neu_compare, S_LIST_FIRST);

    s_list_add(list, n5);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    s_list_add(list, n2);

    TEST_ASSERT(((Neu)(list->first->value))->p == 2);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    s_list_add(list, n3);

    TEST_ASSERT(((Neu)(list->first->value))->p == 3);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    s_list_add(list, n4);

    TEST_ASSERT(((Neu)(list->first->value))->p == 4);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    s_list_add(list, n35);

    TEST_ASSERT(((Neu)(list->first->value))->p == 4);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    s_list_add(list, n45);

    TEST_ASSERT(((Neu)(list->first->value))->p == 4.5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    s_list_add(list, n6);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 6);
    TEST_ASSERT(list->count == 2);
    TEST_ASSERT(list->limit_size == 2);

    s_list_debug(list);

    preallocated_mem_destroy(mem);
}

void test_s_list_limited_reverse(void)
{
    Mem mem = (Mem) preallocated_mem_create(4096);

    Neu n1  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n2  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n3  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n35 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n4  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n45 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n5  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n6  = (Neu) mem_alloc(mem, sizeof(struct neu));

    neu_p_set(n1, 1.0);
    neu_p_set(n2, 2.0);
    neu_p_set(n3, 3.0);
    neu_p_set(n35, 3.5);
    neu_p_set(n4, 4.0);
    neu_p_set(n45, 4.5);
    neu_p_set(n5, 5.0);
    neu_p_set(n6, 6);

    srand(time(NULL));
    S_List list = s_list_create(mem, 2, neu_compare_reverse, S_LIST_LAST);

    s_list_add(list, n5);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    s_list_add(list, n2);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 2);

    s_list_add(list, n3);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->first->next->value))->p == 3);

    s_list_add(list, n4);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    s_list_add(list, n35);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    s_list_add(list, n45);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4.5);

    s_list_add(list, n6);

    TEST_ASSERT(((Neu)(list->first->value))->p == 6);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);
    TEST_ASSERT(list->count == 2);
    TEST_ASSERT(list->limit_size == 2);

    s_list_debug(list);

    preallocated_mem_destroy(mem);
}

void test_s_list_eq(void)
{
    Mem mem = (Mem) preallocated_mem_create(4096);

    Neu n2  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n22 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n3  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n33 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n4  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n44 = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n5  = (Neu) mem_alloc(mem, sizeof(struct neu));
    Neu n6  = (Neu) mem_alloc(mem, sizeof(struct neu));

    neu_p_set(n2, 2.0);
    neu_p_set(n22, 2.0);
    neu_p_set(n3, 3.0);
    neu_p_set(n33, 3.0);
    neu_p_set(n4, 4.0);
    neu_p_set(n44, 4.0);
    neu_p_set(n5, 5.0);
    neu_p_set(n6, 6);

    srand(time(NULL));
    S_List list = s_list_create(mem, 3, neu_compare_reverse, S_LIST_LAST);

    s_list_add(list, n5);
    s_list_add(list, n2);
    S_Node s1 = s_list_add(list, n22);

    TEST_ASSERT(list->count == 3);
    TEST_ASSERT(list->limit_size == 3);
    TEST_ASSERT(s1->values.count == 1);
    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 2);

    s_list_add(list, n3);

    TEST_ASSERT(list->count == 3);
    TEST_ASSERT(list->limit_size == 3);
    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->first->next->value))->p == 3);
    TEST_ASSERT(((Neu)(list->last->value))->p == 2);

    s1 = s_list_add(list, n33);

    TEST_ASSERT(s1->values.count == 1);
    TEST_ASSERT(list->count == 3);
    TEST_ASSERT(list->limit_size == 3);
    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->first->next->value))->p == 3);
    TEST_ASSERT(((Neu)(list->last->value))->p == 3);

    s_list_add(list, n4);
    s_list_add(list, n6);
    s_list_add(list, n44);

    TEST_ASSERT(list->count == 3);
    TEST_ASSERT(list->limit_size == 3);
    TEST_ASSERT(((Neu)(list->first->value))->p == 6);
    TEST_ASSERT(((Neu)(list->first->next->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    s_list_debug(list);

    preallocated_mem_destroy(mem);
}