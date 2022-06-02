/**
	Copyright © 2022 Oleh Ihorovych Novosad 


*/

#include "unity.h"

#include <limits.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>

float a1[6][6] = {
	{ 2, 2, 2, 10, 10, 10 },
	{ 2, 2, 2, 10, 10, 10 },
	{ 2, 2, 2, 10, 10, 10 },
	{ 2, 2, 2, 10, 10, 10 },
	{ 2, 2, 2, 10, 10, 10 },
	{ 2, 2, 2, 10, 10, 10 }
};

float a2[6][6] = {
	{ 2, 2, 2, 10, 2, 2 },
	{ 2, 2, 2, 10, 2, 2 },
	{ 2, 2, 2, 10, 2, 2 },
	{ 2, 2, 2, 10, 2, 2 },
	{ 2, 2, 2, 10, 2, 2 },
	{ 2, 2, 2, 10, 2, 2 }
};

float a3[6][6] = {
	{ 1, 2, 3, 4, 5, 6 },
	{ 1, 2, 3, 4, 5, 6 },
	{ 1, 2, 3, 4, 5, 6 },
	{ 1, 2, 3, 4, 5, 6 },
	{ 1, 2, 3, 4, 5, 6 },
	{ 1, 2, 3, 4, 5, 6 }
};

float a4[6][6] = {
	{ 2, 2, 2, 8, 2, 2 },
	{ 2, 2, 2, 8, 2, 2 },
	{ 8, 8, 8, 8, 8, 8 },
	{ 2, 2, 2, 8, 2, 2 },
	{ 2, 2, 2, 8, 2, 2 },
	{ 2, 2, 2, 8, 2, 2 }
};
 
float a5[6][6] = {
	{ 2, 2, 2, 8, 2, 2 },
	{ 2, 2, 2, 8, 2, 2 },
	{ 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 2, 2 },
	{ 8, 8, 8, 8, 2, 2 },
	{ 8, 8, 8, 8, 2, 2 }
};

float a6[6][7] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 2, 3, 4, 3, 2, 1 },
	{ 1, 2, 3, 4, 3, 2, 1 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 }
};

typedef unsigned int uint;

float find_value(int x, int y, float* p, uint w, uint h)
{
	if (x < 0) x = 0;
	if (x >= w) x = w - 1;
	if (y < 0) y = 0;
	if (y >= h) y = h - 1;

	return p[x + w * y];
}

void c1(float *p, uint w, uint h, uint r, const char* lu_name)
{
	float sum;
	int xmin, xmax, ymin, ymax;
	int x1, y1, x2, y2;
	float count, v;
 
	printf("\n%s INPUT: ", lu_name);
	for(y1 = 0; y1 < h; y1++)
	{
		printf("\n");
		for(x1 = 0; x1 < w; x1++)
		{
			printf("%4.1f, ", p[x1 + w * y1]);
		}
	}

	printf("\n%s OUTPUT: ", lu_name);
	for(y1 = 0; y1 < h; y1++)
	{
		printf("\n");
		for(x1 = 0; x1 < w; x1++)
		{
			xmin = x1 - r;
			// if (xmin < 0) xmin = 0;

			xmax = x1 + r;
			// if (xmax >= w) xmax = w - 1;

			ymin = y1 - r;
			// if (ymin < 0) ymin = 0;

			ymax = y1 + r;
			// if (ymax >= h) ymax = h - 1;

			sum = 0;
			count = 0;

			for(y2 = ymin; y2 <= ymax; y2++)
				for(x2 = xmin; x2 <= xmax; x2++)
				{
					if (y2 == y1 && x2 == x1) continue;

					//sum += p[x2 + w * y2];
					sum += find_value(x2, y2, p, w, h);
					++count;
				}

			v = p[x1 + w * y1] - sum / count;
			if (v < 0) v = 0;

			//printf("%4.1f(%4.1f %4.1f %4.1f %d %d %d %d), ", v, p[x1 + w * y1], sum, count, ymin, ymax, xmin, xmax);
			printf("%4.1f, ", v);
		}
	}
}

void setUp(void)
{ 

}

void tearDown(void)
{	

}

void test_c1a1(void) 
{
	c1((float*)a1, 6, 6, 1, __func__);
	TEST_ASSERT(1);
}

void test_c1a2(void) 
{
	c1((float*)a2, 6, 6, 1, __func__);
	TEST_ASSERT(1);
}

void test_c1a3(void) 
{
	c1((float*)a3, 6, 6, 1, __func__);
	TEST_ASSERT(1);
}

void test_c1a1r2(void) 
{
	c1((float*)a1, 6, 6, 2, __func__);
	TEST_ASSERT(1);
}

void test_c1a1r3(void) 
{
	c1((float*)a1, 6, 6, 3, __func__);
	TEST_ASSERT(1);
}

void test_c1a2r3(void) 
{
	c1((float*)a2, 6, 6, 3, __func__);
	TEST_ASSERT(1);
}

void test_c1a4(void) 
{
	c1((float*)a4, 6, 6, 1, __func__);
	TEST_ASSERT(1);
}

void test_c1a5(void) 
{
	c1((float*)a5, 6, 6, 3, __func__);
	TEST_ASSERT(1);
}

void test_c1a6(void) 
{
	c1((float*)a6, 7, 6, 3, __func__);
	TEST_ASSERT(1);
}

void test_c5a7(void) 
{
	c1((float*)a1, 6, 6, 2, __func__);
	TEST_ASSERT(1);
}