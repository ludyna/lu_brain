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

	struct lu_s_cell {
		enum lu_s_cell_type    	type;			
		//lu_size 				l_ix;		// nomer v layer

		Lu_S_Layer 				layer;
	
		Lu_S_Cell*					b;
		Lu_S_Cell*					d;
	}; 

	struct lu_s_cell_2 {
		struct lu_s_cell 			super;

		lu_size 				x; 
		lu_size 				y;   		
	};


	struct lu_s_cell_values {
		Lu_S_Layer_Conf conf;
		Hnn_Cell_Value* cells;
	};

	static Lu_S_Cell_Values lu_s_cell_values_create(Lu_Mem mem, Lu_S_Layer_Conf conf);
	static void lu_s_cell_values_destroy(Lu_S_Cell_Values self, Lu_Mem mem);

	struct lu_s_cell_3 {
		struct lu_s_cell_2 		super;

		lu_size 				z;


		Lu_S_Cell_Values 			v;
		Lu_S_Cell_Values  			p;
	};

	// s_neu_inits.lu
	static Lu_S_Cell lu_s_cell_init(Lu_S_Cell self, enum lu_s_cell_type type, Lu_S_Layer, lu_size l_ix);
	static Lu_S_Cell_2 lu_s_cell_2_init(Lu_S_Cell_2 self, enum lu_s_cell_type type, Lu_S_Layer layer, lu_size l_ix, lu_size x, lu_size y);
	
	static Lu_S_Cell_3 lu_s_cell_3_init(Lu_S_Cell_3 self, Lu_S_Layer layer, lu_size l_ix, lu_size x, lu_size y, lu_size z);
	static void lu_s_cell_3_deinit(Lu_S_Cell_3 self);

	static Lu_S_Cell s_component_links_alloc(Lu_S_Cell self, Lu_S_Rec_Rg);
	static Lu_S_Cell s_pixel_links_alloc(Lu_S_Cell self, Lu_S_Rec_Rg);
	static Lu_S_Cell s_pyra_links_alloc(Lu_S_Cell self, Lu_S_Rec_Rg);
	static Lu_S_Cell s_block_links_alloc(Lu_S_Cell self, Lu_S_Rec_Rg); 
	static void lu_s_cell_links_free(Lu_S_Cell self);

	// s_neu_connects.lu
	static void s_pixel_connect(Lu_S_Cell_2 self, Lu_S_Layer);
	static void s_pyra_connect(Lu_S_Cell_2 self, Lu_S_Layer);
	static void s_block_connect(Lu_S_Cell self, Lu_S_Layer);

