/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	test_lu_brain tests public interfaces (from library user point of view) and includes 
	general integration tests. It uses nouns with Lu_ prefix only and methods with lu_ prefixes 
	only.
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Brain 			brain;
Lu_Rec 				rec_0;
Lu_Rec 				rec_1;

lu_value			data_00[] 		= { 
										0, 0, 0,
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_01[] 		= { 
										1, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_02[] 		= { 
										2, 0, 0,
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_03[] 		= { 
										3, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_04[] 		= { 
										4, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_05[] 		= { 
										5, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_06[] 		= { 
										6, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};

lu_value			data_10[] 		= { 
										0, 0, 
										1, 1,
									};
lu_value			data_11[] 		= { 
										1, 0,
										1, 1,
									};
lu_value			data_12[] 		= { 
										2, 0,
										1, 1,
									};
lu_value			data_13[] 		= { 
										3, 0, 
										1, 1,
									};
lu_value			data_14[] 		= { 
										4, 0, 
										1, 1,
									};
lu_value			data_15[] 		= { 
										5, 0, 
										1, 1,
									};
lu_value			data_16[] 		= { 
										6, 0,
										1, 1,
									};


// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	brain 				= lu_brain__create(lu_g_mem, lu_brain_config__get_by_id(LU_BC_DEFAULT));

	TEST_ASSERT(brain);

	rec_0 				= lu_brain_rec_add(
		/*belongs to*/			brain, 
		/*width*/				3, 
		/*height*/				3, 
		/*depth*/				1,
		/*config*/ 				lu_rec_config__get_by_id(LU_RC_TEST1)
	);	

	TEST_ASSERT(rec_0);

	rec_1 				= lu_brain_rec_add(
		/*belongs to*/			brain, 
		/*width*/				2, 
		/*height*/				2, 
		/*depth*/				1,
		/*config*/ 				lu_rec_config__get_by_id(LU_RC_TEST1)
	);	

	TEST_ASSERT(rec_1);

	TEST_ASSERT(brain->recs->count);
}

void tearDown(void)
{	
	lu_rec__destroy(rec_0);
	lu_rec__destroy(rec_1);
	lu_brain__destroy(brain);
}

void test_lu_seq_1(void)
{ 
	lu_p_value d;
	Lu_Seq seq = lu_seq__create(lu_g_mem, lu_brain__recs_size(brain)); 

 		TEST_ASSERT(lu_seq__blocks_count(seq) == 0);
 		TEST_ASSERT(lu_seq__last_values(seq, 0) == NULL);
		
	lu_seq__push(seq, rec_0, data_00);

		d = lu_seq__last_values(seq, rec_0->id);
		TEST_ASSERT(d[0] == 0);
		TEST_ASSERT(lu_seq__blocks_count(seq) == 1);

	lu_seq__push(seq, rec_0, data_01);
		
		TEST_ASSERT(lu_seq__blocks_count(seq) == 2);

	lu_seq__push(seq, rec_1, data_12);

		TEST_ASSERT(lu_seq__blocks_count(seq) == 2);
		d = lu_seq__last_values(seq, rec_0->id);
		TEST_ASSERT(d[0] == 1);
		d = lu_seq__last_values(seq, rec_1->id);
		TEST_ASSERT(d[0] == 2);

	lu_seq__block_begin(seq);

		TEST_ASSERT(lu_seq__blocks_count(seq) == 2);

	lu_seq__push(seq, rec_0, data_02);
	
		TEST_ASSERT(lu_seq__blocks_count(seq) == 3);

	lu_seq__push(seq, rec_1, data_13);
		
		d = lu_seq__last_values(seq, rec_1->id);
		TEST_ASSERT(d[0] == 3);

	lu_seq__block_end(seq);
		
		TEST_ASSERT(lu_seq__blocks_count(seq) == 3);

	lu_seq__push(seq, rec_0, data_04);
		
		TEST_ASSERT(lu_seq__blocks_count(seq) == 4);

	lu_seq__reset(seq);

	 	TEST_ASSERT(lu_seq__blocks_count(seq) == 0);

	lu_seq__block_begin(seq);
		
		TEST_ASSERT(lu_seq__blocks_count(seq) == 0);

	lu_seq__push(seq, rec_0, data_05);

		TEST_ASSERT(lu_seq__blocks_count(seq) == 1);

	lu_seq__push(seq, rec_1, data_16);

		TEST_ASSERT(lu_seq__blocks_count(seq) == 1);

	lu_seq__block_end(seq);

		TEST_ASSERT(lu_seq__blocks_count(seq) == 1);

	lu_seq__destroy(seq);
}

void test_lu_seq_2(void)
{ 
	lu_p_value d;
	Lu_Seq seq = lu_seq__create(lu_g_mem, lu_brain__recs_size(brain)); 
	lu_seq__block_begin(seq);
	lu_seq__block_begin(seq);
	lu_seq__block_begin(seq);

 		TEST_ASSERT(lu_seq__blocks_count(seq) == 0);
	 	TEST_ASSERT(lu_seq__last_values(seq, 0) == NULL);
	
	lu_seq__block_end(seq);
		TEST_ASSERT(lu_seq__blocks_count(seq) == 0);
	lu_seq__block_end(seq);
	lu_seq__push(seq, rec_0, data_00);
	lu_seq__block_begin(seq);
	lu_seq__block_begin(seq);

		d = lu_seq__last_values(seq, rec_0->id);
		TEST_ASSERT(d[0] == 0);
		TEST_ASSERT(lu_seq__blocks_count(seq) == 1);

	lu_seq__destroy(seq);
}

void test_lu_seq_data(void)
{
	lu_p_value d;
	Lu_Data data;
	Lu_Seq seq = lu_seq__create(lu_g_mem, lu_brain__recs_size(brain)); 

		TEST_ASSERT(lu_seq__blocks_count(seq) == 0);

  		data = lu_seq__last_data(seq, 0);

  			TEST_ASSERT(data == NULL);

		data = lu_seq__last_data(seq, 0);

			TEST_ASSERT(data == NULL);

	lu_seq__push(seq, rec_0, data_00);
 		
 		TEST_ASSERT(lu_seq__blocks_count(seq) == 1);
		
		data = lu_seq__last_data(seq, 0);
		
		TEST_ASSERT(data->values);
		TEST_ASSERT(data->values[0] == 0);
		TEST_ASSERT(data->w == 3);
 		TEST_ASSERT(data->h == 3);
		
	lu_seq__push(seq, rec_1, data_16);
 		
 		TEST_ASSERT(lu_seq__blocks_count(seq) == 1);
		
		data = lu_seq__last_data(seq, 1);
		
		TEST_ASSERT(data->values);
		TEST_ASSERT(data->values[0] == 6);
		TEST_ASSERT(data->w == 2);
 		TEST_ASSERT(data->h == 2);
		
		data = lu_seq__last_data(seq, 0);
		TEST_ASSERT(data);
		TEST_ASSERT(data->values[0] == 0);
		TEST_ASSERT(data->w == 3);
 		TEST_ASSERT(data->h == 3);


	lu_seq__destroy(seq);
}

void test_lu_seq_validate(void)
{
	Lu_Seq seq = lu_seq__create(lu_g_mem, lu_brain__recs_size(brain)); 

	lu__user_assert_off();
	TEST_ASSERT(lu_seq__validate(seq) == NULL); 
	lu__user_assert_on();

	lu_seq__push(seq, rec_0, data_00);

	TEST_ASSERT(lu_seq__validate(seq) != NULL); 

	lu_seq__destroy(seq);
}

void test_lu_seq_prepare(void)
{
	lu_p_value d;
	Lu_Data data;
	Lu_Seq seq = lu_seq__create(lu_g_mem, lu_brain__recs_size(brain)); 

	lu_seq__push(seq, rec_0, data_00);

	seq = lu_seq__prepare(seq);
	TEST_ASSERT(seq);

	lu_seq__destroy(seq);
}