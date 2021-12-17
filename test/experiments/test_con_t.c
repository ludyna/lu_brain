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
	{ 2, 2, 2, 2, 10, 10 },
	{ 2, 2, 2, 2, 10, 10 },
	{ 2, 2, 2, 2, 10, 10 },
	{ 2, 2, 2, 2, 10, 10 },
	{ 2, 2, 2, 2, 10, 10 },
	{ 2, 2, 2, 2, 10, 10 }
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

float a7[6][7] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 }
};

typedef unsigned int uint;

float find_value(int x, int y, float* p, uint w, uint h)
{
	if(x < 0) x = 0;
	if(x >= w) x = w - 1;
	if(y < 0) y = 0;
	if(y >= h) y = h - 1;

	return p[x + w * y];
}

void c1(float* t1, float* t2, uint w, uint h, uint r, const char* lu_name)
{
	float sum;
	int xmin, xmax, ymin, ymax;
	int x1, y1, x2, y2;
	float count, v;
 
	printf("\n%s INPUT t1: ", lu_name);
	for(y1 = 0; y1 < h; y1++)
	{
		printf("\n");
		for(x1 = 0; x1 < w; x1++)
		{
			printf("%4.1f, ", t1[x1 + w * y1]);
		}
	}
	printf("\n%s INPUT t2: ", lu_name);
	for(y1 = 0; y1 < h; y1++)
	{
		printf("\n");
		for(x1 = 0; x1 < w; x1++)
		{
			printf("%4.1f, ", t2[x1 + w * y1]);
		}
	}

	printf("\n%s OUTPUT: ", lu_name);
	for(y1 = 0; y1 < h; y1++)
	{
		printf("\n");
		for(x1 = 0; x1 < w; x1++)
		{
			v = fabs(t1[x1 + w * y1] - t2[x1 + w * y1]);

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

void test_a1a2(void) 
{
	c1((float*)a1, (float*)a2, 6, 6, 1, __func__);
}

void test_a6a7(void) 
{
	c1((float*)a6, (float*)a7, 7, 6, 1, __func__);
}
