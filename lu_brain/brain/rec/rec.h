/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Rec_Opts

	struct rec_opts {
		Brain_Opts  	brain_opts;

		lu_size 		channel_size;
		lu_size 		width;
		lu_size 		height;
		lu_value 		min_value;
		lu_value 		max_value;
		lu_size			val_neu_size;
		lu_value		val_ssp;  // val significant similarity percent
	};

///////////////////////////////////////////////////////////////////////////////
// Rec

	struct rec {
		Brain 			brain;
		lu_size 		id;

		lu_size 		channel_size;
		lu_size 		width;
		lu_size 		height;
		lu_value 		min_value;
		lu_value 		max_value;
		lu_size			val_neu_size;
		lu_value		val_ssp;  // val significant similarity percent
	};
