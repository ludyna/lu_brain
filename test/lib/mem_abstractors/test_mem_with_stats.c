#include "unity.h"
#include "lib/_module.h"
  
Lu_Mem g_mem;

void setUp(void)
{
	g_mem = (Lu_Mem) lu_mem_with_stats_create(lu_g_mem);
	TEST_ASSERT(g_mem);
	lu_user_assert_off();
}

void tearDown(void)
{
	lu_mem_destroy(g_mem, lu_g_mem);
	lu_user_assert_on();
}

struct test1 
{ 
    lu_size size;
};

typedef struct test1* Test1;

void test_mem_stack_1(void)
{
    lu_p_byte p;
	
    #define ALLOC_SIZE 13

	p = lu_mem_alloc(g_mem, ALLOC_SIZE);
	TEST_ASSERT(p);

	TEST_ASSERT(g_mem->preallocated);
	TEST_ASSERT(lu_mem_preallocated(g_mem) == 0); 

	lu_debug("\n Used size: %ld", lu_mem_used(g_mem));

	TEST_ASSERT(lu_mem_used(g_mem) == ALLOC_SIZE + sizeof(lu_size));

	Lu_Mem_With_Stats stats = (Lu_Mem_With_Stats) g_mem;

	TEST_ASSERT(stats->alloc_size == ALLOC_SIZE + sizeof(lu_size));
	TEST_ASSERT(stats->alloc_count == 1);
	TEST_ASSERT(stats->free_count == 0);
	TEST_ASSERT(stats->free_size == 0);
	TEST_ASSERT(stats->realloc_count == 0);

	lu_mem_free(g_mem, p);

	TEST_ASSERT(stats->alloc_size == ALLOC_SIZE + sizeof(lu_size));
	TEST_ASSERT(stats->alloc_count == 1);
	TEST_ASSERT(stats->free_count == 1);

	lu_debug("\n Free size: %ld", stats->free_size);

	TEST_ASSERT(stats->free_size == ALLOC_SIZE + sizeof(lu_size));
	TEST_ASSERT(stats->realloc_count == 0);

	lu_mem_free(g_mem, p);
}
