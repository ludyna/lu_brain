#include "unity.h"
#include "src/brain.h"

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
   System sys = system_create(512);

   system_destroy(sys);
}
