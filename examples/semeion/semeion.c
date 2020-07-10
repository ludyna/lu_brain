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

		printf("\nDigit: %d\n", self->value);
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
	}

///////////////////////////////////////////////////////////////////////////////
// Smn Data

	Smn_Digit smn_data;

	size_t smn_data_read()
	{
	    FILE * fp;
	    char * line = NULL;
	    size_t len = 0;
	    ssize_t read;
	    size_t lines_count = 0;


	    fp = fopen(SMN_FILE_NAME, "r");
	    if (fp == NULL) 
	    { 
	        printf("Could not open file %s", SMN_FILE_NAME); 
	        exit(EXIT_FAILURE);
	    } 

	    while ((read = getline(&line, &len, fp)) != -1) {
	        // printf("Retrieved line of length %zu:\n", read);
	        // printf("%s", line);
	        ++lines_count;
	    }
		printf("\nLoading %lu samples..", lines_count);
		rewind(fp);

		smn_data = (struct smn_digit*) malloc(sizeof(struct smn_digit) * lines_count);

		Smn_Digit digit;
		float val_f;
		int val_i;
		size_t i;
	    size_t j;
	    size_t non_zero_ix;

		for (i = 0; i < lines_count; i++)
		{
			digit = &smn_data[i];
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
		}

		printf("\nLoading complete.");
	    
	exit: 
	    fclose(fp);
	    if (line)
	        free(line);

	    return lines_count;
	}