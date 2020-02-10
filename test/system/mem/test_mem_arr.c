#include "unity.h"
#include "src/brain.h"

void setUp(void)
{
}

void tearDown(void)
{
}

struct test1 {
    lu_size size;
};

typedef struct test1* Test1;

void test_mem_arr1(void)
{
    Mem mem     = (Mem) mem_preallocated_create(512);
    Mem_Arr ma  = mem_arr_create(
        /*Mem*/         mem, 
        /*item_size*/   sizeof(struct test1), 
        /*size*/        3, 
        /*percent*/     0, 
        /*flags*/       MEM_ARR_ITEM_FREEABLE
    );

    TEST_ASSERT(ma->size == 3);
    TEST_ASSERT(ma->free_count == 0);
    TEST_ASSERT(ma->items_count == 0);

    Test1 l1 = (Test1) mem_arr_item_alloc(ma);

    lu_debug("%ld %ld %p", (lu_size)l1, (lu_size)(ma->items_start + (ma->size - 1) * ma->item_size), ma->free_start);
    TEST_ASSERT( ((lu_size)l1) == (lu_size)(ma->items_start));
    TEST_ASSERT(ma->size == 3);
    TEST_ASSERT(ma->free_count == 0);
    TEST_ASSERT(ma->items_count == 1);
    TEST_ASSERT(l1 != NULL);

    Test1 l2 = (Test1) mem_arr_item_alloc(ma);

    TEST_ASSERT( ((lu_size)l2) == (lu_size)(ma->items_start + ma->item_size) );
    TEST_ASSERT(ma->size == 3);
    TEST_ASSERT(ma->free_count == 0);
    TEST_ASSERT(ma->items_count == 2);
    TEST_ASSERT(l2 != NULL);

    Test1 l3 = (Test1) mem_arr_item_alloc(ma);

    TEST_ASSERT( ((lu_size)l3) == (lu_size)(ma->items_end - ma->item_size) );
    TEST_ASSERT(ma->size == 3);
    TEST_ASSERT(ma->free_count == 0);
    TEST_ASSERT(ma->items_count == 3);
    TEST_ASSERT(l3 != NULL);

    mem_arr_item_free(ma, (lu_p_byte) l3);

    TEST_ASSERT(ma->size == 3);
    TEST_ASSERT(ma->free_count == 1);
    TEST_ASSERT(ma->items_count == 2);
    TEST_ASSERT( ((lu_size)l3) == (lu_size)(ma->free_start[0]) );

    mem_arr_item_free(ma, (lu_p_byte) l2);

    TEST_ASSERT(ma->size == 3);
    TEST_ASSERT(ma->free_count == 2);
    TEST_ASSERT(ma->items_count == 1);
    TEST_ASSERT( ((lu_size)l2) == (lu_size)(ma->free_start[1]) );

    l2 = (Test1) mem_arr_item_alloc(ma);
    l1 = (Test1) mem_arr_item_alloc(ma);

    TEST_ASSERT(ma->size == 3);
    TEST_ASSERT(ma->free_count == 0);
    TEST_ASSERT(ma->items_count == 3);

    Test1 l4 = (Test1) mem_arr_item_alloc(ma);
    TEST_ASSERT(l4 == NULL);

    mem_arr_item_free(ma, (lu_p_byte) l4);
    mem_arr_item_free(ma, (lu_p_byte) l3);
    mem_arr_item_free(ma, (lu_p_byte) l2);
    mem_arr_item_free(ma, (lu_p_byte) l1);

    // TEST_ASSERT(ma->size == 12);
    // TEST_ASSERT(ma->free_count == 8);
    // TEST_ASSERT(ma->items_count == 0);

    mem_preallocated_destroy(mem);
    mem = NULL;
}
