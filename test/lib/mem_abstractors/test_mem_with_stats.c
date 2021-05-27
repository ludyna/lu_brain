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
	
	p = lu_mem_alloc(g_mem, 13);

	TEST_ASSERT(p);

	lu_mem_free(g_mem, p);
}
