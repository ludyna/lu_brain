/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "../../lu_brain/lib/_module.h"
 
///////////////////////////////////////////////////////////////////////////////
// Smn_Digit

	#define SMN_DIGIT__W 16
	#define SMN_DIGIT__H 16
	#define SMN_DIGIT__PIXEL_COUNT (SMN_DIGIT__W*SMN_DIGIT__H)
	#define SMN_DIGIT__VALUE_COUNT 10
	#define SMN_FILE_NAME "data/semeion.data"

	typedef struct smn_digit* Smn_Digit;
	typedef struct smn_group* Smn_Group;

	enum sd_type {
		SD_NONE = 0, 
		SD_SELECTED_FOR_TRAINING, 
		SD_SELECTED_FOR_TEST
	};

	// Single digit sample
	struct smn_digit {
		size_t 			id;
		lu_value 		pixels[SMN_DIGIT__PIXEL_COUNT];
		int 			name;
		enum 			sd_type type;
	};

	static inline void smn_values__print(lu_p_value values)
	{
		size_t x;
		size_t y;
		lu_value val;

		for(y = 0; y < SMN_DIGIT__H; y++)
		{
			for(x = 0; x < SMN_DIGIT__W; x++)
			{
				val = values[y * SMN_DIGIT__W + x];
				if (val >= 0.25)
					printf("X");
				else 
					printf(" ");
			}
			printf("\n");
		}
	}

	void smn_digit__print(Smn_Digit self);

	// Group digit samples with the same name 
	struct smn_group {
		int 			name;
		size_t 			size;
		size_t 			count;
		Smn_Digit* 		data;
		size_t			training_size;
		size_t 			training_count;
		size_t 			test_size;
		size_t  		test_count;
		Smn_Digit* 	    training_samples;
		Smn_Digit* 	    test_samples;
	};

	lu_value smn_blank_pixels[] = 
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};
///////////////////////////////////////////////////////////////////////////////
// Smn_Data

	#define SMN_TRAINING_SAMPLES_PERCENT 0.93

	extern Smn_Digit 				smn_data;
	extern size_t 					smn_data_count;

	extern struct smn_group			smn_groups[SMN_DIGIT__VALUE_COUNT];

	extern Smn_Digit* 				smn_training_samples;
	extern size_t 					smn_training_samples_count;

	extern Smn_Digit*				smn_test_samples;
	extern size_t 					smn_test_samples_count;

	void smn_groups__init();
	void smn_groups__data_alloc();
	void smn_groups__data_fill();
	void smn_groups__data_free();

	void smn_data__load();
	void smn_data__free();

	void smn_data__samples_create();
	void smn_data__samples_free();

///////////////////////////////////////////////////////////////////////////////
// Utils

	static inline int smn__rand_in_range(int lower, int upper) 
	{ 
		return (rand() % (upper - lower + 1)) + lower;
	} 

	#define smn__user_assert(exp, msg) if(!(exp)) return lu_g_user_assert ? printf(msg) : NULL;
	#define smn__user_assert_void(exp, msg) if(!(exp)) { if (lu_g_user_assert) printf(msg); return; }
	