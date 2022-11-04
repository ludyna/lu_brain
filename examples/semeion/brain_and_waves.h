/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	This is just helper header file originaly created for example_02.c
*/

///////////////////////////////////////////////////////////////////////////////
// Tokens

	// LE shortcut to Ludyna Example 
	#define LE__GREETING_SIZE 4000

	enum le_set_type {
		LE_DATA_SET__TRAIN,
		LE_DATA_SET__TEST,
		LE_DATA_SET__ID,
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
		else if (strcmp(self, "id") == 0)
		{
			return LE_DATA_SET__ID;
		}

		return LE_DATA_SET__END;
	}


	static inline int le_token__to_num(char* self) 
	{
		if (strcmp(self, "all") == 0)
		{
			return -1; // means all
		}
		else if (strcmp(self, "all0") == 0)
		{
			return -20;
		}
		else if (strcmp(self, "all1") == 0)
		{
			return -19;
		}
		else if (strcmp(self, "all2") == 0)
		{
			return -18;
		}
		else if (strcmp(self, "all3") == 0)
		{
			return -17;
		}
		else if (strcmp(self, "all4") == 0)
		{
			return -16;
		}
		else if (strcmp(self, "all5") == 0)
		{
			return -15;
		}
		else if (strcmp(self, "all6") == 0)
		{
			return -14;
		}
		else if (strcmp(self, "all7") == 0)
		{
			return -13;
		}
		else if (strcmp(self, "all8") == 0)
		{
			return -12;
		}
		else if (strcmp(self, "all9") == 0)
		{
			return -11;
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

	struct lu_delete_config le_delete_config;
	Lu_Delete_Wave le_delete_wave;

	struct lu_restore_config le_restore_config;
	Lu_Restore_Wave le_restore_wave;

	static inline void le_brain_and_waves__create()
	{
		le_config = lu_config__get_by_id(LU_CONFIG__SEMEION_01);

		le_config.w_match_sig_breakpoint = 0.4;

		le_brain = lu_brain__create(le_config);
		lu__assert(le_brain);
		
		le_image_rec = lu_brain__add_rec(
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

		le_delete_config.processor_list_size = 100000;
		le_delete_wave = lu_delete_wave__create(le_brain, le_delete_config);
		lu__assert(le_delete_wave);

		le_restore_config.processor_list_size = 100000;
		le_restore_wave = lu_restore_wave__create(le_brain, le_restore_config);
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
		if(sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%digit is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];

		printf("Showing random sample for digit %d from test_set.", sample);
		Smn_Digit digit = group.test_samples[smn__rand_in_range(0, (int) group.test_count - 1)];
		smn_digit__print(digit);
	}

	static inline void le_user_action__show_train_sample(int sample)
	{
		if(sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%digit is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];

		printf("Showing random sample for digit %d from train_set.", sample);
		Smn_Digit digit = group.training_samples[smn__rand_in_range(0, (int) group.training_count - 1)];
		smn_digit__print(digit);
	}

	static inline void le_user_action__show_sample_by_id(int sample)
	{
		if(sample < 0 || sample >= smn_data_count)
		{
			printf("%%digit is out of scope [0, %ld).", smn_data_count);
			return;
		}

		Smn_Digit d = &smn_data[sample];
		smn_digit__print(d);
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
			case LE_DATA_SET__ID:
				le_user_action__show_sample_by_id(sample);
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

	static inline void le_user_action__learn_all_test_samples_for_digit(int sample)
	{
		if (sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("digit %d is out of scope [0, %d).", sample, SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];

		for (lu_size i = 0; i < group.test_count; i++)
		{
			le_learn_sample(group.test_samples[i]);
		}

		printf("Learned %ld test samples learned for digit %d.", group.test_count, sample);
	}

	static inline void le_user_action__learn_all_training_samples_for_digit(int sample)
	{
		if(sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("digit is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];

		for (lu_size i = 0; i < group.training_count; i++)
		{
			le_learn_sample(group.training_samples[i]);
		}

		printf("Learned %ld training samples learned for digit %d.", group.training_count, sample);
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
		else if (sample < -1)
		{
			le_user_action__learn_all_test_samples_for_digit(sample + 20);
			return;
		}

		if(sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%digit is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];

		printf("Learning random sample for digit %d from test_set.", sample);
		Smn_Digit d = group.test_samples[smn__rand_in_range(0, (int) group.test_count - 1)];
		smn_digit__print(d);
		le_learn_sample(d);
		printf("Learned test sample with ID %ld.", d->id);
	}

	static inline void le_user_action__learn_train_sample(int sample)
	{
		if (sample == -1)
		{
			le_user_action__learn_all_training_samples();
			return;
		}
		else if (sample < -1)
		{
			le_user_action__learn_all_training_samples_for_digit(sample + 20);
			return;
		}

		if(sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%digit is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];

		printf("Learning random sample for digit %d from train_set.", sample);
		Smn_Digit d = group.training_samples[smn__rand_in_range(0, (int) group.training_count - 1)];
		smn_digit__print(d);
		le_learn_sample(d);
		printf("Learned training sample with ID %ld.", d->id);
	} 

	static inline void le_user_action__learn_by_id(int sample)
	{
		if(sample < 0 || sample >= smn_data_count)
		{
			printf("%%id is out of scope [0, %ld).", smn_data_count);
			return;
		}

		Smn_Digit d = &smn_data[sample];
		smn_digit__print(d);
		le_learn_sample(d);
		printf("Learned sample with ID %ld.", d->id);
	}

	static inline void le_user_action__learn(enum le_set_type set_type, int sample)
	{
		switch(set_type)
		{
			case LE_DATA_SET__ID:
				le_user_action__learn_by_id(sample);
				break;
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

	static inline lu_value lu_match__print_batch_results(lu_size success_count, lu_size failed_count, lu_bool print_results)
	{
		lu_value accuracy = (success_count / (lu_value) (success_count + failed_count)) * 100.0;

		if (print_results)
		{
			printf(
				"Match success: %ld, failed %ld, accuracy: %.2f%%", 
				success_count, 
				failed_count, 
				accuracy
			);
		}

		return accuracy;
	}

	static inline void le_match_print_results(Smn_Digit d, int res)
	{
		lu_match_wave__print_results(le_match_wave);
		printf("\n");

		if (res == d->name)
		{
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

	static inline void le_user_action__match_all_training_samples_for_digit(int sample)
	{
		if (sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("digit %d is out of scope [0, %d).", sample, SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];
		int res;
		lu_size success_count = 0;
		lu_size failed_count = 0;
		Smn_Digit d;

		for (lu_size i = 0; i < group.training_count; i++)
		{
			d = group.training_samples[i];
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

		lu_match__print_batch_results(success_count, failed_count, true);
	}

	static inline lu_value le_user_action__match_all_test_samples_for_digit(int sample, lu_bool print_results)
	{
		if (sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("digit %d is out of scope [0, %d).", sample, SMN_DIGIT__VALUE_COUNT);
			return 0;
		}

		struct smn_group group = smn_groups[sample];
		int res;
		lu_size success_count = 0;
		lu_size failed_count = 0;
		Smn_Digit d;

		Smn_Digit succ[group.test_count];
		Smn_Digit fail[group.test_count];

		for (lu_size i = 0; i < group.test_count; i++)
		{
			d = group.test_samples[i];
			res = le_match_sample(d); 

			if (res == d->name)
			{
				succ[success_count] = d;
				++success_count;
			}
			else
			{
				fail[failed_count] = d;
				++failed_count;
			}
		}

		printf("\n	S ids: ");
		for (lu_size i = 0; i < success_count; i++)
		{
			if (i > 0 && i <= success_count - 1)
			{
				printf(", ");
			}

			d = succ[i];
			printf("%ld", d->id);
		}

		printf("\n	F ids: ");
		for (lu_size i = 0; i < failed_count; i++)
		{
			if (i > 0 && i <= failed_count - 1)
			{
				printf(", ");
			}

			d = fail[i];
			printf("%ld", d->id);
		}

		printf("\n");

		return lu_match__print_batch_results(success_count, failed_count, print_results);
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

		lu_match__print_batch_results(success_count, failed_count, true);
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

		lu_match__print_batch_results(success_count, failed_count, true);
	}

	static inline void le_user_action__match_train_sample(int sample)
	{
		// if (sample == -1)
		// {
		// 	le_user_action__match_all_training_samples();
		// 	return;
		// }
		// else if (sample < -1)
		// {
		// 	le_user_action__match_all_training_samples_for_digit(sample + 20);
		// 	return;
		// }

		if(sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%digit is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];

		printf("Matching random sample for digit %d from train_set.", sample);
		Smn_Digit d = group.training_samples[smn__rand_in_range(0, (int) group.training_count - 1)];
		smn_digit__print(d);
		le_match_print_results(d, le_match_sample(d));
	}

	static inline void le_user_action__match_test_sample(int sample)
	{
		if (sample == -1)
		{
			//le_user_action__match_all_test_samples();
			printf("NOTE: compression and optimizations not implemented yet.\n");

			lu_value sum = 0;

			for (lu_size i =0; i < SMN_DIGIT__VALUE_COUNT; i++)
			{
				printf("For digit %ld: ", i);
				sum += le_user_action__match_all_test_samples_for_digit(i, false);
				printf("\n"); 
			}

			printf("Average accuracy: %.2f%%", sum / (lu_value)SMN_DIGIT__VALUE_COUNT);

			return;
		}
		else if (sample < -1)
		{
			le_user_action__match_all_test_samples_for_digit(sample + 20, true);
			return;
		}

		if(sample < 0 || sample >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%digit is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		struct smn_group group = smn_groups[sample];

		printf("Matching random sample for digit %d from test_set.", sample);
		Smn_Digit d = group.test_samples[smn__rand_in_range(0, (int) group.test_count - 1)];
		smn_digit__print(d);
		le_match_print_results(d, le_match_sample(d));
	}

	static inline void le_user_action__match_by_id(int sample)
	{
		if(sample < 0 || sample >= smn_data_count)
		{
			printf("%%id is out of scope [0, %ld).", smn_data_count);
			return;
		}

		Smn_Digit d = &smn_data[sample];
		smn_digit__print(d);
		le_match_print_results(d, le_match_sample(d));
	}

	static inline void le_user_action__match(enum le_set_type set_type, int sample)
	{
		switch(set_type)
		{
			case LE_DATA_SET__ID:
				le_user_action__match_by_id(sample);
				break;
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

	static inline void le_user_action__delete(int label)
	{
		if (label == -1)
		{
			for (lu_size i = 0; i < SMN_DIGIT__VALUE_COUNT; i++)
			{
				lu_delete_wave__delete_label(le_delete_wave, i);
			}

			printf("Neurons and links for all labels were deleted.");
			return;
		}

		if(label < 0 || label >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%label is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		lu_delete_wave__delete_label(le_delete_wave, label);
		printf("Neurons and links related to label %d were deleted.", label);
	}

///////////////////////////////////////////////////////////////////////////////
// Restore

	static inline void le_user_action__restore(int label)
	{
		if(label < 0 || label >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%label is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		lu_restore_wave__restore_from_label(le_restore_wave, label);
		lu_p_value values = lu_restore_wave__get_values_temp(le_restore_wave);

		if (values == NULL)
		{
			lu__debug("Cannot restore data for label %ld. Doesn't exist?", label);
		}
		else
		{
			lu__debug("RESTORED PATTERN FOR LABEL: %ld", label);

			printf("\n--------------------------------------------------\n");
			smn_values__convert_to_01(values);
			smn_values__print(values);
			printf("\n--------------------------------------------------\n");
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Compress

	static inline void le_user_action__compress_label(int label)
	{
		if(label < 0 || label >= SMN_DIGIT__VALUE_COUNT)
		{
			printf("%%label is out of scope [0, %d).", SMN_DIGIT__VALUE_COUNT);
			return;
		}

		lu_restore_wave__restore_from_label(le_restore_wave, label);
		lu_p_value values = lu_restore_wave__get_values_temp(le_restore_wave);

		if (values == NULL)
		{
			lu__debug("Cannot find data for label %ld. Doesn't exist?", label);
		}

		smn_values__convert_to_01(values);

		le_user_action__delete(label);

		lu_save_wave__push(le_save_wave, le_image_rec, smn_blank_pixels, 16, 16, 1);
		lu_save_wave__push(le_save_wave, le_image_rec, values, 16, 16, 1);

		lu_save_wave__save(le_save_wave, LU_SAVE_CONFIG__DEFAULT);

		Lu_La_Cell la_cell = lu_save_wave__link_to_label(le_save_wave, 2, 0, 0, 0, label);
		lu__assert(la_cell);
	}

	static inline void le_user_action__compress(int label)
	{
		printf("WARNING: This feature is in progress. Doesn't work yet.");

		if (label == -1)
		{
			for (lu_size i = 0; i < SMN_DIGIT__VALUE_COUNT; i++)
			{
				le_user_action__compress_label(i);
			}
		}
		else
		{
			le_user_action__compress_label(label);
		}

		le_brain->config.w_match_sig_breakpoint = 0.0;
	}