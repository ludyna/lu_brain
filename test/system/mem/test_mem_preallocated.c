#include "unity.h"
#include "brain/brain.h"

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

void test_sys_1(void)
{
   Mem mem = (Mem) mem_preallocated_create(g_mem_default, 512);

   TEST_ASSERT(mem != NULL);

   mem_destroy(mem, g_mem_default);
}
