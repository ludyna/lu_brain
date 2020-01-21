/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/
#ifndef _LU_SEQUENCE_H
#define _LU_SEQUENCE_H

#include "@brain/net/neu.h"

struct sequence {

};

typedef struct sequence* Sequence;


Neu sequence_save(Sequence, lu_time t);

#endif // _LU_SEQUENCE_H