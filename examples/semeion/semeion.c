/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "../../lu_brain/lib/vendor/CException.c"
#include "../../lu_brain/lib/_module.c"

///////////////////////////////////////////////////////////////////////////////
// Smn_Digit

	void smn_digit__print(Smn_Digit self)
	{
		size_t x;
		size_t y;
		lu_value val;

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
		printf("\nDigit: %d, type: %s, id: %lu\n\n", self->name, type_string, self->id);
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
// Smn_Groups

	struct smn_group smn_groups[SMN_DIGIT_VALUE_COUNT];

	void smn_groups__init()
	{
		size_t i;
		Smn_Group group;
		for (i = 0; i < SMN_DIGIT_VALUE_COUNT; i++)
		{
			group 					= &smn_groups[i];
			group->name 			= i;
			group->size 			= 0;
			group->count 			= 0;
			group->data 			= NULL;
			group->training_size 	= 0;
			group->test_size 		= 0;
		}
	}

	void smn_groups__data_alloc()
	{
		size_t i;
		Smn_Group group;
		for (i = 0; i < SMN_DIGIT_VALUE_COUNT; i++)
		{
			group = &smn_groups[i];
			if (group->size)
			{
				group->data = (Smn_Digit*) calloc(group->size, sizeof(Smn_Digit));
			}
		}
	}

	void smn_groups__data_fill()
	{
		Smn_Digit digit;
		Smn_Group group;

		size_t i;
		for (i = 0; i < smn_data_count; i++)
		{
			digit = &smn_data[i];
			group = &smn_groups[digit->name];

			group->data[group->count] = digit;
			++group->count;

			if (group->count > group->size)
			{
				printf("\nSomething went wrong!!");
				break;
			}
		}
	}

	void smn_groups__data_free()
	{
		size_t i;
		Smn_Group group;
		for (i = 0; i < SMN_DIGIT_VALUE_COUNT; i++)
		{
			group 			= &smn_groups[i];
			if (group->data)
			{
				free(group->data);
			}
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Smn_Data

	Smn_Digit 		smn_data 					= NULL;
	size_t 			smn_data_count				= 0;

	Smn_Digit* 		smn_training_samples 		= NULL;
	size_t 			smn_training_samples_count 	= 0;

	Smn_Digit* 		smn_test_samples 			= NULL;
	size_t 			smn_test_samples_count  	= 0;


	void smn_data__load()
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
		Smn_Group group;

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

			digit->name = non_zero_ix;
			digit->type = SD_NONE;

			if (digit->name >= SMN_DIGIT_VALUE_COUNT)
			{
				printf("\ndigit->name >= SMN_DIGIT_VALUE_COUNT!!!\n");
				goto exit;
			}

			group = &smn_groups[digit->name];
			++group->size;
		}
	    
	exit: 
	    fclose(fp);
	    if (line)
	        free(line);
	}

	void smn_data__free()
	{
		if (smn_data) free(smn_data);
	}

	void smn_data__samples_create()
	{
		smn__user_assert_void(SMN_TRAINING_SAMPLES_PERCENT < 0.99 && SMN_TRAINING_SAMPLES_PERCENT >= 0.3, "SMN_TRAINING_SAMPLES_PERCENT in bad range"); 

		smn_training_samples_count = 0;
		smn_test_samples_count = 0;

		size_t i;
		Smn_Group group;
		for (i = 0; i < SMN_DIGIT_VALUE_COUNT; i++)
		{
			group = &smn_groups[i];

			group->training_size = group->count * SMN_TRAINING_SAMPLES_PERCENT;
			group->test_size = group->count - group->training_size;

			smn_training_samples_count += group->training_size;
			smn_test_samples_count += group->test_size;

			printf("\n %d: test(%lu), training(%lu), total(%lu)", group->name, group->test_size, group->training_size, group->count);
		}

		smn_test_samples = (Smn_Digit*) calloc(smn_test_samples_count, sizeof(Smn_Digit));
		smn__user_assert_void(smn_test_samples, "Cannot allocate smn_test_samples");

		smn_training_samples = (Smn_Digit*) calloc(smn_training_samples_count, sizeof(Smn_Digit));
		smn__user_assert_void(smn_training_samples, "Cannot allocate smn_training_samples");

		size_t j;
		Smn_Digit d;
		size_t test_count = 0;
		size_t training_count = 0;
		for (i = 0; i < SMN_DIGIT_VALUE_COUNT; i++)
		{
			group = &smn_groups[i];

			j = 0;
			while (j < group->test_size)
			{
				d = group->data[smn__rand_in_range(0, (int) group->count - 1)];
				smn__user_assert_void(d, "d is NULL");

				if (d->type == SD_NONE)
				{
	 				d->type = SD_SELECTED_FOR_TEST;
	 				smn_test_samples[test_count] = d;
	 				++test_count;
	 				++j;
				}
			}
		}

		smn__user_assert_void(test_count == smn_test_samples_count, "Sanity check failed: test_count == smn_test_samples_count");

		printf("\nSelected %lu random test samples", smn_test_samples_count);

		for (i = 0; i < SMN_DIGIT_VALUE_COUNT; i++)
		{
			group = &smn_groups[i];

			for (j = 0; j < group->count; j++)
			{
				d = group->data[j];

				if (d->type == SD_NONE)
				{
					d->type = SD_SELECTED_FOR_TRAINING;
					smn_training_samples[training_count] = d;
					++training_count;
				}
			}
		}

		smn__user_assert_void(training_count == smn_training_samples_count, "Sanity check failed: training_count == smn_training_samples_count");

		printf("\nSelected %lu random training samples", smn_training_samples_count);
	}

	void smn_data__samples_free()
	{
		if (smn_test_samples) free(smn_test_samples);
		if (smn_training_samples) free(smn_training_samples);
	}