/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
 
	
///////////////////////////////////////////////////////////////////////////////
// W_Sig

	struct w_sig {
		lu_size 	n_ent;
		lu_value 	p;
	};

///////////////////////////////////////////////////////////////////////////////
// W_Col

	struct w_col
	{

	};

	static W_Col w_col_create(Mem mem, W_Rec w_rec, S_Col s_col);

///////////////////////////////////////////////////////////////////////////////
// W_Rec 

	struct w_rec
	{

	};

	static W_Rec w_rec_create(Mem mem, S_Rec s_rec);


///////////////////////////////////////////////////////////////////////////////
// Lu_Wave

	struct lu_wave {
		Gate 				gate;
		S_Mem 				s_mem; 
		N_Mem 				n_mem;

		Lu_Story 			story;

		Arr 				recs;
	};

	static Lu_Wave wave_init(Lu_Wave self, Gate gate, S_Mem s_mem, N_Mem n_mem);