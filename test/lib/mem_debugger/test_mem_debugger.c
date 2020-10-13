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
    Mem_Debugger md = mem_debugger_create(g_mem_temp);
    TEST_ASSERT(md);

    mem_debugger_destroy(md, true);
}
