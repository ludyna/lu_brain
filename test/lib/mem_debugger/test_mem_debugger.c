#include "unity.h"
#include "lib/_module.h"

void setUp(void)
{
}

void tearDown(void)
{
}



void test_mem_debugger(void)
{
    Lu_Mem_Debugger md = lu_mem_debugger__create(lu_g_mem);
    TEST_ASSERT(md);

    lu_mem_debugger__destroy(md, true);
}
