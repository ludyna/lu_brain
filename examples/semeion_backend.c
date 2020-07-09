/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

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