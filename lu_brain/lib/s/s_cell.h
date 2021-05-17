/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// S Net
// 
	// block_neu
 	#define b_b(n) n->b[0]  
	#define d_d(n) n->d[0]

	// neu
	#define b_vl(n) n->b[0]
	#define b_vp(n) n->b[1]
	#define b_np(n) n->b[2]
	#define b_nl(n) n->b[3]

	#define d_vl(n) n->d[0]
	#define d_vp(n) n->d[1]
	#define d_np(n) n->d[2]
	#define d_nl(n) n->d[3]

	struct s_cell {
		enum s_cell_type    	type;			
		//lu_size 				l_ix;		// nomer v layer

		S_Layer 				layer;
	
		S_Cell*					b;
		S_Cell*					d;
	}; 

	struct s_cell_2 {
		struct s_cell 			super;

		lu_size 				x; 
		lu_size 				y;   		
	};

	struct s_cell_3 {
		struct s_cell_2 		super;

		lu_size 				z;

		S_Layer_Conf 			v_conf;
		Hnn_Cell_0* 			n_v_cells;

		S_Layer_Conf 			p_conf;
		Hnn_Cell_0*				n_p_cells;
	};

	// s_neu_inits.lu
	static S_Cell s_cell_init(S_Cell self, enum s_cell_type type, S_Layer, lu_size l_ix);
	static S_Cell_2 s_cell_2_init(S_Cell_2 self, enum s_cell_type type, S_Layer layer, lu_size l_ix, lu_size x, lu_size y);
	
	static S_Cell_3 s_cell_3_init(S_Cell_3 self, S_Layer layer, lu_size l_ix, lu_size x, lu_size y, lu_size z);
	static void s_cell_3_deinit(S_Cell_3 self);

	static S_Cell s_component_links_alloc(S_Cell self, S_Rec);
	static S_Cell s_pixel_links_alloc(S_Cell self, S_Rec);
	static S_Cell s_pyra_links_alloc(S_Cell self, S_Rec);
	static S_Cell s_block_links_alloc(S_Cell self, S_Rec); 
	static void s_cell_links_free(S_Cell self);

	// s_neu_connects.lu
	static void s_pixel_connect(S_Cell_2 self, S_Layer);
	static void s_pyra_connect(S_Cell_2 self, S_Layer);
	static void s_block_connect(S_Cell self, S_Layer);

