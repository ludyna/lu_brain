/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"


void setUp(void)
{ 

}

void tearDown(void)
{	
}

union u1 {
	lu_byte column_ix;
	lu_size cell_ix;
};

char* itoa(lu_size num, char* buffer, lu_size base) {
    lu_size curr = 0;
 
    if (num == 0) {
        // Base case
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return buffer;
    }
 
    lu_size num_digits = 0;
 
    if (num < 0) {
        if (base == 10) {
            num_digits ++;
            buffer[curr] = '-';
            curr ++;
            // Make it positive and finally add the minus sign
            num *= -1;
        }
        else
            // Unsupported base. Return NULL
            return NULL;
    }
 
    num_digits += (lu_size)floor(log(num) / log(base)) + 1;
 
    // Go through the digits one by one
    // from left to right
    while (curr < num_digits) {
        // Get the base value. For example, 10^2 = 1000, for the third digit
        lu_size base_val = (lu_size) pow(base, num_digits-1-curr);
 
        // Get the numerical value
        lu_size num_val = num / base_val;
 
        char value = num_val + '0';
        buffer[curr] = value;
 
        curr ++;
        num -= base_val * num_val;
    }
    buffer[curr] = '\0';
    return buffer;
}

void test__union_lu_n_addr(void) 
{
	union lu_n_addr addr;
	addr.column_ix = 1;
	addr.cell_ix = 3;
	addr.layer_ix = 9;

	union u1 u1;
	u1.column_ix = 1;
	u1.cell_ix = 3;

	lu__debug("\n union lu_n_addr SIZE: %d", sizeof(union lu_n_addr));
	lu__debug("\n lu_size SIZE: %d", sizeof(lu_size));
	lu__debug("\n union u1 SIZE: %d", sizeof(union u1));

	lu__debug("\n addr.column_ix = %d", addr.column_ix);
	lu__debug("\n addr.cell_ix = %d", addr.cell_ix);
	lu__debug("\n addr.value = %d", addr.value);

	char buffer[64];
  	itoa(addr.value, buffer, 2);
  	printf ("\n Binary cell_ix.value: %s", buffer);


	lu__debug("\n u1.column_ix = %d", u1.column_ix);
	lu__debug("\n u1.cell_ix = %d", u1.cell_ix);

	TEST_ASSERT(addr.column_ix == 1);
	TEST_ASSERT(addr.cell_ix == 3);
}

void test__union_lu_n_addr__methods(void)
{
	union lu_n_addr addr;

	Lu_N_Addr p_ix = lu_n_addr__init(&addr, 0, 0, 0);

	TEST_ASSERT(lu_n_addr__is_blank(p_ix) == true);
	TEST_ASSERT(lu_n_addr__is_present(p_ix) == false);

	lu_n_addr__init(p_ix, 0, 0, 1);

	TEST_ASSERT(lu_n_addr__is_blank(p_ix) == false);
	TEST_ASSERT(lu_n_addr__is_present(p_ix) == true);

	lu_n_addr__set_to_null(p_ix);

	TEST_ASSERT(lu_n_addr__is_blank(p_ix) == true);
	TEST_ASSERT(lu_n_addr__is_present(p_ix) == false);
}





