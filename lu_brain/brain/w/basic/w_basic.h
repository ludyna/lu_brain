/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
 
	struct w_sig {
		N_Neu 				neu;
		lu_value 			p;
	};

	// asociyuyetsia do s_neu, a ne n_neu
	struct w_neu {
		W_Sig 	sigs; 	// velykyy masyv, de sigs[n_neu_1->sid] vidpovidaye za w_sig dlia n_neu_1
						// kozhne vykorystania n_neu miniaye misciamy n_neu->sid z vyshchym n_neu->sid
						// takym chynom my mozhemo vyddaliaty neu z sid sho perevyshchuye pevne znachennia (starinnia neuroniv)
	};

	struct w_layer {
		lu_size 			w;
		lu_size 			h;

		W_Neu* 				neus;  // peremozhci?
	};

	struct lu_wave {
		Gate 				gate;
		S_Mem 				s_mem; 
		N_Mem 				n_mem;
		Lu_Story 			story;

		struct w_layer 		la_1;
		struct w_layer 		la_2;


	};

	static Lu_Wave wave_init(Lu_Wave self, Gate gate, S_Mem s_mem, N_Mem n_mem);