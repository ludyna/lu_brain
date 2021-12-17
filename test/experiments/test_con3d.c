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

float a0[3][6][6] = {
	{
		{ 10, 10, 10, 10, 10, 10 },
		{ 10, 10, 10, 10, 10, 10 },
		{ 10, 10, 10, 10, 10, 10 },
		{ 10, 10, 10, 10, 10, 10 },
		{ 10, 10, 10, 10, 10, 10 },
		{ 10, 10, 10, 10, 10, 10 }
	},
	{
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 }
	},
	{
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 },
		{ 2, 2, 2, 10, 10, 10 }
	}
};

float a1[3][6][6] = {
	{
		{ 10, 2, 2, 2, 2, 2 },
		{ 2, 10, 2, 2, 2, 2 },
		{ 2, 2, 10, 2, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 2, 10, 2 },
		{ 2, 2, 2, 2, 2, 10 }
	},
	{
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 }
	},
	{
		{ 2, 2, 2, 2, 2, 10 },
		{ 2, 2, 2, 2, 10, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 10, 2, 2, 2 },
		{ 2, 10, 2, 2, 2, 2 },
		{ 10, 2, 2, 2, 2, 2 }
	}
};

float a2[3][6][6] = {
	{
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 }
	},
	{
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 }
	},
	{
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 },
		{ 2, 2, 2, 10, 2, 2 }
	}
};


typedef unsigned int uint;

static inline float get(int x, int y, int z, float* p, int h, int w)
{
	return p[z * w * h + x + w * y];
}

float find_value(int x, int y, int z, float* p, uint w, uint h)
{
	if(x < 0) x = 0;
	if(x >= w) x = w - 1;
	if(y < 0) y = 0;
	if(y >= h) y = h - 1;

	return get(x, y, z, p, h, w);
}

void c1(float *p, uint w, uint h, uint r, const char* lu_name)
{
	float sum;
	int xmin, xmax, ymin, ymax, zmin, zmax;
	int x1, y1, z1, x2, y2, z2;
	float count, v;
 	
 	z1 = 1;

	printf("\n%s INPUT: ", lu_name);
	for(z1 = 0; z1 < 3; z1++)
		for(y1 = 0; y1 < h; y1++)
		{
			printf("\n");
			for(x1 = 0; x1 < w; x1++)
			{
				printf("%4.1f, ", get(x1, y1, z1, p, h, w));
			}
		}

	printf("\n%s OUTPUT: ", lu_name);

	z1 = 1;

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

			zmin = 0;
			zmax = 2;

			sum = 0;
			count = 0;

			for(z2 = zmin; z2 <= zmax; z2++)
			//z2 = 1;
				for(y2 = ymin; y2 <= ymax; y2++)
					for(x2 = xmin; x2 <= xmax; x2++)
					{
						if (y2 == y1 && x2 == x1 && z2 == z1) continue;

						//sum += p[x2 + w * y2];
						sum += find_value(x2, y2, z2, p, w, h);
						++count;
					}

			v = get(x1, y1, z1, p, h, w) - sum / count;
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

void test_c1a0(void) 
{
	c1((float*)a0, 6, 6, 1, __func__);
	TEST_ASSERT(1);
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