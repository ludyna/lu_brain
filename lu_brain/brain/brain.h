/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_SRC_BRAIN_H
#define _LU_SRC_BRAIN_H

#include "basic/basic.h"
#include "lib/lib.h"

#include "../lu_brain.h" // public interface

#include "typedefs.h"
#include "data/data.h"
#include "n/n.h"
#include "rec/rec.h"
#include "net/net.h"
#include "w/w.h"
#include "gate/gate.h"
#include "story/story.h"
#include "s/s.h"

///////////////////////////////////////////////////////////////////////////////
// Nouns



///////////////////////////////////////////////////////////////////////////////
// Brain API

	struct lu_brain_opts {
		lu_size				id;
		lu_size 			size_in_bytes;			// lu_brain size in bytes including 
													// everything related

		////////////////////////////////////
		// Recs
		Arr					rec_opts;				// recs options

		////////////////////////////////////
		// Gate
		struct gate_opts 	gate_opts;

	};

	struct lu_brain {
		lu_size			id;  		// useful for logs and debugging 
									// in multi-lu_brain env

		Mem 			app_mem;

		Arr				recs;		// receivers
 
 		Gate 			gate;

		S_Mem 			s_mem;
		N_Mem 			n_mem;		
	};	


	static inline Gate brain_gate(Lu_Brain self)
	{
		return self->gate;
	}	


#endif // _LU_SRC_BRAIN_H
