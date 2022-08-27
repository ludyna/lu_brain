/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	$ clear; ceedling clean; ceedling test:brain_02 --trace
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger     md;
Lu_Brain 			brain;
struct lu_config 	brain_config;
Lu_Save_Wave 		s_wave;
Lu_Restore_Wave 	r_wave;

Lu_Rec 				rec_0;
Lu_Rec 				rec_1;

lu_value blank_values[] = 
	{ 
		0, 0, 0, 
		0, 0, 0, 
		0, 0, 0, 
		0, 0, 0, 
		0, 0, 0, 
	};

lu_value patterns[][15] = {
	{ 
		1, 1, 1, 
		1, 0, 1, 
		1, 0, 1, 
		1, 0, 1, 
		1, 1, 1, 
	},
	{ 
		0, 0, 1, 
		0, 1, 1, 
		0, 0, 1, 
		0, 0, 1, 
		0, 0, 1, 
	},
	{ 
		1, 1, 1, 
		0, 0, 1, 
		0, 1, 0, 
		1, 0, 0, 
		1, 1, 1, 
	},
	{ 
		1, 1, 1, 
		0, 0, 1, 
		1, 1, 1, 
		0, 0, 1, 
		1, 1, 1, 
	},
	{ 
		1, 0, 1, 
		1, 0, 1, 
		1, 1, 1, 
		0, 0, 1,
		0, 0, 1,
	},
	{ 
		1, 1, 1, 
		1, 0, 0,
		1, 1, 1, 
		0, 0, 1,
		1, 1, 1, 
	},
	{ 
		1, 1, 1, 
		1, 0, 0, 
		1, 1, 1, 
		1, 0, 1, 
		1, 1, 1, 
	},
	{ 
		1, 1, 1, 
		1, 0, 1, 
		0, 0, 1, 
		0, 0, 1, 
		0, 0, 1, 
	},
	{ 
		1, 1, 1, 
		1, 0, 1, 
		1, 1, 1, 
		1, 0, 1, 
		1, 1, 1, 
	},
	{ 
		1, 1, 1, 
		1, 0, 1, 
		1, 1, 1, 
		0, 0, 1, 
		1, 1, 1, 
	},
	{ 
		1, 0, 0, 
		0, 0, 0, 
		0, 0, 0, 
		0, 0, 0, 
		0, 0, 0, 
	},
	{ 
		0, 0, 0, 
		0, 1, 0, 
		0, 0, 0, 
		0, 1, 0, 
		0, 0, 0, 
	}
};

enum label_type {
	LABEL_0 = 0,
	LABEL_1 = 1,
	LABEL_2 = 2,
	LABEL_3 = 3,
	LABEL_4 = 4,
	LABEL_5 = 5,
	LABEL_6 = 6,
	LABEL_7 = 7,
	LABEL_8 = 8,
	LABEL_9 = 9,
	LABEL_DOT = 14,
	LABEL_DOT_2 = 15,
	LABEL_END = 12
};

lu_size labels[] = { 
	LABEL_0,
	LABEL_1,
	LABEL_2,
	LABEL_3,
	LABEL_4,
	LABEL_5,
	LABEL_6,
	LABEL_7,
	LABEL_8,
	LABEL_9,
	LABEL_DOT,
	LABEL_DOT_2
};



// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);
 
	brain_config 		= lu_config__get_by_id(LU_CONFIG__DEFAULT);

	brain 				= lu_brain__create(brain_config);
	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);

	rec_0 				= lu_brain__rec_add(
		/*belongs to*/			brain, 
		/*width*/				3, 
		/*height*/				5, 
		/*depth*/				1,
		/*config*/ 				lu_rec_config__get_by_id(LU_REC__MONO1_IMAGE)
	);	
	TEST_ASSERT(rec_0);

	// rec_1 				= lu_brain__rec_add(
	// 	/*belongs to*/			brain, 
	// 	/*width*/				3, 
	// 	/*height*/				3, 
	// 	/*depth*/				1,
	// 	/*config*/ 				lu_rec_config__get_by_id(LU_REC__TEST1)
	// );	
	// TEST_ASSERT(rec_1);
	
	TEST_ASSERT(brain->recs->count);

	lu_brain__build(brain);


	//
	// Reset waves variables
	// 

	s_wave = NULL;
	r_wave = NULL;
}

void tearDown(void)
{	
	//
	// Destroy waves
	//

	if (s_wave) lu_save_wave__destroy(s_wave); 
	if (r_wave) lu_restore_wave__destroy(r_wave);

	//
	// Destroy brain
	//

	lu_brain__destroy(brain);

	//
	// Destroy debugger
	//

	lu_mem_debugger__print(md);

	TEST_ASSERT(lu_mem_debugger__is_all_freed(md));
    lu_mem_debugger__destroy(md, true);
}

void save_all_paterns()
{
	s_wave = lu_save_wave__create(brain); 
	TEST_ASSERT(s_wave);
	TEST_ASSERT(lu_wave__get_ix((Lu_Wave)s_wave) == 0);
	TEST_ASSERT(lu_brain__get_wave_by_ix(brain, lu_wave__get_ix((Lu_Wave)s_wave), lu_wave__get_type((Lu_Wave)s_wave)) == (Lu_Wave)s_wave);

	lu_size label;
	lu_value* values;
	Lu_La_Cell label_cell;
	for (lu_size i = 0; i < LABEL_END; i++)
	{
		label = labels[i];
		values = patterns[i];

		lu__debug("\nSAVING PATTERN FOR LABEL: %ld", label);
		lu_values__print_symbols(values, 3, 5, 1);

		lu_save_wave__push(s_wave, rec_0, blank_values, 3, 5, 1);
		lu_save_wave__push(s_wave, rec_0, values, 3, 5, 1);

		lu_save_wave__save(s_wave, LU_SAVE_CONFIG__DEFAULT);
		label_cell = lu_save_wave__link_to_label(s_wave, 2, 0, 0, 0, label);
		TEST_ASSERT(label_cell);
	}
}


void restore_all_patterns()
{
	r_wave = lu_restore_wave__create(brain, LU_RESTORE_CONFIG__DEFAULT);

	lu_size label;
	for (lu_size i = 0; i < 1; i++)
	{
		label = labels[i];
		lu_restore_wave__restore_from_label(r_wave, label);
	}

}

void test_brain_05(void) 
{ 
	save_all_paterns();
	
	restore_all_patterns();

	lu_brain__print_net_stats(brain);
}
