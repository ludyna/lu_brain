#include "unity.h"
#include "lib/_module.h"

void setUp(void)
{
    
}

void tearDown(void)
{
}

struct test1 {
    lu_size table_size_in_records;
};

typedef struct test1* Test1;

void test_mem_table1(void)
{
    Lu_Mem mem        = (Lu_Mem) mem_perm_create(lu_g_mem, 512);
    Lu_Mem_Table mt   = mem_table_create(
        /*Lu_Mem*/                     mem, 
        /*record_size_in_bytes*/    sizeof(struct test1), 
        /*table_size_in_records*/   3, 
        /*percent*/                 0, 
        /*flags*/                   MTF_FREEABLE
    );

    TEST_ASSERT( ((Mem_Table_Perm)mt)->mem_perm == (Mem_Perm) mem );

    TEST_ASSERT(mt->table_size_in_records == 3);
    TEST_ASSERT(mt->free_count == 0);
    TEST_ASSERT(mt->records_count == 0);

    Test1 l1 = (Test1) mem_record_alloc(mt);

    lu_debug("%ld %ld %p", (lu_size)l1, (lu_size)(mt->records_start + (mt->table_size_in_records - 1) * mt->record_size_in_bytes), mt->free_start);
    TEST_ASSERT( ((lu_size)l1) == (lu_size)(mt->records_start));
    TEST_ASSERT(mt->table_size_in_records == 3);
    TEST_ASSERT(mt->free_count == 0);
    TEST_ASSERT(mt->records_count == 1);
    TEST_ASSERT(l1 != NULL);

    Test1 l2 = (Test1) mem_record_alloc(mt);

    TEST_ASSERT( ((lu_size)l2) == (lu_size)(mt->records_start + mt->record_size_in_bytes) );
    TEST_ASSERT(mt->table_size_in_records == 3);
    TEST_ASSERT(mt->free_count == 0);
    TEST_ASSERT(mt->records_count == 2);
    TEST_ASSERT(l2 != NULL);

    Test1 l3 = (Test1) mem_record_alloc(mt);

    TEST_ASSERT( ((lu_size)l3) == (lu_size)(mt->records_end - mt->record_size_in_bytes) );
    TEST_ASSERT(mt->table_size_in_records == 3);
    TEST_ASSERT(mt->free_count == 0);
    TEST_ASSERT(mt->records_count == 3);
    TEST_ASSERT(l3 != NULL);

    mem_record_free(mt, (lu_p_byte) l3);

    TEST_ASSERT(mt->table_size_in_records == 3);
    TEST_ASSERT(mt->free_count == 1);
    TEST_ASSERT(mt->records_count == 2);
    TEST_ASSERT( ((lu_size)l3) == (lu_size)(mt->free_start[0]) );

    mem_record_free(mt, (lu_p_byte) l2);

    TEST_ASSERT(mt->table_size_in_records == 3);
    TEST_ASSERT(mt->free_count == 2);
    TEST_ASSERT(mt->records_count == 1);
    TEST_ASSERT( ((lu_size)l2) == (lu_size)(mt->free_start[1]) );

    l2 = (Test1) mem_record_alloc(mt);
    l1 = (Test1) mem_record_alloc(mt);

    TEST_ASSERT(mt->table_size_in_records == 3);
    TEST_ASSERT(mt->free_count == 0);
    TEST_ASSERT(mt->records_count == 3);

    lu_user_assert_off();
    Test1 l4 = (Test1) mem_record_alloc(mt);
    lu_user_assert_on();
    
    TEST_ASSERT(l4 == NULL);

    mem_record_free(mt, (lu_p_byte) l4);
    mem_record_free(mt, (lu_p_byte) l3);
    mem_record_free(mt, (lu_p_byte) l2);
    mem_record_free(mt, (lu_p_byte) l1);

    // TEST_ASSERT(mt->table_size_in_records == 12);
    // TEST_ASSERT(mt->free_count == 8);
    // TEST_ASSERT(mt->records_count == 0);

    mem_destroy(mem, lu_g_mem);
}
