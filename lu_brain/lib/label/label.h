/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// Label

	struct lu_label {
		lu_size label;
		lu_size count;
	};

	struct lu_labels {
		struct lu_arr labels;
	};