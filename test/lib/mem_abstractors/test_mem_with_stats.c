#include "unity.h"
#include "lib/_module.h"
  
Lu_Mem g_mem;

void setUp(void)
{
	g_mem = (Lu_Mem) lu_mem_with_stats_create(lu_g_mem);
	TEST_ASSERT(g_mem);
	lu__user_assert_off();
}

void tearDown(void)
{
	lu_mem__destroy(g_mem, lu_g_mem);
	lu__user_assert_on();
}

void test_mem_stats(void)
{
    lu_p_byte p;
	
    #define ALLOC_SIZE 13
    #define REALLOC_SIZE 44

	p = lu_mem__alloc(g_mem, ALLOC_SIZE);

		TEST_ASSERT(p);

		TEST_ASSERT(g_mem->preallocated);
		TEST_ASSERT(lu_mem__preallocated(g_mem) == 0); 

		lu__debug("\n Used size: %ld", lu_mem__used(g_mem));

		TEST_ASSERT(lu_mem__used(g_mem) == ALLOC_SIZE + sizeof(lu_size));

		Lu_Mem_With_Stats stats = (Lu_Mem_With_Stats) g_mem;

		TEST_ASSERT(stats->alloc_size == ALLOC_SIZE + sizeof(lu_size));
		TEST_ASSERT(stats->alloc_count == 1);
		TEST_ASSERT(stats->free_count == 0);
		TEST_ASSERT(stats->free_size == 0);
		TEST_ASSERT(stats->realloc_count == 0);

	p = lu_mem__realloc(g_mem, p, REALLOC_SIZE);

		TEST_ASSERT(p);
		TEST_ASSERT(lu_mem__used(g_mem) == REALLOC_SIZE + sizeof(lu_size)); 

	lu_mem__free(g_mem, p);

		TEST_ASSERT(stats->alloc_size == ALLOC_SIZE + sizeof(lu_size) + REALLOC_SIZE + sizeof(lu_size));
		TEST_ASSERT(stats->alloc_count == 1);
		TEST_ASSERT(stats->free_count == 1);

		lu__debug("\n Free size: %ld", stats->free_size);

		TEST_ASSERT(stats->free_size == ALLOC_SIZE + sizeof(lu_size) + REALLOC_SIZE + sizeof(lu_size));
		TEST_ASSERT(stats->realloc_count == 1);

	lu_mem__free(g_mem, p);
}
