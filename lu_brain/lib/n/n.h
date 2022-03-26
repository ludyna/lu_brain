/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	n_tables are always "3d"
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_Base

	struct lu_n_cell_base {
		lu_byte type;
	};
	
	static inline Lu_N_Cell_Base lu_n_cell_base__init(Lu_N_Cell_Base self, lu_byte type)
	{
		lu__assert(self);
		self->type = type;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_VP

	struct lu_n_cell_vp {
		struct lu_n_cell_base super;

		lu_value value; 
		lu_size x;
		lu_size y;
		lu_size z;
	};

	static inline Lu_N_Cell_VP lu_n_cell_vp__init(
		Lu_N_Cell_VP self, 
		lu_value value,
		lu_size x,
		lu_size y,
		lu_size z
	)
	{
		self->value = value;
		self->x = x;
		self->y = y;
		self->z = z;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table_Comp
//

	struct lu_n_table_comp {
		Lu_Mem mem;
		lu_size w;
		lu_size h;
		lu_size d;

		// w x h x d, empty by default
		struct lu_n_cell_vp* cells;
	};

	static Lu_N_Table_Comp lu_n_table_comp__create(
		Lu_Config config, 
		Lu_Comp_Calc comp_calc, 
		lu_size width, 
		lu_size height, 
		lu_size depth 
	);

	static void lu_n_table_comp__destroy(Lu_N_Table_Comp self);

	static inline Lu_N_Cell_VP lu_n_table_comp__get_cell(Lu_N_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		return &self->cells[z * self->w * self->h + y * self->w + x];
	}

	static inline lu_size lu_n_table_comp__get_cell_ix(Lu_N_Table_Comp self, Lu_N_Cell_VP cell)
	{
		return cell - self->cells;
	} 
	

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell
//

	#define LU_N__NULL 0

	struct lu_n_cell {
		// insead of adding +1 when saving index, we dont use 0 index cells
		lu_size prev_ix;
		// lu_size id; nema smyslu davaty id, yaksho my mozhemu vziaty &lu_n_cell - &cells i bude id

		// index to back links strings (zero limited) in for prev (child) n_table located in this n_table
		lu_size links_ix; 
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_N_String

	struct lu_n_string {
		lu_size pos;
		lu_p_size p;
	};

	static inline void lu_n_string__init(Lu_N_String self, lu_p_size p)
	{
		lu__debug_assert(self);
		lu__debug_assert(p);

		self->pos = 0;
		self->p = p;
	}

	static inline void lu_n_string__reset(Lu_N_String self)
	{
		lu__debug_assert(self);
		self->p = NULL;
		self->pos = 0;
	}

	static inline lu_size lu_n_string__get(Lu_N_String self)
	{
		lu_size v = self->p[self->pos]; 
		v && (++self->pos);
		return v;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Free_Links
//
	struct lu_n_free_links {
		// free (deleted) strings
		// Ce maye buty okrema structura
		lu_p_size *free_1;
		lu_p_size *free_2;
		lu_p_size *free_4;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Links
// Mozhe buty dlia vsih n_table, chy krashche zrobyty dlia kozhnoho n_column?
// Dlia kozhnoho n_column krashche - maksymalna rozparalezaciya

	struct lu_n_links {
		lu_p_size p;

		//struct lu_n_free_links free_links;
	};

	static Lu_N_Links lu_n_links__init(Lu_Mem mem, lu_size size);
	static void lu_n_links__deinit(Lu_N_Links self, Lu_Mem mem);

	static inline lu_p_size lu_n_links__alloc(Lu_N_Links self, lu_size size)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Column
// 

	////
	// Having separete columns helps with parallelization in the future, but takes a little bit more memory.
	// my mozhemo vykorystovuvaty columns, ale treba
	// prosto znaty v yakomu poriadku zberihayemo string, sho prosto
	// size parne, 0-size/2 cells, size/2-size - free cells
	struct lu_n_column {
		lu_size size;
		struct lu_n_cell* cells;

		// links size is proportional to cells size
		struct lu_n_links links;
	};

	static Lu_N_Column lu_n_column__init(Lu_N_Column self, Lu_Mem mem, lu_size size);
	static void lu_n_column__deinit(Lu_N_Column self, Lu_Mem mem);

	static inline lu_size lu_n_column__get_cell_ix(Lu_N_Column self, Lu_N_Cell cell)
	{
		return cell - self->cells;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table

	struct lu_n_table {
		Lu_Mem mem;

		lu_size w;
		lu_size h;

		lu_byte cell_type; // nema smyslu davaty cell_type v komirku koly to vse povtoruyetsia

		struct lu_n_column* columns;
	};

	static Lu_N_Table lu_n_table__create(Lu_Mem mem, lu_size w, lu_size h, lu_byte cell_type, Lu_Config config);
	static void lu_n_table__destroy(Lu_N_Table self);