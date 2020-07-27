/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "../../lu_brain/brain/brain.h"
 
///////////////////////////////////////////////////////////////////////////////
// Smn_Digit

	#define SMN_DIGIT_W 16
	#define SMN_DIGIT_H 16
	#define SMN_DIGIT_PIXEL_COUNT (SMN_DIGIT_W*SMN_DIGIT_H)
	#define SMN_DIGIT_VALUE_COUNT 10
	#define SMN_FILE_NAME "data/semeion.data"

	typedef struct smn_digit* 		Smn_Digit;
	typedef struct smn_group* Smn_Group;

	enum sd_type {
		SD_NONE = 0, 
		SD_SELECTED_FOR_TRAINING, 
		SD_SELECTED_FOR_TEST
	};

	// Single digit sample
	struct smn_digit {
		size_t 			id;
		lu_value 		pixels[SMN_DIGIT_PIXEL_COUNT];
		int 			name;
		enum 			sd_type type;
	};

	void smn_digit_print(Smn_Digit self);

	// Group digit samples with the same name 
	struct smn_group {
		int 			name;
		size_t 			size;
		size_t 			count;
		Smn_Digit* 		data;
		size_t			training_size;
		size_t 			test_size;
	};

///////////////////////////////////////////////////////////////////////////////
// Smn_Data

	#define SMN_SAVE_SAMPLES_PERCENT 0.9

	extern Smn_Digit 				smn_data;
	extern size_t 					smn_data_count;

	extern struct smn_group			smn_groups[SMN_DIGIT_VALUE_COUNT];

	extern Smn_Digit* 				smn_training_samples;
	extern size_t 					smn_training_samples_count;

	extern Smn_Digit*				smn_test_samples;
	extern size_t 					smn_test_samples_count;

	void smn_groups_init();
	void smn_groups_data_alloc();
	void smn_groups_data_fill();
	void smn_groups_data_free();

	void smn_data_load();
	void smn_data_free();

	void smn_data_samples_create();;
	void smn_data_samples_free();

///////////////////////////////////////////////////////////////////////////////
// Utils

	static inline int rand_in_range(int lower, int upper) 
	{ 
		return (rand() % (upper - lower + 1)) + lower;
	} 

	#define smn_user_assert(exp, msg) if(!(exp)) return g_user_assert ? printf(msg) : NULL;
	#define smn_user_assert_void(exp, msg) if(!(exp)) { if (g_user_assert) printf(msg); return; }
	