#include "unity.h"
#include "src/brain.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ph_sisa1(void)
{
    Ph_Mem ph_mem   = ph_mem_create(512);
    Ph_Sisa alloc = ph_sisa_create(ph_mem, sizeof(struct list), 3, 0, PH_S_ITEM_FREEABLE);

    TEST_ASSERT(alloc->size == 3);
    TEST_ASSERT(alloc->free_count == 0);
    TEST_ASSERT(alloc->items_count == 0);

    List l1 = (List) ph_sisa_item_alloc(alloc);
    list_init(l1, NULL);

    //lu_debug("%ld %ld %p", (lu_size)l1, (lu_size)(alloc->items_start + (alloc->size - 1) * alloc->item_size), alloc->free_start);
    TEST_ASSERT( ((lu_size)l1) == (lu_size)(alloc->items_start));
    TEST_ASSERT(alloc->size == 3);
    TEST_ASSERT(alloc->free_count == 0);
    TEST_ASSERT(alloc->items_count == 1);

    List l2 = (List) ph_sisa_item_alloc(alloc);
    list_init(l2, NULL);

    TEST_ASSERT( ((lu_size)l2) == (lu_size)(alloc->items_start + alloc->item_size) );
    TEST_ASSERT(alloc->size == 3);
    TEST_ASSERT(alloc->free_count == 0);
    TEST_ASSERT(alloc->items_count == 2);

    List l3 = (List) ph_sisa_item_alloc(alloc);
    list_init(l3, NULL);

    TEST_ASSERT( ((lu_size)l3) == (lu_size)(alloc->items_end - alloc->item_size) );
    TEST_ASSERT(alloc->size == 3);
    TEST_ASSERT(alloc->free_count == 0);
    TEST_ASSERT(alloc->items_count == 3);

    ph_sisa_item_free(alloc, (lu_p_byte) l3);

    TEST_ASSERT(alloc->size == 3);
    TEST_ASSERT(alloc->free_count == 1);
    TEST_ASSERT(alloc->items_count == 2);
    TEST_ASSERT( ((lu_size)l3) == (lu_size)(alloc->free_start[0]) );

    ph_sisa_item_free(alloc, (lu_p_byte) l2);

    TEST_ASSERT(alloc->size == 3);
    TEST_ASSERT(alloc->free_count == 2);
    TEST_ASSERT(alloc->items_count == 1);
    TEST_ASSERT( ((lu_size)l2) == (lu_size)(alloc->free_start[1]) );

    l2 = (List) ph_sisa_item_alloc(alloc);
    l1 = (List) ph_sisa_item_alloc(alloc);

    TEST_ASSERT(alloc->size == 3);
    TEST_ASSERT(alloc->free_count == 0);
    TEST_ASSERT(alloc->items_count == 3);

    List l4 = (List) ph_sisa_item_alloc(alloc);
    list_init(l4, NULL);

    ph_sisa_item_free(alloc, (lu_p_byte) l4);
    ph_sisa_item_free(alloc, (lu_p_byte) l3);
    ph_sisa_item_free(alloc, (lu_p_byte) l2);
    ph_sisa_item_free(alloc, (lu_p_byte) l1);

    TEST_ASSERT(alloc->size == 12);
    TEST_ASSERT(alloc->free_count == 8);
    TEST_ASSERT(alloc->items_count == 0);

    ph_mem_destroy(ph_mem);
    ph_mem = NULL;
}
