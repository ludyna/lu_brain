/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H


///////////////////////////////////////////////////////////////////////////////
// N Net

// serializaciya bude duzhe prostoyu, 
// treba prosto zberehty N Net ta parametry za yakymy buv stvorenyy brain
// vse reshtu perestvoruyetsia. Tak samo perevydilenia pamiati (z mozhlyvym peremishcheniam v inshe misce).

	struct n_name {
		lu_char 				name[255];
	};	

	struct n_val {
		lu_value 				val;
	};

	struct n_com {
		enum n_com_type type;

		union {
			struct n_name 	name;
			struct n_val 	value;
		} data;
	};

	struct n_neu {
		S_Neu 					s_neu;

		N_Lin 					b_l; 		// v and h and other links
		lu_value 				b_count;

		N_Lin  					d_l;		// v and h and other links

		N_Com 					com;		
	};

	struct n_lin {
		N_Neu	 				b;			// b i d potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		N_Neu					d;

		// ce dva spysky
		// odyn z storony b, inshyy z storony d
		N_Lin	 				b_p;
		N_Lin	 				b_n;

		N_Lin	 				d_p; 		// p i n potribni u vypadku yakshou my vydaliayemo zviazok?
		N_Lin					d_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys p ale my neznayemo n
		 		   							// tomu naspravdi i p i n potribni
	};

///////////////////////////////////////////////////////////////////////////////
// N Dopomizhni

	struct n_mem_opts {
		lu_size 				names_size;
	};

	static inline N_Mem_Opts n_mem_opts_init(N_Mem_Opts self)
	{
		self->names_size = LU_NAMES_SIZE;
	}
	
	struct n_mem {
		// vlasnyk
		Lu_Brain 				brain;

		// Tut potriben Mem_Table bo teoretychno neu mozhut vydaliatys
		Mem_Table				coms;
		Mem_Table 				neus;
		Mem_Table				lins; 
	};

	static N_Mem n_mem_create(Lu_Brain brain);
	static Mem_Table n_mem_coms_create(N_Mem self, Mem mem);
	static Mem_Table n_mem_neus_create(N_Mem self, Mem mem);
	static Mem_Table n_mem_lins_create(N_Mem self, Mem mem);

#endif // _LU_N_H