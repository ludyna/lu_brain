#include "unity.h"
#include "lib/_module.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_arr1(void)
{
    Lu_Mem mem  = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 2048);
    Lu_Arr arr1 = lu_arr__create(mem, 5, true);
    Lu_Arr arr2 = lu_arr__create(mem, 2, true);

    int v1 = 1;
    int v2 = 2;
    int v3 = 3;

    lu_arr_append(arr1, (lu_p_void) &v1);
    lu_arr_append(arr2, (lu_p_void) &v2);
    lu_arr_append(arr2, (lu_p_void) &v3);

    lu_arr_merge(arr1, arr2);

    TEST_ASSERT(arr1->size == 5);
    TEST_ASSERT(arr1->count == 3);
    TEST_ASSERT( *((int*)(arr1->items[0])) == v1);
    TEST_ASSERT( *((int*)(arr1->items[1])) == v2);
    TEST_ASSERT( *((int*)(arr1->items[2])) == v3);

    lu_arr__destroy(arr1);
    lu_arr__destroy(arr2);
}

void test_arr2(void)
{
    Lu_Mem mem = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 2048);
    Lu_Arr arr1 = lu_arr__create(mem, 5, true);

    lu_arr__set(arr1, 0, NULL);
    lu_arr__set(arr1, 1, NULL);
    lu_arr__set(arr1, 2, NULL);
    lu_arr__set(arr1, 3, NULL);
    lu_arr__set(arr1, 4, NULL);

    TEST_ASSERT(lu_arr__get(arr1, 2) == NULL);

    lu_arr__destroy(arr1);
}