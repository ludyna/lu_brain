/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "../../lu_brain/brain/brain.h"
#include "../../lu_brain/brain/brain.c"
 
///////////////////////////////////////////////////////////////////////////////
// Smn_Digit

	#define SMN_DIGIT_W 16
	#define SMN_DIGIT_H 16
	#define SMN_DIGIT_PIXEL_COUNT (SMN_DIGIT_W*SMN_DIGIT_H)
	#define SMN_DIGIT_VALUE_COUNT 10
	#define SMN_FILE_NAME "data/semeion.data"

	typedef struct smn_digit* Smn_Digit;

	struct smn_digit {
		int pixels[SMN_DIGIT_PIXEL_COUNT];
		int value;
	};

	void smn_digit_print(Smn_Digit self);

///////////////////////////////////////////////////////////////////////////////
// Smn_Data

	#define SMN_SAVE_SAMPLES_PERCENT 0.8

	extern Smn_Digit 		smn_data;
	extern size_t 			smn_data_count;

	extern Smn_Digit 		smn_save_samples;
	extern size_t 			smn_save_samples_count;

	extern Smn_Digit 		smn_find_samples;
	extern size_t 			smn_find_samples_count;

	void smn_data_load();
	void smn_data_free();

	void smn_data_save_samples_create();
	void smn_data_save_samples_free();

	void smn_data_find_samples_create();
	void smn_data_find_samples_free();

///////////////////////////////////////////////////////////////////////////////
// Utils

	static inline int rand_in_range(int lower, int upper) 
	{ 
		return (rand() % (upper - lower + 1)) + lower;
	} 