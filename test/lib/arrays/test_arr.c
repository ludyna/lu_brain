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
    Arr arr1 = arr_create(mem, 5, true);
    Arr arr2 = arr_create(mem, 2, true);

    int v1 = 1;
    int v2 = 2;
    int v3 = 3;

    arr_append(arr1, (lu_p_void) &v1);
    arr_append(arr2, (lu_p_void) &v2);
    arr_append(arr2, (lu_p_void) &v3);

    arr_merge(arr1, arr2);

    TEST_ASSERT(arr1->size == 5);
    TEST_ASSERT(arr1->count == 3);
    TEST_ASSERT( *((int*)(arr1->items[0])) == v1);
    TEST_ASSERT( *((int*)(arr1->items[1])) == v2);
    TEST_ASSERT( *((int*)(arr1->items[2])) == v3);

    arr_destroy(arr1);
    arr_destroy(arr2);
}

void test_arr2(void)
{
    Lu_Mem mem = (Lu_Mem) lu_mem_stack_create(lu_g_mem, 2048);
    Arr arr1 = arr_create(mem, 5, true);

    arr_set(arr1, 0, NULL);
    arr_set(arr1, 1, NULL);
    arr_set(arr1, 2, NULL);
    arr_set(arr1, 3, NULL);
    arr_set(arr1, 4, NULL);

    TEST_ASSERT(arr_get(arr1, 2) == NULL);

    arr_destroy(arr1);
}