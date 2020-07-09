
#include "../lu_brain/brain/brain.h"
#include "../lu_brain/brain/brain.c"

#define PIXEL_COUNT 256
#define VALUE_COUNT 10

struct smn_digit {
	int pixels[PIXEL_COUNT];
	int value;
};

typedef struct smn_digit* Smn_Digit;

void smn_digit_print(Smn_Digit self)
{

}

char file_name[256] = "data/semeion.data";
struct smn_digit* smn_data = NULL;

void smn_data_read()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t lines_count = 0;


    fp = fopen(file_name, "r");
    if (fp == NULL) 
    { 
        printf("Could not open file %s", file_name); 
        exit(EXIT_FAILURE);
    } 

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s", line);
        ++lines_count;
    }
	printf("%lu", lines_count);
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
		for (j = 0; j < PIXEL_COUNT; j++)
		{
			read = fscanf(fp, "%f", &val_f);
			if (read == -1) goto exit;
			digit->pixels[j] = val_f;
		}

		non_zero_ix = 100;
		for (j = 0; j < VALUE_COUNT; j++)
		{
			read = fscanf(fp, "%d", &val_i);
			if (read == -1) goto exit;
			if (val_i != 0) non_zero_ix = j;
		}

		digit->value = non_zero_ix;

	}
  //   float val_f;
  //   while((read = fscanf(fp, "%f", &val_f)) != -1) 
  //   {
		// printf("\n%f", val_f);
  //   }
    
exit: 
    fclose(fp);
    if (line)
        free(line);
}

// gcc -gsemeion.c -osemeion -lm; ./semeion
int main()
{
	printf("Hello SEMEION\n");

	Lu_Brain_Opts brain_opts 			= lu_brain_opts_create(1, 200 * 1024);

	smn_data_read();

	lu_brain_opts_destroy(brain_opts);

	if (smn_data) free(smn_data);

	exit(EXIT_SUCCESS);
}

// 0000001111111100
// 0000011111101100
// 0000111111000110
// 0001111100001111
// 0001111011111110
// 0001110111110110
// 0011111111000110
// 0011111100001100
// 0111111000001100
// 0111100000001100
// 0111000000111000
// 1110000000110000
// 1111000011110000
// 1111000111000000
// 1011111110000000
// 0001111000000000

// 1000000000 


// 0000000001111100
// 0000000000000110
// 0000000000000011
// 0000011100000011
// 0001111100000011
// 0011100000000011
// 0111000000000011
// 0110000000000010
// 1100000000000010
// 1100000000000110
// 1000000000001100
// 1000000000011000
// 1000000000110000
// 1100000011100000
// 0111111110000000
// 0011111000000000
// 1 0 0 0 0 0 0 0 0 0 

// 0000001111111110
// 0000011110001110
// 0000111100000011
// 0001111100000011
// 0011111000000011
// 0111110000000011
// 0111110000000011
// 1101100000000111
// 1101100000000110
// 1101100000001110
// 1011100000011100
// 0001100000111000
// 0001100001110000
// 0001110111100000
// 0000111111000000
// 0000011100000000
// 1 0 0 0 0 0 0 0 0 0 


// 0000000000000111
// 0000000000001110
// 0000000000111110
// 0000000000111100
// 0000000011111000
// 0000011111110000
// 0000111111110000
// 0011110011100000
// 1111100011100000
// 1000000111000000
// 0000001111000000
// 0000001110000000
// 0000011110000000
// 0000011110000000
// 0000011110000000
// 0000111100000000

// 0 1 0 0 0 0 0 0 0 0 


// 0111111110000000
// 0110000111000000
// 1100000011100000
// 1000000001100000
// 0000000011100000
// 0000000011000000
// 0000001110000000
// 0000011000000000
// 0000110000000000
// 0011100000000000
// 0111000000000000
// 0110000000000000
// 1100000000000000
// 1110000000011110
// 0111111111111111
// 0001111111000000

// 0 0 1 0 0 0 0 0 0 0 
