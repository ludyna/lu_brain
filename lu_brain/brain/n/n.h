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
		lu_size 				neu;
		lu_char 				name[255];
	};	

	struct n_val {
		lu_size 				neu;
		lu_value 				val;
	};

	struct n_time {
		lu_size				neu;
		lu_size 				val;
	};

	struct n_neu {
		// layer num, s_neu num, sid
		// lu_size 				layer_ix;
		// lu_size				x;
		// lu_size 				y;

		lu_size 				s_ix;

		lu_size 				p_l; 		
		lu_value 				p_count;

		lu_size 				c_l;

		lu_size 				tp;
		lu_size 				tc;

		enum n_com_type			com_type;
		lu_size 				com;		
	};

	struct n_h_lin {
		lu_size	 			p;			
		lu_size				c;
	};

	struct n_v_lin {
		lu_size	 			p;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		lu_size				c;

		// ce dva spysky
		// odyn z storony p, inshyy z storony c
		lu_size	 			p_p;
		lu_size	 			p_n;

		lu_size	 			c_p; 		// p i n potribni u vypadku yakshou my vydaliayemo zviazok?
		lu_size				c_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys p ale my neznayemo n
		 		   						// tomu naspravdi i p i n potribni
	};

///////////////////////////////////////////////////////////////////////////////
// N Dopomizhni
	
	struct n_mem {
		// vlasnyk
		Lu_Brain 				brain;

		// Tut potriben Mem_Table bo teoretychno neu mozhut vydaliatys
		Mem_Table 				neus;
		Mem_Table				lins; 
		Mem_Table				names;
		Mem_Table 				vals;
	};

	static N_Mem n_mem_create(Lu_Brain brain);
	

#endif // _LU_N_H