/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
 
	struct w_sig {
		lu_size 			n_ent;
		lu_value 			p;
	};

	struct w_neu {

	};

	struct w_layer {
		lu_size 			w;
		lu_size 			h;

		W_Neu* 				neus;
	};

	struct lu_wave {
		Gate 				gate;
		S_Mem 				s_mem; 
		N_Mem 				n_mem;

		Lu_Story 			story;

		Arr 				recs;
	};

	static Lu_Wave wave_init(Lu_Wave self, Gate gate, S_Mem s_mem, N_Mem n_mem);