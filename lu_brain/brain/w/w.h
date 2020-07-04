/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_sig {
		N_Neu 					neu;
		lu_value 				p;
	};

	// asociyuyetsia do s_neu, a ne n_neu
	struct lu_space {
		Lu_Sig 					sigs; 	// velykyy masyv, de sigs[n_neu_1->sid] vidpovidaye za w_sig dlia n_neu_1
										// kozhne vykorystania n_neu miniaye misciamy n_neu->sid z vyshchym n_neu->sid
										// takym chynom my mozhemo vyddaliaty neu z sid sho perevyshchuye pevne znachennia (starinnia neuroniv)

		Lu_Sig 					w;		// peremozhec
	};

	struct lu_layer {
		lu_size 				w;
		lu_size 				h;

		Lu_Space* 				neus;  // asociyuyutsia z s_neu
	};

	struct lu_net {

	};

	struct lu_wave {
		Gate 					gate;
		S_Mem 					s_mem; 
		N_Mem 					n_mem;
		Lu_Story 				story;

		Lu_Net 					net;
	};

	// Lu_Wave lu_wave_create(Lu_Brain, lu_flags opts);
	// Lu_Net lu_wave_save(Lu_Wave, color, contrast, new_breakpoint); 
	// Lu_Net lu_wave_find(Lu_Wave, color, contrast, fire_breakpoint);
	// Lu_Net lu_wave_restore(Lu_Wave, Lu_Sig);

	// CE PIZDEC IDEA
	// wave stvoruyutsia okremo vid brain v temp memory
	// wave posylayutsia na brain (save , find , restore)
	// rezultatom wave ye nabir w_layers z peremozhnymy w_sig
	// my mozhemo podyvytys de sho ye


