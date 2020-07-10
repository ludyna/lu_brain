/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Smn_Digit

	void smn_digit_print(Smn_Digit self)
	{
		size_t x;
		size_t y;
		int val;

		char* type_string;

		switch(self->type)
		{
			case SD_NONE:
				type_string = "SD_NONE";
				break;
			case SD_SELECTED_FOR_TEST:
				type_string = "SD_SELECTED_FOR_TEST";
				break;
			case SD_SELECTED_FOR_TRAINING:
				type_string = "SD_SELECTED_FOR_TRAINING";
				break;
			default:
				type_string = "UNKNOWN";
		}
		printf("\n--------------------------------------------------");
		printf("\nDigit: %d, type: %s, id: %lu\n\n", self->value, type_string, self->id);
		for(y = 0; y < SMN_DIGIT_H; y++)
		{
			for(x = 0; x < SMN_DIGIT_W; x++)
			{
				val = self->pixels[y * SMN_DIGIT_W + x];
				if (val > 0)
					printf("X");
				else 
					printf(" ");
			}
			printf("\n");
		}
		printf("\n--------------------------------------------------\n");
	}

///////////////////////////////////////////////////////////////////////////////
// Smn_Data

	Smn_Digit 		smn_data 				= NULL;
	size_t 			smn_data_count			= 0;

	Smn_Digit* 		smn_training_samples 		= NULL;
	size_t 			smn_training_samples_count 	= 0;

	Smn_Digit* 		smn_test_samples 		= NULL;
	size_t 			smn_test_samples_count  = 0;

	void smn_data_load()
	{
	    FILE * fp;
	    char * line = NULL;
	    size_t len = 0;
	    ssize_t read;

	    fp = fopen(SMN_FILE_NAME, "r");
	    if (fp == NULL) 
	    { 
	        printf("\nCould not open file %s", SMN_FILE_NAME); 
	        exit(EXIT_FAILURE);
	    } 

	    while ((read = getline(&line, &len, fp)) != -1) {
	        ++smn_data_count;
	    }
		printf("\nLoading %lu samples..", smn_data_count);
		rewind(fp);

		smn_data = (Smn_Digit) calloc(smn_data_count, sizeof(struct smn_digit));

		Smn_Digit digit;
		float val_f;
		int val_i;
		size_t i;
	    size_t j;
	    size_t non_zero_ix;

		for (i = 0; i < smn_data_count; i++)
		{
			digit = &smn_data[i];
			
			digit->id = i;

			for (j = 0; j < SMN_DIGIT_PIXEL_COUNT; j++)
			{
				read = fscanf(fp, "%f", &val_f);
				if (read == -1) goto exit;
				digit->pixels[j] = val_f;
			}

			non_zero_ix = 100;
			for (j = 0; j < SMN_DIGIT_VALUE_COUNT; j++)
			{
				read = fscanf(fp, "%d", &val_i);
				if (read == -1) goto exit;
				if (val_i != 0) non_zero_ix = j;
			}

			digit->value = non_zero_ix;
			digit->type = SD_NONE;
		}

		printf("\nLoading complete.");
	    
	exit: 
	    fclose(fp);
	    if (line)
	        free(line);
	}

	void smn_data_free()
	{
		if (smn_data) free(smn_data);
	}

	void smn_data_samples_create()
	{
		smn_user_assert_void(SMN_SAVE_SAMPLES_PERCENT < 0.99 && SMN_SAVE_SAMPLES_PERCENT >= 0.3, "SMN_SAVE_SAMPLES_PERCENT in bad range"); 

		smn_training_samples_count = smn_data_count * SMN_SAVE_SAMPLES_PERCENT;
		smn_test_samples_count = smn_data_count - smn_training_samples_count;

		smn_test_samples = (Smn_Digit*) calloc(smn_test_samples_count, sizeof(Smn_Digit));
		smn_user_assert_void(smn_test_samples, "Cannot allocate smn_test_samples");

		smn_training_samples = (Smn_Digit*) calloc(smn_training_samples_count, sizeof(Smn_Digit));
		smn_user_assert_void(smn_training_samples, "Cannot allocate smn_training_samples");

		printf("\nSelecting %lu random test samples", smn_test_samples_count);

		size_t i = 0;
		Smn_Digit d;
		while (i < smn_test_samples_count)
		{
			d = &smn_data[rand_in_range(0, (int) smn_data_count - 1)];
			smn_user_assert_void(d, "d is NULL");

			if (d->type == SD_NONE)
			{
 				d->type = SD_SELECTED_FOR_TEST;
 				smn_test_samples[i] = d;
 				++i;
			}
		}

		printf("\nSelecting %lu random training samples", smn_training_samples_count);

		size_t j = 0;
		i = 0;
		while (i < smn_training_samples_count && j < smn_data_count)
		{
			d = &smn_data[j];
			if (d->type == SD_NONE)
			{
				d->type = SD_SELECTED_FOR_TRAINING;
				smn_training_samples[i] = d;
				++i;
			}
			++j;
		}

		smn_user_assert_void(i == smn_training_samples_count, "Sanity check failed: i != smn_training_samples_count");
	}

	void smn_data_samples_free()
	{
		if (smn_test_samples) free(smn_test_samples);
		if (smn_training_samples) free(smn_training_samples);
	}