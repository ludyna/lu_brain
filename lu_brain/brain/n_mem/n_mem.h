/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_N_MEM_H
#define _LU_N_MEM_H

	typedef struct n_mem* N_Mem;


///////////////////////////////////////////////////////////////////////////////
// N_Mem

	struct n_mem {
		Brain 			brain;

		Mem_Table 		ents;
		Mem_Table 		f_links;
		Mem_Table 		b_links;
		Mem_Table 		signals; // stvoruyemo dlia kozhnoho wave okremo
	};
	
	N_Mem n_mem_create(Brain brain);


#endif // _LU_N_MEM_H
