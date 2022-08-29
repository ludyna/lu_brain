/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	This is just helper header file originaly created for example_02.c
*/

///////////////////////////////////////////////////////////////////////////////
// Tokens

	// LE shortcut to Ludyna Example 
	#define LE__GREETING_SIZE 2000

	enum le_set_type {
		LE_DATA_SET__TRAIN,
		LE_DATA_SET__TEST,
		LE_DATA_SET__END
	};

	static inline enum le_set_type le_token__to_type(char* self)
	{
		if (strcmp(self, "train_set") == 0)
		{
			return LE_DATA_SET__TRAIN;
		}
		else if (strcmp(self, "test_set") == 0)
		{
			return LE_DATA_SET__TEST;
		}

		return LE_DATA_SET__END;
	}


	static inline int le_token__to_num(char* self) 
	{
		if (strcmp(self, "all") == 0)
		{
			return -1; // means all
		}

		int num;
		sscanf(self, "%d", &num);

		return num;
	}

///////////////////////////////////////////////////////////////////////////////
// Brain and waves


	struct lu_config le_config;
	Lu_Brain le_brain;
	Lu_Rec le_image_rec;
	Lu_Save_Wave le_save_wave;
	Lu_Match_Wave le_match_wave;
	Lu_Delete_Wave le_delete_wave;
	Lu_Restore_Wave le_restore_wave;

	static inline void le_brain_and_waves__create()
	{
		le_config = lu_config__get_by_id(LU_CONFIG__SEMEION_01);

		le_config.w_match_sig_breakpoint = 0.4;

		le_brain = lu_brain__create(le_config);
		lu__assert(le_brain);
		
		le_image_rec = lu_brain__rec_add(
			/*belongs to*/			le_brain, 
			/*width*/				16, 
			/*height*/				16, 
			/*depth*/				1,
			/*predefined le_config */ 	lu_rec_config__get_by_id(LU_REC__MONO1_IMAGE)
		);	
		lu__assert(le_image_rec);

		// After we added all recs we need to build/rebuild le_brain
		lu_brain__build(le_brain);

		// Create le_save_wave
		
		le_save_wave = lu_save_wave__create(le_brain);
		lu__assert(le_save_wave);  

		le_match_wave = lu_match_wave__create(le_brain);
		lu__assert(le_match_wave);

		le_delete_wave = lu_delete_wave__create(le_brain, LU_DELETE_CONFIG__DEFAULT);
		lu__assert(le_delete_wave);

		le_restore_wave = lu_restore_wave__create(le_brain, LU_RESTORE_CONFIG__DEFAULT);
		lu__assert(le_restore_wave);
	}

	static inline void le_brain_and_waves__destroy()
	{
		lu_restore_wave__destroy(le_restore_wave);
		lu_delete_wave__destroy(le_delete_wave);
		lu_match_wave__destroy(le_match_wave);
		lu_save_wave__destroy(le_save_wave);
		lu_brain__destroy(le_brain);
	}


///////////////////////////////////////////////////////////////////////////////
// Show

	static inline void le_user_action__show_test_sample(int sample)
	{
		if(sample < 0 || sample >= smn_test_samples_count)
		{
			printf("%%number is out of scope [0, %ld).", smn_test_samples_count);
			return;
		}

		Smn_Digit digit = smn_test_samples[sample];
		smn_digit__print(digit);
	}

	static inline void le_user_action__show_train_sample(int sample)
	{
		if(sample < 0 || sample >= smn_training_samples_count)
		{
			printf("%%number is out of scope [0, %ld).", smn_training_samples_count);
			return;
		}

		Smn_Digit digit = smn_training_samples[sample];
		smn_digit__print(digit);
	}

	static inline void le_user_action__show(enum le_set_type set_type, int sample)
	{
		switch(set_type)
		{
			case LE_DATA_SET__TRAIN:
				le_user_action__show_train_sample(sample);
			 	break;
			case LE_DATA_SET__TEST:
				le_user_action__show_test_sample(sample);
				break;
			default:
				printf("Unknown data set.");
		}

	}

///////////////////////////////////////////////////////////////////////////////
// Learn

	static inline void le_learn_sample(Smn_Digit d)
	{
		lu_save_wave__push(le_save_wave, le_image_rec, smn_blank_pixels, 16, 16, 1);
		lu_save_wave__push(le_save_wave, le_image_rec, d->pixels, 16, 16, 1);

		lu_save_wave__save(le_save_wave, LU_SAVE_CONFIG__DEFAULT);

		Lu_La_Cell la_cell = lu_save_wave__link_to_label(le_save_wave, 2, 0, 0, 0, d->name);
		lu__assert(la_cell);
	}

	static inline void le_user_action__learn_all_test_samples()
	{
		for (lu_size i = 0; i < smn_test_samples_count; i++)
		{
			le_learn_sample(smn_test_samples[i]);
		}
		printf("All %ld test samples learned.", smn_test_samples_count);
	}

	static inline void le_user_action__learn_all_training_samples()
	{
		for (lu_size i = 0; i < smn_training_samples_count; i++)
		{
			le_learn_sample(smn_training_samples[i]);
		}
		printf("All %ld training samples learned.", smn_training_samples_count);
	}

	static inline void le_user_action__learn_test_sample(int sample)
	{
		if (sample == -1)
		{
			le_user_action__learn_all_test_samples();
			return;
		}

		if(sample < 0 || sample >= smn_test_samples_count)
		{
			printf("%%number is out of scope [0, %ld).", smn_test_samples_count);
			return;
		}

		smn_digit__print(smn_test_samples[sample]);
		le_learn_sample(smn_test_samples[sample]);
		printf("Test sample %d learned.", sample);
	}

	static inline void le_user_action__learn_train_sample(int sample)
	{
		if (sample == -1)
		{
			le_user_action__learn_all_training_samples();
			return;
		}

		if(sample < 0 || sample >= smn_training_samples_count)
		{
			printf("%%number is out of scope [0, %ld).", smn_training_samples_count);
			return;
		}

		smn_digit__print(smn_training_samples[sample]);
		le_learn_sample(smn_training_samples[sample]);
		printf("Training sample %d learned.", sample);
	}

	static inline void le_user_action__learn(enum le_set_type set_type, int sample)
	{
		switch(set_type)
		{
			case LE_DATA_SET__TRAIN:
				le_user_action__learn_train_sample(sample);
			 	break;
			case LE_DATA_SET__TEST:
				le_user_action__learn_test_sample(sample);
				break;
			default:
				printf("Unknown data set.");
		}

	}

///////////////////////////////////////////////////////////////////////////////
// Match

	static inline void le_match_print_results(Smn_Digit d, int res)
	{
		if (res == d->name)
		{
			lu_match_wave__print_results(le_match_wave);
			printf("\nRESULT: %d (SUCCESS)", res);
		}
		else
		{
			printf("\nRESULT: %d (FAILED)", res);

		}
	}

	static inline int le_match_sample(Smn_Digit d)
	{
		lu_match_wave__push(le_match_wave, le_image_rec, smn_blank_pixels, 16, 16, 1);
		lu_match_wave__push(le_match_wave, le_image_rec, d->pixels, 16, 16, 1);

		lu_match_wave__match(le_match_wave, LU_MATCH_CONFIG__DEFAULT);

		Lu_Label* labels = lu_match_wave__get_result_labels(le_match_wave);

		if (labels && labels[0])
		{
			return lu_label__get_id(labels[0]);
		}

		return	-1;
	}

	static inline void le_user_action__match_all_training_samples()
	{
		int res;
		lu_size success_count = 0;
		lu_size failed_count = 0;
		Smn_Digit d;
		for (lu_size i = 0; i < smn_training_samples_count; i++)
		{
			d = smn_test_samples[i];
			res = le_match_sample(d);

			if (res == d->name)
			{
				++success_count;
			}
			else
			{
				++failed_count;
			}
		}

		printf(
			"Match success: %ld, failed %ld, accuracy: %.2f%%", 
			success_count, 
			failed_count, 
			(success_count / (lu_value) smn_training_samples_count) * 100.0
		);
	}

	static inline void le_user_action__match_all_test_samples()
	{
		int res;
		lu_size success_count = 0;
		lu_size failed_count = 0;
		Smn_Digit d;
		for (lu_size i = 0; i < smn_test_samples_count; i++)
		{
			d = smn_test_samples[i];
			res = le_match_sample(d);

			if (res == d->name)
			{
				++success_count;
			}
			else
			{
				++failed_count;
			}
		}

		printf(
			"Match success: %ld, failed %ld, accuracy: %.2f%%", 
			success_count, 
			failed_count, 
			(success_count / (lu_value) smn_test_samples_count) * 100.0
		);
	}

	static inline void le_user_action__match_train_sample(int sample)
	{
		if (sample == -1)
		{
			le_user_action__match_all_training_samples();
			return;
		}

		if(sample < 0 || sample >= smn_training_samples_count)
		{
			printf("%%number is out of scope [0, %ld).", smn_training_samples_count);
			return;
		}

		Smn_Digit d = smn_training_samples[sample];
		smn_digit__print(d);
		le_match_print_results(d, le_match_sample(d));
	}

	static inline void le_user_action__match_test_sample(int sample)
	{
		if (sample == -1)
		{
			le_user_action__match_all_test_samples();
			return;
		}

		if(sample < 0 || sample >= smn_test_samples_count)
		{
			printf("%%number is out of scope [0, %ld).", smn_test_samples_count);
			return;
		}

		Smn_Digit d = smn_test_samples[sample];
		smn_digit__print(d);
		le_match_print_results(d, le_match_sample(d));
	}

	static inline void le_user_action__match(enum le_set_type set_type, int sample)
	{
		switch(set_type)
		{
			case LE_DATA_SET__TRAIN:
				le_user_action__match_train_sample(sample);
			 	break;
			case LE_DATA_SET__TEST:
				le_user_action__match_test_sample(sample);
				break;
			default:
				printf("Unknown data set.");
		}

	}

///////////////////////////////////////////////////////////////////////////////
// Delete

	static inline void le_user_action__delete(int label, int sample)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Restore

	static inline void le_user_action__restore(int label, int sample)
	{

	}
