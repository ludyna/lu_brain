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
    Lu_Mem_Debugger md = mem_debugger_create(lu_g_mem);
    TEST_ASSERT(md);

    mem_debugger_destroy(md, true);
}
