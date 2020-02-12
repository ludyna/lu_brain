#include "unity.h"
#include "brain/brain.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_list1(void)
{
    Mem mem  = mem_create();
    Arr arr1 = arr_create(mem, 2);
    Arr arr2 = arr_create(mem, 3);

    int v1 = 1;
    int v2 = 2;
    int v3 = 3;

    arr_append(arr1, (lu_p_void) &v1);
    arr_append(arr2, (lu_p_void) &v2);
    arr_append(arr2, (lu_p_void) &v3);

    arr_merge(arr1, arr2);

    TEST_ASSERT(arr1->size == 3);
    TEST_ASSERT(arr1->count == 3);
    TEST_ASSERT( *((int*)(arr1->items[0])) == v1);
    TEST_ASSERT( *((int*)(arr1->items[1])) == v2);
    TEST_ASSERT( *((int*)(arr1->items[2])) == v3);

    arr_destroy(arr1, mem);
    arr_destroy(arr2, mem);
}
