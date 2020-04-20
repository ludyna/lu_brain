/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Opts

	struct lu_rec_opts {
		Lu_Brain_Opts  	brain_opts;

		lu_size 		width;
		lu_size 		height;
		lu_size 		depth;

		lu_value 		min_value;
		lu_value 		max_value;
		lu_size			val_neu_size;
		lu_value		val_ssp;  // val significant similarity percent
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec

	struct lu_rec {
		Lu_Brain 		brain;
		lu_size 		id;

		lu_size 		width;
		lu_size 		height;
		lu_size 		depth;

		lu_value 		min_value;
		lu_value 		max_value;
		lu_size			val_neu_size;
		lu_value		val_ssp;  // val significant similarity percent
	};
