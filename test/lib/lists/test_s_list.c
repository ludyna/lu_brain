#include "unity.h"
#include "lib/_module.h"

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
    Lu_Mem mem = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 4096);

    Neu n1  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n2  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n3  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n35 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n4  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n45 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n5  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));

    lu__debug("A1");

    neu_p_set(n1, 1.0);
    neu_p_set(n2, 2.0);
    neu_p_set(n3, 3.0);
    neu_p_set(n35, 3.5);
    neu_p_set(n4, 4.0);
    neu_p_set(n45, 4.5);
    neu_p_set(n5, 5.0);

    srand(time(NULL));
    Lu_S_List list = lu_s_list__create(mem, 10, neu_compare, LU_S_LST__FIRST);

    lu_s_list__add(list, n4);
    TEST_ASSERT(((Neu)(list->first->value))->p == 4);
    TEST_ASSERT(list->last != NULL);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    lu_s_list__add(list, n3);
    TEST_ASSERT(((Neu)(list->first->value))->p == 3);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    lu_s_list__add(list, n1);
    lu_s_list__add(list, n5);
    lu_s_list__add(list, n35);
    lu_s_list__add(list, n2);
    lu_s_list__add(list, n45);
    TEST_ASSERT(((Neu)(list->first->value))->p == 1);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);
    TEST_ASSERT(list->count == 7);
    TEST_ASSERT(list->limit_size == 10);

    TEST_ASSERT(((Neu)(list->last->prev->value))->p == 4.5);
    TEST_ASSERT(((Neu)(list->last->prev->prev->value))->p == 4.0);
    TEST_ASSERT(((Neu)(list->last->prev->prev->prev->value))->p == 3.5);

    lu_s_list__debug(list);

    TEST_ASSERT(list->level_size == 3);

    lu_s_list__destroy(list);
    lu_mem__destroy(mem, lu_g_mem);
}

void test_s_list_limited(void)
{
    Lu_Mem mem = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 4096);

    Neu n1  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n2  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n3  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n35 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n4  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n45 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n5  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n6  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));

    neu_p_set(n1, 1.0);
    neu_p_set(n2, 2.0);
    neu_p_set(n3, 3.0);
    neu_p_set(n35, 3.5);
    neu_p_set(n4, 4.0);
    neu_p_set(n45, 4.5);
    neu_p_set(n5, 5.0);
    neu_p_set(n6, 6);

    srand(time(NULL));
    Lu_S_List list = lu_s_list__create(mem, 2, neu_compare, LU_S_LST__FIRST);

    lu_s_list__add(list, n5);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    lu_s_list__add(list, n2);

    TEST_ASSERT(((Neu)(list->first->value))->p == 2);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    lu_s_list__add(list, n3);

    TEST_ASSERT(((Neu)(list->first->value))->p == 3);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    lu_s_list__add(list, n4);

    TEST_ASSERT(((Neu)(list->first->value))->p == 4);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    lu_s_list__add(list, n35);

    TEST_ASSERT(((Neu)(list->first->value))->p == 4);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    lu_s_list__add(list, n45);

    TEST_ASSERT(((Neu)(list->first->value))->p == 4.5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    lu_s_list__add(list, n6);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 6);
    TEST_ASSERT(list->count == 2);
    TEST_ASSERT(list->limit_size == 2);

    lu_s_list__debug(list);

    lu_s_list__destroy(list);
    lu_mem__destroy(mem, lu_g_mem);
}

void test_s_list_limited_reverse(void)
{
    Lu_Mem mem = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 4096);

    Neu n1  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n2  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n3  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n35 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n4  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n45 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n5  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n6  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));

    neu_p_set(n1, 1.0);
    neu_p_set(n2, 2.0);
    neu_p_set(n3, 3.0);
    neu_p_set(n35, 3.5);
    neu_p_set(n4, 4.0);
    neu_p_set(n45, 4.5);
    neu_p_set(n5, 5.0);
    neu_p_set(n6, 6);

    srand(time(NULL));
    Lu_S_List list = lu_s_list__create(mem, 2, neu_compare_reverse, LU_S_LST__LAST);

    lu_s_list__add(list, n5);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);

    lu_s_list__add(list, n2);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 2);

    lu_s_list__add(list, n3);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->first->next->value))->p == 3);

    lu_s_list__add(list, n4);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    lu_s_list__add(list, n35);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    lu_s_list__add(list, n45);

    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4.5);

    lu_s_list__add(list, n6);

    TEST_ASSERT(((Neu)(list->first->value))->p == 6);
    TEST_ASSERT(((Neu)(list->last->value))->p == 5);
    TEST_ASSERT(list->count == 2);
    TEST_ASSERT(list->limit_size == 2);

    lu_s_list__debug(list);

    lu_s_list__destroy(list);
    lu_mem__destroy(mem, lu_g_mem);
}

void test_s_list_eq(void)
{
    Lu_Mem mem = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 4096);

    Neu n2  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n22 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n3  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n33 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n4  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n44 = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n5  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));
    Neu n6  = (Neu) lu_mem__alloc(mem, sizeof(struct neu));

    neu_p_set(n2, 2.0);
    neu_p_set(n22, 2.0);
    neu_p_set(n3, 3.0);
    neu_p_set(n33, 3.0);
    neu_p_set(n4, 4.0);
    neu_p_set(n44, 4.0);
    neu_p_set(n5, 5.0);
    neu_p_set(n6, 6);

    srand(time(NULL));
    Lu_S_List list = lu_s_list__create(mem, 3, neu_compare_reverse, LU_S_LST__LAST);

    lu_s_list__add(list, n5);
    lu_s_list__add(list, n2);
    Lu_S_Node s1 = lu_s_list__add(list, n22);

    TEST_ASSERT(list->count == 3);
    TEST_ASSERT(list->limit_size == 3);
    TEST_ASSERT(lu_lim_list__count(&s1->values) == 1);
    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 2);

    lu_s_list__add(list, n3);

    TEST_ASSERT(list->count == 3);
    TEST_ASSERT(list->limit_size == 3);
    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->first->next->value))->p == 3);
    TEST_ASSERT(((Neu)(list->last->value))->p == 2);

    s1 = lu_s_list__add(list, n33);

    TEST_ASSERT(lu_lim_list__count(&s1->values) == 1);
    TEST_ASSERT(list->count == 3);
    TEST_ASSERT(list->limit_size == 3);
    TEST_ASSERT(((Neu)(list->first->value))->p == 5);
    TEST_ASSERT(((Neu)(list->first->next->value))->p == 3);
    TEST_ASSERT(((Neu)(list->last->value))->p == 3);

    lu_s_list__add(list, n4);
    lu_s_list__add(list, n6);
    lu_s_list__add(list, n44);

    TEST_ASSERT(list->count == 3);
    TEST_ASSERT(list->limit_size == 3);
    TEST_ASSERT(((Neu)(list->first->value))->p == 6);
    TEST_ASSERT(((Neu)(list->first->next->value))->p == 5);
    TEST_ASSERT(((Neu)(list->last->value))->p == 4);

    lu_s_list__debug(list);

    lu_s_list__destroy(list);
    lu_mem__destroy(mem, lu_g_mem);
}