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
	lu_byte pos;
	lu_size ix;
};

char* itoa(int num, char* buffer, int base) {
    int curr = 0;
 
    if (num == 0) {
        // Base case
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return buffer;
    }
 
    int num_digits = 0;
 
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
 
    num_digits += (int)floor(log(num) / log(base)) + 1;
 
    // Go through the digits one by one
    // from left to right
    while (curr < num_digits) {
        // Get the base value. For example, 10^2 = 1000, for the third digit
        int base_val = (int) pow(base, num_digits-1-curr);
 
        // Get the numerical value
        int num_val = num / base_val;
 
        char value = num_val + '0';
        buffer[curr] = value;
 
        curr ++;
        num -= base_val * num_val;
    }
    buffer[curr] = '\0';
    return buffer;
}

void test_string__eq(void) 
{
	union lu_n_ix ix;
	ix.pos = 1;
	ix.ix = 3;

	union u1 u1;
	u1.pos = 1;
	u1.ix = 3;

	lu__debug("\n struct lu_n_ix SIZE: %d", sizeof(union lu_n_ix));
	lu__debug("\n lu_size SIZE: %d", sizeof(lu_size));
	lu__debug("\n union u1 SIZE: %d", sizeof(union u1));

	lu__debug("\n ix.pos = %d", ix.pos);
	lu__debug("\n ix.ix = %d", ix.ix);
	lu__debug("\n ix.value = %d", ix.value);

	char buffer[64];
  	itoa(ix.value, buffer, 2);
  	printf ("\n Binary ix.value: %s", buffer);


	lu__debug("\n u1.pos = %d", u1.pos);
	lu__debug("\n u1.ix = %d", u1.ix);

	TEST_ASSERT(ix.pos == 1);
	TEST_ASSERT(ix.ix == 3);
}





