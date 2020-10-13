#include "unity.h"
#include "lib/_module.h"
  
void setUp(void)
{

}

void tearDown(void)
{

}

struct test1 
{ 
    lu_size size;
};

typedef struct test1* Test1;

void test_mem_perm_1(void)
{
	Mem mem = (Mem) mem_perm_create(g_mem_temp, 512);

    TEST_ASSERT(mem);

    lu_p_byte p;
	
	lu_user_assert_off();

	for (lu_size i = 0; i < 10; i++)
	{
		p = mem_alloc(mem, 512);

		TEST_ASSERT(p == NULL);
	}

	lu_user_assert_on();

	mem_destroy(mem, g_mem_temp);
}
