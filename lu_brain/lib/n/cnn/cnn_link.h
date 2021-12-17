/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Cnn Link	

	struct n_lin {
		N_Cell	 				b;			// b i d potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		N_Cell					d;

		// ce dva spysky
		// odyn z storony b, inshyy z storony d
		N_Lin	 				b_p;
		N_Lin	 				b_n;

		N_Lin	 				d_p; 		// p i n potribni u vypadku yakshou my vydaliayemo zviazok?
		N_Lin					d_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys p ale my neznayemo n
		 		   							// tomu naspravdi i p i n potribni
	};
