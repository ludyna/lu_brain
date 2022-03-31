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
		lu_value value; 
		lu_size x;
		lu_size y;
		lu_size z;
	};

	static inline void lu_n_cell__null_init(Lu_N_Cell_VP self)
	{
		self->value = 0;
		self->x = 0;
		self->y = 0;
		self->z = 0;
	}

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
		return &(self->cells + 1)[z * self->w * self->h + y * self->w + x];
	}

	static inline lu_size lu_n_table_comp__get_cell_ix(Lu_N_Table_Comp self, Lu_N_Cell_VP cell)
	{
		return cell - self->cells;
	} 


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell
//

	#define LU_N_IX__NULL 0

	////
	// Insead of adding +1 when saving index, we dont use 0 index cells
	struct lu_n_cell {
		// lu_size id; nema smyslu davaty id, yaksho my mozhemu vziaty &lu_n_cell - &cells i bude id

		// index to back links strings (zero limited) in for prev (child) n_table located in this n_table
		lu_size p_ix; // either parent ixs string or prev ix dependently on connection type
		lu_size c_ix; // children ixs string 
	};

	static inline lu_bool lu_n_cell_compare(Lu_N_Cell a, Lu_N_Cell b)
	{
		// a.p_ix != b.p_ix && (return false); 

		// // we can make so the same strings have the same index, so comparing 
		// // string index is enough
		// a.c_ix != b.c_ix && (return false); 

		return true;
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Column
// 

	////
	// Having separete columns helps with parallelization in the future, but takes a little bit more memory.
	// my mozhemo vykorystovuvaty columns, ale treba
	// prosto znaty v yakomu poriadku zberihayemo string, sho prosto
	// size parne, 0-size/2 cells, size/2-size - free cells
	// p_reg mozhna vykorystaty ya dlia zberihannia string tak i dlia
	// zberihannia n_cell
	//   xxxxx
	// y
	// y 
	// y 
	// y 

	// de y ce index, y x - ce znachenia strichky, prychomu maksymum 4?
	// mozhna zrobyty z dlia vypadku koly my mayemo povtorennia, 
	// yasho z > max_z robymo povnyy realloc i vse
	// , te same dlia komirok
	// komirka bude maty z i ix, de z i ix toy samyy dlia strichky i dlia komirky
	struct lu_n_column {
		Lu_Mem mem;

		lu_size w;
		lu_size h;
		lu_size d;

		lu_size *strings;
		struct lu_n_cell* cells;
	};

	static Lu_N_Column lu_n_column__init(Lu_N_Column self, Lu_Mem mem, lu_size w, lu_size h, lu_size d);
	static void lu_n_column__deinit(Lu_N_Column self);
	static void lu_n_column__realloc(Lu_N_Column self, lu_size w, lu_size h, lu_size d);

	// static inline lu_size lu_n_column__get_cell_ix(Lu_N_Column self, Lu_N_Cell cell)
	// {
	// 	return cell - self->cells;
	// }

	static Lu_N_Cell lu_n_column__save(Lu_N_Column self, lu_size* children)
	{
		// lu_size p_reg = 0;
		// lu_size ix;
		// lu_size *p = children;
		// while((ix = *p))
		// {
		// 	p_reg = lu_hash_comb(p_reg, ix);
		// 	++p;
		// }


		// ix = p_reg % self->size;

		// Lu_N_Cell n_cell = &(self->cells + 1)[ix];



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

	Lu_N_Table lu_n_table__create(Lu_Mem mem, lu_size w, lu_size h, lu_byte cell_type, Lu_Config config);
 	void lu_n_table__destroy(Lu_N_Table self);


	static inline Lu_N_Cell lu_n_table__save(Lu_N_Table self, lu_size x, lu_size y, lu_size *links)
	{
		return lu_n_column__save(&self->columns[y * self->w + x], links);
	}