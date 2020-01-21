/**
	Copyright © 2019 Oleh Ihorovych Novosad (Novossaad)
*/
#ifndef _LU_MAX_N_NEU_H
#define _LU_MAX_N_NEU_H
 
#include "lib/lists/list.h"

///////////////////////////////////////////////////////////////////////////////
// Structs and types

struct max_n_neu {
	List list;
};

typedef struct max_n_neu* MaxNNeu;

///////////////////////////////////////////////////////////////////////////////
// Init, create and destroy

MaxNNeu max_n_neu_create(lu_size size);
void max_n_neu_destroy(MaxNNeu*);

///////////////////////////////////////////////////////////////////////////////
// Main public methods

void max_n_neu_set(Neu neu);
void max_n_neu_max();

///////////////////////////////////////////////////////////////////////////////
// Other public methods



#endif // _LU_MAX_N_NEU_H
